// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ethercat_device_configurator:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_
#define ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_

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

// Struct defined in msg/MotorCommand in the package ethercat_device_configurator.
typedef struct ethercat_device_configurator__msg__MotorCommand
{
  rosidl_runtime_c__String name;
  uint8_t mode;
  double commande;
} ethercat_device_configurator__msg__MotorCommand;

// Struct for a sequence of ethercat_device_configurator__msg__MotorCommand.
typedef struct ethercat_device_configurator__msg__MotorCommand__Sequence
{
  ethercat_device_configurator__msg__MotorCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ethercat_device_configurator__msg__MotorCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_
