// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ethercat_device_configurator:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
#define ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_

#include "ethercat_device_configurator/msg/detail/motor_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ethercat_device_configurator
{

namespace msg
{

namespace builder
{

class Init_MotorData_currant
{
public:
  explicit Init_MotorData_currant(::ethercat_device_configurator::msg::MotorData & msg)
  : msg_(msg)
  {}
  ::ethercat_device_configurator::msg::MotorData currant(::ethercat_device_configurator::msg::MotorData::_currant_type arg)
  {
    msg_.currant = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorData msg_;
};

class Init_MotorData_velocity
{
public:
  explicit Init_MotorData_velocity(::ethercat_device_configurator::msg::MotorData & msg)
  : msg_(msg)
  {}
  Init_MotorData_currant velocity(::ethercat_device_configurator::msg::MotorData::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_MotorData_currant(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorData msg_;
};

class Init_MotorData_position
{
public:
  explicit Init_MotorData_position(::ethercat_device_configurator::msg::MotorData & msg)
  : msg_(msg)
  {}
  Init_MotorData_velocity position(::ethercat_device_configurator::msg::MotorData::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_MotorData_velocity(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorData msg_;
};

class Init_MotorData_name
{
public:
  Init_MotorData_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorData_position name(::ethercat_device_configurator::msg::MotorData::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_MotorData_position(msg_);
  }

private:
  ::ethercat_device_configurator::msg::MotorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ethercat_device_configurator::msg::MotorData>()
{
  return ethercat_device_configurator::msg::builder::Init_MotorData_name();
}

}  // namespace ethercat_device_configurator

#endif  // ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
