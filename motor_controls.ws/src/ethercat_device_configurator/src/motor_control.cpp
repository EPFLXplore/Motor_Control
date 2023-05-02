#include "ethercat_device_configurator/EthercatDeviceConfigurator.hpp"
#include <maxon_epos_ethercat_sdk/Maxon.hpp>

#include "rclcpp/rclcpp.hpp"
#include "motor_control_interfaces/msg/motor_command.hpp"

#include <iostream>
#include <thread>
#include <csignal>
#include <string>
#include <vector>

using namespace std::chrono_literals;

using std::placeholders::_1;

enum Motor_mode{
    POSITION,
    VELOCITY,
    TORQUE
};

struct Motor_command{
    std::string name;
    Motor_mode mode;
    double command;
};

std::vector<Motor_command> motor_command_list;

std::unique_ptr<std::thread> worker_thread;
bool abrt = false;

EthercatDeviceConfigurator::SharedPtr configurator;

unsigned int counter = 0;

class Motor_controller : public rclcpp::Node
{
    public:
        Motor_controller()
        : Node("Motor_controller")
        {
            subscription_motor_command_ = this->create_subscription<motor_control_interfaces::msg::MotorCommand>(
                "motor_command", 10, std::bind(&Motor_controller::motor_command_callback, this, _1)
                );
        }

    private:

        /**                         variablres                             **/ 
        // commande au moteur
        std::vector<Motor_command> motor_command_list;

        // Ros related
        rclcpp::Subscription<motor_control_interfaces::msg::MotorCommand>::SharedPtr subscription_motor_command_;
        // rclcpp::Publisher<motor_param>::SharedPtr publisher_motor_param_;

        /**                         fonction                              **/
        void motor_command_callback(const motor_control_interfaces::msg::MotorCommand::SharedPtr msg){
            
            std::cout << "coucou" << std::endl;
            
            for(auto & command : motor_command_list){
                if(command.name == msg->name){
                    switch (msg->mode) {
                    case 0: command.mode = Motor_mode::POSITION;
                    case 1: command.mode = Motor_mode::VELOCITY;
                    case 2: command.mode = Motor_mode::TORQUE;
                    default:;
                    }
                    command.command = msg->commande;

                    break;
                }
            }
        }
};

void worker()
{
    bool rtSuccess = true;
    for(const auto & master: configurator->getMasters())
    {
        rtSuccess &= master->setRealtimePriority(99);
    }
    std::cout << "Setting RT Priority: " << (rtSuccess? "successful." : "not successful. Check user privileges.") << std::endl;

    // Flag to set the drive state for the elmos on first startup
    bool maxonEnabledAfterStartup = false;

    /*
    ** The communication update loop.
    ** This loop is supposed to be executed at a constant rate.
    ** The EthercatMaster::update function incorporates a mechanism
    ** to create a constant rate.
     */
    while(!abrt)
    {
        /*
        ** Update each master.
        ** This sends tha last staged commands and reads the latest readings over EtherCAT.
        ** The StandaloneEnforceRate update mode is used.
        ** This means that average update rate will be close to the target rate (if possible).
         */
        for(const auto & master: configurator->getMasters() )
        {
            master->update(ecat_master::UpdateMode::StandaloneEnforceRate); // TODO fix the rate compensation (Elmo reliability problem)!!
        }



        /*
        ** Do things with the attached devices.
        ** Your lowlevel control input / measurement logic goes here.
        ** Different logic can be implemented for each device.
         */
        for(const auto & motor_command: motor_command_list) {
            
            // Keep constant update rate
            auto start_time = std::chrono::steady_clock::now();

            auto slave = configurator->getSlave(motor_command.name);

            std::shared_ptr<maxon::Maxon> maxon_slave_ptr = std::dynamic_pointer_cast<maxon::Maxon>(slave);

            if (!maxonEnabledAfterStartup)
            {
                // Set maxons to operation enabled state, do not block the call!
                maxon_slave_ptr->setDriveStateViaPdo(maxon::DriveState::OperationEnabled, false);
            }

            // set commands if we can
            if (maxon_slave_ptr->lastPdoStateChangeSuccessful() &&
                    maxon_slave_ptr->getReading().getDriveState() == maxon::DriveState::OperationEnabled)
            {
                maxon::Command command;
                    
                switch (motor_command.mode){
                case Motor_mode::POSITION:
                    command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousPositionMode);
                    command.setTargetPosition(motor_command.command);
                    break;
                case Motor_mode::VELOCITY:
                    command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousVelocityMode);
                    command.setTargetVelocity(motor_command.command);
                    break;
                case Motor_mode::TORQUE:
                    command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode);
                    command.setTargetTorque(motor_command.command);
                    break;
                default:
                    std::cerr << "Motor mode not recognized" << std::endl;
                    break;
                }
                maxon_slave_ptr->stageCommand(command);
            
            }
            else
            {
                MELO_WARN_STREAM("Maxon '" << maxon_slave_ptr->getName()
                                                                        << "': " << maxon_slave_ptr->getReading().getDriveState());
            }

            // Constant update rate
            std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1));
            
        }
        counter++;
        maxonEnabledAfterStartup = true;
    }
}


