// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from coucou:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef COUCOU__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_
#define COUCOU__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_

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

// Struct defined in msg/MotorCommand in the package coucou.
typedef struct coucou__msg__MotorCommand
{
  rosidl_runtime_c__String name;
  uint8_t mode;
  double commande;
} coucou__msg__MotorCommand;

// Struct for a sequence of coucou__msg__MotorCommand.
typedef struct coucou__msg__MotorCommand__Sequence
{
  coucou__msg__MotorCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} coucou__msg__MotorCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COUCOU__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_
