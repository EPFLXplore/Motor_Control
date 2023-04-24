#include <memory>

#include "rclcpp/rclcpp.hpp"


#include <iostream>

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<Motor_Command>(
      "hd_motor_command", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const Motor_Command::SharedPtr msg) const
    {
      std::cout << msg->name << std::endl;
    }
    rclcpp::Subscription<Motor_Command>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}