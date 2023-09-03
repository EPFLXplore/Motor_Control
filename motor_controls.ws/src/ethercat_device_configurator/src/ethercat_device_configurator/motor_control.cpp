#include "EthercatDeviceConfigurator.hpp"
#include <maxon_epos_ethercat_sdk/Maxon.hpp>

#include "rclcpp/rclcpp.hpp"
#include "motor_control_interfaces/msg/motor_command.hpp"
#include "motor_control_interfaces/msg/motor_data.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/int8.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

#include <iostream>
#include <thread>
#include <csignal>
#include <string>
#include <vector>

#define TIME_CONTDOWN 100ms

using namespace std::chrono_literals;

using std::placeholders::_1;

enum Motor_mode
{
    POSITION = 0,
    VELOCITY = 1,
    TORQUE = 2
};

struct Motor_command
{
    std::string name;
    maxon::Command command;
    std::chrono::steady_clock::time_point command_time;
    double max_velocity = 0;
    double pos_lower_limit = 0;
    double pos_upper_limit = 0;

    Motor_command(std::string name, maxon::Command command, std::chrono::steady_clock::time_point command_time) : name(name), command(command), command_time(command_time) {}
};

static const double PI = 3.14159265359;
static const double INF = 1e10;
static const std::vector<std::string> DEVICE_NAMES = {"J1", "J2", "J3", "J4", "J5", "J6", "Gripper", "Rassor"};
static const std::vector<double> MAX_VELOCITIES = {0.2, 0.5, 0.3, 0.3, 0.15, 0.3, 4, 1};
static const std::vector<double> POS_LOWER_LIMITS = {-PI, -PI/2, -PI/4, -PI, -PI/2, -PI, -INF};
static const std::vector<double> POS_UPPER_LIMITS = {PI, PI/2, PI/4, PI, PI/2, PI, INF};

static const std::vector<double> REDUCTIONS = {-1.0/128, 1.0/2, 1.0, -4.0, 1.0, 1.0/64, 1.0, 1.0}; // should all be 1 but are not

std::vector<Motor_command> motor_command_list;

std::unique_ptr<std::thread> worker_thread;
bool abrt = false;

EthercatDeviceConfigurator::SharedPtr configurator;

unsigned int counter = 0;

void signal_handler(int sig);

class Motor_controller : public rclcpp::Node
{
public:
    Motor_controller()
        : Node("Motor_controller")
    {
        // MATTHIAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        subscription_velocity_command_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "HD/fsm/joint_vel_cmd", 10, std::bind(&Motor_controller::velocity_command_callback, this, _1));
        subscription_position_command_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "HD/kinematics/joint_pos_cmd", 10, std::bind(&Motor_controller::position_command_callback, this, _1));
        subscription_single_motor_command_ = this->create_subscription<motor_control_interfaces::msg::MotorCommand>(
            "HD/kinematics/single_joint_cmd", 10, std::bind(&Motor_controller::motor_command_callback, this, _1));
        subscription_shutdown_ = this->create_subscription<std_msgs::msg::Int8>(
            "ROVER/shutdown", 10, std::bind(&Motor_controller::kill, this, _1));
        publisher_state_ = this->create_publisher<sensor_msgs::msg::JointState>("HD/motor_control/joint_telemetry", 10);
        timer_motor_data_ = this->create_wall_timer(
            10ms, std::bind(&Motor_controller::publish_state, this));
        // MATTHIAS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    }

private:
    /**                         variablres                             **/
    // commande au moteur
    // std::vector<Motor_command> motor_command_list;

    // Ros related

    // MATTHIAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_velocity_command_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_position_command_;
    rclcpp::Subscription<motor_control_interfaces::msg::MotorCommand>::SharedPtr subscription_single_motor_command_;
    rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr subscription_shutdown_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_state_;
    // MATTHIAS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    rclcpp::TimerBase::SharedPtr timer_motor_data_;

    // MATTHIAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void velocity_command_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
        for (uint i=0; i < motor_command_list.size(); i++) {
            if (motor_command_list[i].name == "Gripper") {     // TODO: remove the 1 once motors are correctly tuned in velocity
                motor_command_list[i].command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode);
                motor_command_list[i].command.setTargetTorque(msg->data[i]*motor_command_list[i].max_velocity);//*0.1);     // a bit ugly to use max velocity here when really it is a max torque
                motor_command_list[i].command_time = std::chrono::steady_clock::now();
            }
            else {
                motor_command_list[i].command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousVelocityMode);
                motor_command_list[i].command.setTargetVelocity(motor_command_list[i].max_velocity * msg->data[i]);
                motor_command_list[i].command_time = std::chrono::steady_clock::now();
            }
        }
    }

    void position_command_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
    {
        for (uint i = 0; i < 6; i++)     // only accepting position commands for j1-6
        {
            motor_command_list[i].command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousPositionMode);
            double new_pos = msg->data[i];
            //new_pos = std::min(std::max(new_pos, POS_LOWER_LIMITS[i]), POS_UPPER_LIMITS[i]);
            if (new_pos < POS_LOWER_LIMITS[i]) new_pos = POS_LOWER_LIMITS[i];
            if (new_pos > POS_UPPER_LIMITS[i]) new_pos = POS_UPPER_LIMITS[i];
            motor_command_list[i].command.setTargetPosition(new_pos / REDUCTIONS[i]);
            motor_command_list[i].command_time = std::chrono::steady_clock::now();
        }
    }

    void publish_state()
    {
        sensor_msgs::msg::JointState msg;
        for (size_t i = 0; i < motor_command_list.size(); i++)
        {
            auto slave = configurator->getSlave(DEVICE_NAMES[i]);
            std::shared_ptr<maxon::Maxon> maxon_slave_ptr = std::dynamic_pointer_cast<maxon::Maxon>(slave);

            msg.name.push_back(slave->getName());

            auto getReading = maxon_slave_ptr->getReading();
            msg.position.push_back(getReading.getActualPosition() * REDUCTIONS[i]);
            msg.velocity.push_back(getReading.getActualVelocity());
            msg.effort.push_back(getReading.getActualCurrent());
        }
        publisher_state_->publish(msg);
    }

    void kill(const std_msgs::msg::Int8::SharedPtr msg)
    {
        signal_handler(0);
        rclcpp::shutdown();
    }
    // MATTHIAS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    void motor_command_callback(const motor_control_interfaces::msg::MotorCommand::SharedPtr msg)
    {

        for (auto &motor_command : motor_command_list)
        {

            if (motor_command.name == msg->name)
            {
                switch (msg->mode)
                {
                case Motor_mode::POSITION:
                    motor_command.command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousPositionMode);
                    motor_command.command.setTargetPosition(msg->command);
                    break;
                case Motor_mode::VELOCITY:
                    motor_command.command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousVelocityMode);
                    motor_command.command.setTargetVelocity(motor_command.max_velocity * msg->command);
                    break;
                case Motor_mode::TORQUE:
                    motor_command.command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode);
                    motor_command.command.setTargetTorque(msg->command);
                    break;
                default:
                    std::cerr << "Motor mode not recognized" << std::endl;
                    break;
                }
                motor_command.command_time = std::chrono::steady_clock::now();

                return;
            }
        }
    }
};

void reorder_command_list()
{
    // sorting motor_command_list by real order of motors in the arm
    for (int i = 0; i < motor_command_list.size(); i++)
    {
        for (int j = i; j < motor_command_list.size(); j++)
        {
            if (motor_command_list[j].name == DEVICE_NAMES[i])
            {
                if (i != j)
                {
                    auto temp = motor_command_list[i];
                    motor_command_list[i] = motor_command_list[j];
                    motor_command_list[j] = temp;
                }
                break;
            }
        }
    }
}

