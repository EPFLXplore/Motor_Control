// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_control_interfaces:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
#define MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_

#include "motor_control_interfaces/msg/detail/motor_command__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace motor_control_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorCommand_commande
{
public:
  explicit Init_MotorCommand_commande(::motor_control_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  ::motor_control_interfaces::msg::MotorCommand commande(::motor_control_interfaces::msg::MotorCommand::_commande_type arg)
  {
    msg_.commande = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_mode
{
public:
  explicit Init_MotorCommand_mode(::motor_control_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_commande mode(::motor_control_interfaces::msg::MotorCommand::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_MotorCommand_commande(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_name
{
public:
  Init_MotorCommand_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCommand_mode name(::motor_control_interfaces::msg::MotorCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_MotorCommand_mode(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_control_interfaces::msg::MotorCommand>()
{
  return motor_control_interfaces::msg::builder::Init_MotorCommand_name();
}

}  // namespace motor_control_interfaces

#endif  // MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