/*
** Handle the interrupt signal.
** This is the shutdown routine.
** Note: This logic is executed in a thread separated from the communication update!
 */
void signal_handler(int sig)
{
    /*
    ** Pre shutdown procedure.
    ** The devices execute procedures (e.g. state changes) that are necessary for a
    ** proper shutdown and that must be done with PDO communication.
    ** The communication update loop (i.e. PDO loop) continues to run!
    ** You might thus want to implement some logic that stages zero torque / velocity commands
    ** or simliar safety measures at this point using e.g. atomic variables and checking them
    ** in the communication update loop.
     */
    for(const auto & master: configurator->getMasters())
    {
        master->preShutdown();
    }

    // stop the PDO communication at the next update of the communication loop
    abrt = true;
    worker_thread->join();

    /*
    ** Completely halt the EtherCAT communication.
    ** No online communication is possible afterwards, including SDOs.
     */
    for(const auto & master: configurator->getMasters())
    {
        master->shutdown();
    }

    // Exit this executable
    std::cout << "Shutdown" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    exit(0);
}




/*
** Program entry.
** Pass the path to the setup.yaml file as first command line argument.
 */
int main(int argc, char**argv)
{
    // Set the abrt_ flag upon receiving an interrupt signal (e.g. Ctrl-c)
    std::signal(SIGINT, signal_handler);

    if(argc < 2)
    {
        std::cerr << "pass path to 'setup.yaml' as command line argument" << std::endl;
        return EXIT_FAILURE;
    }
    // a new EthercatDeviceConfigurator object (path to setup.yaml as constructor argument)
    configurator = std::make_shared<EthercatDeviceConfigurator>(argv[1]);

    /*
    ** Start all masters.
    ** There is exactly one bus per master which is also started.
    ** All online (i.e. SDO) configuration is done during this call.
    ** The EtherCAT interface is active afterwards, all drives are in Operational
    ** EtherCAT state and PDO communication may begin.
     */
    for(auto & master: configurator->getMasters())
    {
        if(!master->startup())
        {
            std::cerr << "Master Startup not successful." << std::endl;
            return EXIT_FAILURE;
        }
    }

    for (auto & slave: configurator->getSlaves())
    {
        motor_command_list.push_back(Motor_command(slave->getName(), Motor_mode::VELOCITY, 0.0));
    }

    // Start the PDO loop in a new thread.
    worker_thread = std::make_unique<std::thread>(&worker);

    /*
    ** Wait for a few PDO cycles to pass.
    ** Set anydrives into to ControlOp state (internal state machine, not EtherCAT states)
     */
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for(auto & slave: configurator->getSlaves())
    {
        std::cout << " " << slave->getName() << ": " << slave->getAddress() << std::endl;
    }

    std::cout << "Startup finished" << std::endl;
    // nothing further to do in this thread.


    rclcpp::init(argc, argv);

    auto node = std::make_shared<Motor_controller>();

    std::cout << "Node finished" << std::endl;

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}