void setup_command_list()
{
    reorder_command_list();
    for (int i = 0; i < motor_command_list.size(); i++)
    {
        motor_command_list[i].max_velocity = MAX_VELOCITIES[i];
        motor_command_list[i].pos_lower_limit = POS_LOWER_LIMITS[i];
        motor_command_list[i].pos_upper_limit = POS_UPPER_LIMITS[i];
    }
}

void enforce_limits(Motor_command &command)
{
    switch (command.command.getModeOfOperation())
    {
    case maxon::ModeOfOperationEnum::CyclicSynchronousPositionMode:
        // Not Implemented
        break;
    case maxon::ModeOfOperationEnum::CyclicSynchronousVelocityMode:
        // Not Implemented
        break;
    case maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode:
        // Not Implemented
        break;
    }
}

void worker()
{
    bool rtSuccess = true;
    for (const auto &master : configurator->getMasters())
    {
        rtSuccess &= master->setRealtimePriority(99);
    }
    std::cout << "Setting RT Priority: " << (rtSuccess ? "successful." : "not successful. Check user privileges.") << std::endl;

    // Flag to set the drive state for the elmos on first startup
    bool maxonEnabledAfterStartup = false;

    /*
    ** The communication update loop.
    ** This loop is supposed to be executed at a constant rate.
    ** The EthercatMaster::update function incorporates a mechanism
    ** to create a constant rate.
    */
    while (!abrt)
    {
        /*
        ** Update each master.
        ** This sends tha last staged commands and reads the latest readings over EtherCAT.
        ** The StandaloneEnforceRate update mode is used.
        ** This means that average update rate will be close to the target rate (if possible).
        */
        for (const auto &master : configurator->getMasters())
        {
            master->update(ecat_master::UpdateMode::StandaloneEnforceRate); // TODO fix the rate compensation (Elmo reliability problem)!!
        }

        /*
        ** Do things with the attached devices.
        ** Your lowlevel control input / measurement logic goes here.
        ** Different logic can be implemented for each device.
        */
        for (auto &motor_command : motor_command_list)
        {

            // Keep constant update rate
            // std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

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
                if (std::chrono::steady_clock::now() - motor_command.command_time >= TIME_CONTDOWN)
                {
                    motor_command.command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode);
                    motor_command.command.setTargetTorque(0.0);
                }
                enforce_limits(motor_command);
                maxon_slave_ptr->stageCommand(motor_command.command);
            }
            else
            {
                MELO_WARN_STREAM("Maxon '" << maxon_slave_ptr->getName()
                                           << "': " << maxon_slave_ptr->getReading().getDriveState());
            }

            // Constant update rate
            // std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1));
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
    for (const auto &master : configurator->getMasters())
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
    for (const auto &master : configurator->getMasters())
    {
        master->shutdown();
    }

    // Exit this executable
    std::cout << "Shutdown" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    exit(0);
}


/*
spin file as first command line argument.
 */
int main(int argc, char**argv)
{
    // Set the abrt_ flag upon receiving an interrupt signal (e.g. Ctrl-c)
    std::signal(SIGINT, signal_handler);

    if (argc < 2)
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
    for (auto &master : configurator->getMasters())
    {
        if (!master->startup())
        {
            std::cerr << "Master Startup not successful." << std::endl;
            return EXIT_FAILURE;
        }
    }

    maxon::Command command;
    command.setModeOfOperation(maxon::ModeOfOperationEnum::CyclicSynchronousTorqueMode);
    command.setTargetTorque(0.0);

    for (auto &slave : configurator->getSlaves())
    {
        motor_command_list.push_back(Motor_command({slave->getName(), command, std::chrono::steady_clock::now()}));
        std::cout << slave->getName() << std::endl;
    }
    setup_command_list();

    // Start the PDO loop in a new thread.
    worker_thread = std::make_unique<std::thread>(&worker);

    /*
    ** Wait for a few PDO cycles to pass.
    ** Set anydrives into to ControlOp state (internal state machine, not EtherCAT states)
    */
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for (auto &slave : configurator->getSlaves())
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