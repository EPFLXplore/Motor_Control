// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ethercat_device_configurator:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
#define ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_

#include "ethercat_device_configurator/msg/detail/motor_command__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ethercat_device_configurator
{

namespace msg
{

namespace builder
{

class Init_MotorCommand_commande
{
public:
  explicit Init_MotorCommand_commande(::ethercat_device_configurator::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  ::ethercat_device_configurator::msg::MotorCommand commande(::ethercat_device_configurator::msg::MotorCommand::_commande_type arg)
  {
    msg_.commande = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorCommand msg_;
};

class Init_MotorCommand_mode
{
public:
  explicit Init_MotorCommand_mode(::ethercat_device_configurator::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_commande mode(::ethercat_device_configurator::msg::MotorCommand::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_MotorCommand_commande(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorCommand msg_;
};

class Init_MotorCommand_name
{
public:
  Init_MotorCommand_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCommand_mode name(::ethercat_device_configurator::msg::MotorCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_MotorCommand_mode(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ethercat_device_configurator::msg::MotorCommand>()
{
  return ethercat_device_configurator::msg::builder::Init_MotorCommand_name();
}

}  // namespace ethercat_device_configurator

#endif  // ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
