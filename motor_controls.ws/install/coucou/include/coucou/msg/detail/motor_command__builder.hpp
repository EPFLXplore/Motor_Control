// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from coucou:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef COUCOU__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
#define COUCOU__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_

#include "coucou/msg/detail/motor_command__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace coucou
{

namespace msg
{

namespace builder
{

class Init_MotorCommand_commande
{
public:
  explicit Init_MotorCommand_commande(::coucou::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  ::coucou::msg::MotorCommand commande(::coucou::msg::MotorCommand::_commande_type arg)
  {
    msg_.commande = std::move(arg);
    return std::move(msg_);
  }

private:
  ::coucou::msg::MotorCommand msg_;
};

class Init_MotorCommand_mode
{
public:
  explicit Init_MotorCommand_mode(::coucou::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_commande mode(::coucou::msg::MotorCommand::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_MotorCommand_commande(msg_);
  }

private:
  ::coucou::msg::MotorCommand msg_;
};

class Init_MotorCommand_name
{
public:
  Init_MotorCommand_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCommand_mode name(::coucou::msg::MotorCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_MotorCommand_mode(msg_);
  }

private:
  ::coucou::msg::MotorCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::coucou::msg::MotorCommand>()
{
  return coucou::msg::builder::Init_MotorCommand_name();
}

}  // namespace coucou

#endif  // COUCOU__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
