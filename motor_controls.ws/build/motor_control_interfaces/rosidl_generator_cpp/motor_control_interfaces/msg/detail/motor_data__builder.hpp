// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_control_interfaces:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
#define MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_

#include "motor_control_interfaces/msg/detail/motor_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace motor_control_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorData_currant
{
public:
  explicit Init_MotorData_currant(::motor_control_interfaces::msg::MotorData & msg)
  : msg_(msg)
  {}
  ::motor_control_interfaces::msg::MotorData currant(::motor_control_interfaces::msg::MotorData::_currant_type arg)
  {
    msg_.currant = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorData msg_;
};

class Init_MotorData_velocity
{
public:
  explicit Init_MotorData_velocity(::motor_control_interfaces::msg::MotorData & msg)
  : msg_(msg)
  {}
  Init_MotorData_currant velocity(::motor_control_interfaces::msg::MotorData::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_MotorData_currant(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorData msg_;
};

class Init_MotorData_position
{
public:
  explicit Init_MotorData_position(::motor_control_interfaces::msg::MotorData & msg)
  : msg_(msg)
  {}
  Init_MotorData_velocity position(::motor_control_interfaces::msg::MotorData::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_MotorData_velocity(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorData msg_;
};

class Init_MotorData_name
{
public:
  Init_MotorData_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorData_position name(::motor_control_interfaces::msg::MotorData::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_MotorData_position(msg_);
  }

private:
  ::motor_control_interfaces::msg::MotorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_control_interfaces::msg::MotorData>()
{
  return motor_control_interfaces::msg::builder::Init_MotorData_name();
}

}  // namespace motor_control_interfaces

#endif  // MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
