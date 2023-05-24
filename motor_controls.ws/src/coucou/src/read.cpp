#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "motor_control_interfaces/msg/motor_command.hpp"

#include <iostream>

using std::placeholders::_1;

#define S_CONST 60 * 1e6 / (2 * 3.1415)

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

      publisher_ = this->create_publisher<motor_control_interfaces::msg::MotorCommand>("motor_command", 10);
      
    }

  private:
    void topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg) const
    {
      std::cout << msg->axes[0] << " , " << msg->axes[1] << std::endl;

      auto message = motor_control_interfaces::msg::MotorCommand();

      message.name = "J1";
      message.mode = 1;
      message.commande = msg->axes[0]*800/S_CONST;
      
      publisher_->publish(message);


      message.name = "J2";
      message.commande = msg->axes[1] * 2/S_CONST;

      publisher_->publish(message);

      message.name = "J3";
      message.commande = msg->axes[3] * 1/S_CONST;
      
      publisher_->publish(message);

      message.name = "J4";
      message.commande = msg->axes[4] * 2/S_CONST;

      publisher_->publish(message);

      message.name = "J5";
      message.commande = (msg->buttons[4]==1? -1 : -1)(msg->axes[2] - 1)/2 * 2/S_CONST;

      publisher_->publish(message);
      
      message.name = "J6";
      message.commande = (msg->buttons[5]==1? -1 : -1)(msg->axes[5] - 1)/2 * 2/S_CONST;

      publisher_->publish(message);

    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<motor_control_interfaces::msg::MotorCommand>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}