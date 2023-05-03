// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_control_interfaces:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
#define MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/MotorData in the package motor_control_interfaces.
typedef struct motor_control_interfaces__msg__MotorData
{
  rosidl_runtime_c__String name;
  double position;
  double velocity;
  double currant;
} motor_control_interfaces__msg__MotorData;

// Struct for a sequence of motor_control_interfaces__msg__MotorData.
typedef struct motor_control_interfaces__msg__MotorData__Sequence
{
  motor_control_interfaces__msg__MotorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_control_interfaces__msg__MotorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_CONTROL_INTERFACES__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
