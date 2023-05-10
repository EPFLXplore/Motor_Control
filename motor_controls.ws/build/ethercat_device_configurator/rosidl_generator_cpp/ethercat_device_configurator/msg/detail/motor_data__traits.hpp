// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ethercat_device_configurator:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_
#define ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_

#include "ethercat_device_configurator/msg/detail/motor_data__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ethercat_device_configurator::msg::MotorData>()
{
  return "ethercat_device_configurator::msg::MotorData";
}

template<>
inline const char * name<ethercat_device_configurator::msg::MotorData>()
{
  return "ethercat_device_configurator/msg/MotorData";
}

template<>
struct has_fixed_size<ethercat_device_configurator::msg::MotorData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ethercat_device_configurator::msg::MotorData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ethercat_device_configurator::msg::MotorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__TRAITS_HPP_
