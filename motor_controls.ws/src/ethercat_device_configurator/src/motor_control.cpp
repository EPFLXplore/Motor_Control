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