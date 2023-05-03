// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_control_interfaces:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_
#define MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_

#include "motor_control_interfaces/msg/detail/motor_data__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<motor_control_interfaces::msg::MotorData>()
{
  return "motor_control_interfaces::msg::MotorData";
}

template<>
inline const char * name<motor_control_interfaces::msg::MotorData>()
{
  return "motor_control_interfaces/msg/MotorData";
}

template<>
struct has_fixed_size<motor_control_interfaces::msg::MotorData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motor_control_interfaces::msg::MotorData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motor_control_interfaces::msg::MotorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_
