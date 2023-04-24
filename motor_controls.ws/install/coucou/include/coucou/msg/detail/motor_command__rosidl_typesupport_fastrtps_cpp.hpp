// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from coucou:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef COUCOU__MSG__DETAIL__MOTOR_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define COUCOU__MSG__DETAIL__MOTOR_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "coucou/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "coucou/msg/detail/motor_command__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace coucou
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_coucou
cdr_serialize(
  const coucou::msg::MotorCommand & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_coucou
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  coucou::msg::MotorCommand & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_coucou
get_serialized_size(
  const coucou::msg::MotorCommand & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_coucou
max_serialized_size_MotorCommand(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace coucou

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_coucou
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, coucou, msg, MotorCommand)();

#ifdef __cplusplus
}
#endif

#endif  // COUCOU__MSG__DETAIL__MOTOR_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
