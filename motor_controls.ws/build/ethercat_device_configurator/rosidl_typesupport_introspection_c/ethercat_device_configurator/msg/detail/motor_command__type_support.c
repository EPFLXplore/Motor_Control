// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ethercat_device_configurator:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ethercat_device_configurator/msg/detail/motor_command__rosidl_typesupport_introspection_c.h"
#include "ethercat_device_configurator/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ethercat_device_configurator/msg/detail/motor_command__functions.h"
#include "ethercat_device_configurator/msg/detail/motor_command__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ethercat_device_configurator__msg__MotorCommand__init(message_memory);
}

void MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_fini_function(void * message_memory)
{
  ethercat_device_configurator__msg__MotorCommand__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_member_array[3] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ethercat_device_configurator__msg__MotorCommand, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ethercat_device_configurator__msg__MotorCommand, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "commande",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ethercat_device_configurator__msg__MotorCommand, commande),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_members = {
  "ethercat_device_configurator__msg",  // message namespace
  "MotorCommand",  // message name
  3,  // number of fields
  sizeof(ethercat_device_configurator__msg__MotorCommand),
  MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_member_array,  // message members
  MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_type_support_handle = {
  0,
  &MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ethercat_device_configurator
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ethercat_device_configurator, msg, MotorCommand)() {
  if (!MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_type_support_handle.typesupport_identifier) {
    MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &MotorCommand__rosidl_typesupport_introspection_c__MotorCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
