// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from umv_msgs:msg/GlobalPath.idl
// generated code does not contain a copyright notice
#include "umv_msgs/msg/detail/global_path__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `global_xs`
// Member `global_ys`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
umv_msgs__msg__GlobalPath__init(umv_msgs__msg__GlobalPath * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    umv_msgs__msg__GlobalPath__fini(msg);
    return false;
  }
  // global_xs
  if (!rosidl_runtime_c__double__Sequence__init(&msg->global_xs, 0)) {
    umv_msgs__msg__GlobalPath__fini(msg);
    return false;
  }
  // global_ys
  if (!rosidl_runtime_c__double__Sequence__init(&msg->global_ys, 0)) {
    umv_msgs__msg__GlobalPath__fini(msg);
    return false;
  }
  // distance_interval
  return true;
}

void
umv_msgs__msg__GlobalPath__fini(umv_msgs__msg__GlobalPath * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // global_xs
  rosidl_runtime_c__double__Sequence__fini(&msg->global_xs);
  // global_ys
  rosidl_runtime_c__double__Sequence__fini(&msg->global_ys);
  // distance_interval
}

bool
umv_msgs__msg__GlobalPath__are_equal(const umv_msgs__msg__GlobalPath * lhs, const umv_msgs__msg__GlobalPath * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // global_xs
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->global_xs), &(rhs->global_xs)))
  {
    return false;
  }
  // global_ys
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->global_ys), &(rhs->global_ys)))
  {
    return false;
  }
  // distance_interval
  if (lhs->distance_interval != rhs->distance_interval) {
    return false;
  }
  return true;
}

bool
umv_msgs__msg__GlobalPath__copy(
  const umv_msgs__msg__GlobalPath * input,
  umv_msgs__msg__GlobalPath * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // global_xs
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->global_xs), &(output->global_xs)))
  {
    return false;
  }
  // global_ys
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->global_ys), &(output->global_ys)))
  {
    return false;
  }
  // distance_interval
  output->distance_interval = input->distance_interval;
  return true;
}

umv_msgs__msg__GlobalPath *
umv_msgs__msg__GlobalPath__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__GlobalPath * msg = (umv_msgs__msg__GlobalPath *)allocator.allocate(sizeof(umv_msgs__msg__GlobalPath), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(umv_msgs__msg__GlobalPath));
  bool success = umv_msgs__msg__GlobalPath__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
umv_msgs__msg__GlobalPath__destroy(umv_msgs__msg__GlobalPath * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    umv_msgs__msg__GlobalPath__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
umv_msgs__msg__GlobalPath__Sequence__init(umv_msgs__msg__GlobalPath__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__GlobalPath * data = NULL;

  if (size) {
    data = (umv_msgs__msg__GlobalPath *)allocator.zero_allocate(size, sizeof(umv_msgs__msg__GlobalPath), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = umv_msgs__msg__GlobalPath__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        umv_msgs__msg__GlobalPath__fini(&data[i - 1]);
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
umv_msgs__msg__GlobalPath__Sequence__fini(umv_msgs__msg__GlobalPath__Sequence * array)
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
      umv_msgs__msg__GlobalPath__fini(&array->data[i]);
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

umv_msgs__msg__GlobalPath__Sequence *
umv_msgs__msg__GlobalPath__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__GlobalPath__Sequence * array = (umv_msgs__msg__GlobalPath__Sequence *)allocator.allocate(sizeof(umv_msgs__msg__GlobalPath__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = umv_msgs__msg__GlobalPath__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
umv_msgs__msg__GlobalPath__Sequence__destroy(umv_msgs__msg__GlobalPath__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    umv_msgs__msg__GlobalPath__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
umv_msgs__msg__GlobalPath__Sequence__are_equal(const umv_msgs__msg__GlobalPath__Sequence * lhs, const umv_msgs__msg__GlobalPath__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!umv_msgs__msg__GlobalPath__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
umv_msgs__msg__GlobalPath__Sequence__copy(
  const umv_msgs__msg__GlobalPath__Sequence * input,
  umv_msgs__msg__GlobalPath__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(umv_msgs__msg__GlobalPath);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    umv_msgs__msg__GlobalPath * data =
      (umv_msgs__msg__GlobalPath *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!umv_msgs__msg__GlobalPath__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          umv_msgs__msg__GlobalPath__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!umv_msgs__msg__GlobalPath__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
