// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_control_interfaces:msg/MotorData.idl
// generated code does not contain a copyright notice
#include "motor_control_interfaces/msg/detail/motor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
motor_control_interfaces__msg__MotorData__init(motor_control_interfaces__msg__MotorData * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    motor_control_interfaces__msg__MotorData__fini(msg);
    return false;
  }
  // position
  // velocity
  // currant
  return true;
}

void
motor_control_interfaces__msg__MotorData__fini(motor_control_interfaces__msg__MotorData * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // position
  // velocity
  // currant
}

bool
motor_control_interfaces__msg__MotorData__are_equal(const motor_control_interfaces__msg__MotorData * lhs, const motor_control_interfaces__msg__MotorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // currant
  if (lhs->currant != rhs->currant) {
    return false;
  }
  return true;
}

bool
motor_control_interfaces__msg__MotorData__copy(
  const motor_control_interfaces__msg__MotorData * input,
  motor_control_interfaces__msg__MotorData * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // position
  output->position = input->position;
  // velocity
  output->velocity = input->velocity;
  // currant
  output->currant = input->currant;
  return true;
}

motor_control_interfaces__msg__MotorData *
motor_control_interfaces__msg__MotorData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control_interfaces__msg__MotorData * msg = (motor_control_interfaces__msg__MotorData *)allocator.allocate(sizeof(motor_control_interfaces__msg__MotorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_control_interfaces__msg__MotorData));
  bool success = motor_control_interfaces__msg__MotorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_control_interfaces__msg__MotorData__destroy(motor_control_interfaces__msg__MotorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_control_interfaces__msg__MotorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_control_interfaces__msg__MotorData__Sequence__init(motor_control_interfaces__msg__MotorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control_interfaces__msg__MotorData * data = NULL;

  if (size) {
    data = (motor_control_interfaces__msg__MotorData *)allocator.zero_allocate(size, sizeof(motor_control_interfaces__msg__MotorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_control_interfaces__msg__MotorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_control_interfaces__msg__MotorData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
motor_control_interfaces__msg__MotorData__Sequence__fini(motor_control_interfaces__msg__MotorData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      motor_control_interfaces__msg__MotorData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

motor_control_interfaces__msg__MotorData__Sequence *
motor_control_interfaces__msg__MotorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control_interfaces__msg__MotorData__Sequence * array = (motor_control_interfaces__msg__MotorData__Sequence *)allocator.allocate(sizeof(motor_control_interfaces__msg__MotorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_control_interfaces__msg__MotorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_control_interfaces__msg__MotorData__Sequence__destroy(motor_control_interfaces__msg__MotorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_control_interfaces__msg__MotorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_control_interfaces__msg__MotorData__Sequence__are_equal(const motor_control_interfaces__msg__MotorData__Sequence * lhs, const motor_control_interfaces__msg__MotorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_control_interfaces__msg__MotorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_control_interfaces__msg__MotorData__Sequence__copy(
  const motor_control_interfaces__msg__MotorData__Sequence * input,
  motor_control_interfaces__msg__MotorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_control_interfaces__msg__MotorData);
    motor_control_interfaces__msg__MotorData * data =
      (motor_control_interfaces__msg__MotorData *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_control_interfaces__msg__MotorData__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          motor_control_interfaces__msg__MotorData__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_control_interfaces__msg__MotorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
