#include "ethercat_device_configurator/EthercatDeviceConfigurator.hpp"
#include <maxon_epos_ethercat_sdk/Maxon.hpp>

#include "rclcpp/rclcpp.hpp"
#include "motor_control_interfaces/msg/motor_command.hpp"

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

class Motor_controller : public rclcpp::Node
{
    public:
        Motor_controller(int argc, char**argv)
        : Node("Motor_controller")
        {
            if(argc < 2)
            {
                std::cerr << "pass path to 'setup.yaml' as command line argument" << std::endl;
                // return EXIT_FAILURE;
            }
            // a new EthercatDeviceConfigurator object (path to setup.yaml as constructor argument)
            configurator_ = std::make_shared<EthercatDeviceConfigurator>(argv[1]);

            /*
            ** Start all masters.
            ** There is exactly one bus per master which is also started.
            ** All online (i.e. SDO) configuration is done during this call.
            ** The EtherCAT interface is active afterwards, all drives are in Operational
            ** EtherCAT state and PDO communication may begin.
            */
            for(auto & master: configurator_->getMasters())
            {
                if(!master->startup())
                {
                    std::cerr << "Master Startup not successful." << std::endl;
                    // return EXIT_FAILURE;
                }
            }

            for(auto & slave: configurator_->getSlaves()){
                motor_command_list.push_back({slave->getName(), Motor_mode::VELOCITY, 0.0});
            }

            // Start the PDO loop in a new thread.

            bool rtSuccess = true;
            for(const auto & master: configurator_->getMasters())
            {
                rtSuccess &= master->setRealtimePriority(99);
            }
            std::cout << "Setting RT Priority: " << (rtSuccess? "successful." : "not successful. Check user privileges.") << std::endl;

            // Flag to set the drive state for the elmos on first startup
            maxonEnabledAfterStartup_ = false;

            timer_update_motor_ = this->create_wall_timer(500ms, std::bind(&Motor_controller::update_motor, this));
            
            subscription_motor_command_ = this->create_subscription<motor_control_interfaces::msg::MotorCommand>(
                "motor_command", 10, std::bind(&Motor_controller::motor_command_callback, this, _1)
                );


            


            /*
            ** Wait for a few PDO cycles to pass.
            ** Set anydrives into to ControlOp state (internal state machine, not EtherCAT states)
            */
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
            for(auto & slave: configurator_->getSlaves())
            {
                std::cout << " " << slave->getName() << ": " << slave->getAddress() << std::endl;
            }

            

            std::cout << "Startup finished" << std::endl;
        }

        ~Motor_controller()
        {
            for(const auto & master: configurator_->getMasters())
            {
                master->preShutdown();
            }

            /*
            ** Completely halt the EtherCAT communication.
            ** No online communication is possible afterwards, including SDOs.
            */
            for(const auto & master: configurator_->getMasters())
            {
                master->shutdown();
            }

            // Exit this executable
            std::cout << "Shutdown" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            exit(0);
        }

    private:

        /**                         variablres                             **/ 
        // bool abrt = false;
        EthercatDeviceConfigurator::SharedPtr configurator_;

        bool maxonEnabledAfterStartup_ = false;
        
        // commande au moteur
        std::vector<Motor_command> motor_command_list;

        // Ros related
        rclcpp::TimerBase::SharedPtr timer_update_motor_;
        rclcpp::Subscription<motor_control_interfaces::msg::MotorCommand>::SharedPtr subscription_motor_command_;
        // rclcpp::Publisher<motor_param>::SharedPtr publisher_motor_param_;


        /**                         fonction                              **/
        void update_motor(){
            /*
            ** Update each master.
            ** This sends tha last staged commands and reads the latest readings over EtherCAT.
            ** The StandaloneEnforceRate update mode is used.
            ** This means that average update rate will be close to the target rate (if possible).
            */
            for(const auto & master: configurator_->getMasters())
            {
                master->update(ecat_master::UpdateMode::StandaloneEnforceRate); // TODO fix the rate compensation (Elmo reliability problem)!!
            }

            /*
            ** Do things with the attached devices.
            ** Your lowlevel control input / measurement logic goes here.
            ** Different logic can be implemented for each device.
            */
            for(const auto & motor_command: motor_command_list) {

                // Get the slave object
                auto slave = configurator_->getSlave(motor_command.name);

                std::shared_ptr<maxon::Maxon> maxon_slave_ptr = std::dynamic_pointer_cast<maxon::Maxon>(slave);

                if (!maxonEnabledAfterStartup_)
                {
                    // Set maxons to operation enabled state, do not block the call!
                    maxonEnabledAfterStartup_ = maxon_slave_ptr->setDriveStateViaPdo(maxon::DriveState::OperationEnabled, false);
                }

                // Maxon
                if (configurator_->getInfoForSlave(slave).type == EthercatDeviceConfigurator::EthercatSlaveType::Maxon)
                {
                    if (!maxonEnabledAfterStartup_)
                    {
                        // Set maxons to operation enabled state, do not block the call!
                        maxon_slave_ptr->setDriveStateViaPdo(maxon::DriveState::OperationEnabled, true);
                    }

                    // set commands if we can
                    if (maxon_slave_ptr->lastPdoStateChangeSuccessful() &&
                            maxon_slave_ptr->getReading().getDriveState() == maxon::DriveState::OperationEnabled)
                    {
                        maxon::Command command;
                        
                        if (motor_command.mode == Motor_mode::POSITION){
                            command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousPositionMode);
                            command.setTargetPosition(motor_command.command);
                        }
                        else if (motor_command.mode == Motor_mode::VELOCITY){
                            command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousVelocityMode);
                            command.setTargetVelocity(motor_command.command);
                        }
                        else if (motor_command.mode == Motor_mode::TORQUE){
                            command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode);
                            command.setTargetTorque(motor_command.command);
                        }
                        else{
                            std::cerr << "Motor mode not recognized" << std::endl;
                        }
                        maxon_slave_ptr->stageCommand(command);
                        
                    }
                    else
                    {
                        MELO_WARN_STREAM("Maxon '" << maxon_slave_ptr->getName()
                                                << "': " << maxon_slave_ptr->getReading().getDriveState());
                    }
                }
            }
            // maxonEnabledAfterStartup_ = true;
        }

        void motor_command_callback(const motor_control_interfaces::msg::MotorCommand::SharedPtr msg){
            for(auto & command : motor_command_list){
                if(command.name == msg->name){
                    switch (msg->mode)
                    {
                    case 0: command.mode = Motor_mode::POSITION; break;
                    case 1: command.mode = Motor_mode::VELOCITY; break;
                    case 2: command.mode = Motor_mode::TORQUE; break;
                    default: break;
                    }
                    command.command = msg->commande;
                    break;
                }
            }
        }



};

int main(int argc, char**argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Motor_controller>(argc, argv));
  rclcpp::shutdown();
  return 0;
}