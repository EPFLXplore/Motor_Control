#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "motor_control_interface/msg/motor_control.hpp"

#include <iostream>

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

      publisher_ = this->create_publisher<motor_control_interface::msg::MotorControl>("hd_motor_command", 10);
      
    }

  private:
    void topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg) const
    {
      std::cout << msg->axes[0] << " , " << msg->axes[1] << std::endl;

      auto message = motor_control_interface::msg::MotorControl();

      message.name = "J1";
      message.mode = 1;
      message.commande = msg->axes[0];

      publisher_->publish(message);

      // message.name = "J2";
      // message.mode = 1;
      // message.commande = msg->axes[1];

      // message.name = "J3";
      // message.mode = 1;
      // message.commande = msg->axes[3];

      // message.name = "J4";
      // message.mode = 1;
      // message.commande = msg->axes[0];

      // message.name = "J5";
      // message.mode = 1;
      // message.commande = msg->axes[0];

    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<motor_control_interface::msg::MotorControl>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}