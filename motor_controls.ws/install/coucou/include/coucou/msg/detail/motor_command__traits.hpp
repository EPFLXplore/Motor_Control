// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from coucou:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef COUCOU__MSG__DETAIL__MOTOR_COMMAND__TRAITS_HPP_
#define COUCOU__MSG__DETAIL__MOTOR_COMMAND__TRAITS_HPP_

#include "coucou/msg/detail/motor_command__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<coucou::msg::MotorCommand>()
{
  return "coucou::msg::MotorCommand";
}

template<>
inline const char * name<coucou::msg::MotorCommand>()
{
  return "coucou/msg/MotorCommand";
}

template<>
struct has_fixed_size<coucou::msg::MotorCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<coucou::msg::MotorCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<coucou::msg::MotorCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COUCOU__MSG__DETAIL__MOTOR_COMMAND__TRAITS_HPP_
