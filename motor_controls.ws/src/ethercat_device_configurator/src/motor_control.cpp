#include "ethercat_device_configurator/EthercatDeviceConfigurator.hpp"
#include <maxon_epos_ethercat_sdk/Maxon.hpp>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class motor_controller : public rclcpp::Node
{
    public:
        motor_controller()
        : Node("motor_controller")
        {
            // init the node
        }

        ~motor_controller()
        {
            // end the com and node
        }

    private:
        
        void update(){
            // update the motor at a constant rate
        }

        void motor_command_callback(const std_msgs::msg::Float64::SharedPtr msg){
            // get the command from the topic
        }

}