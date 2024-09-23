// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice
#include "umv_msgs/msg/detail/obstacles__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `obs_xs`
// Member `obs_ys`
// Member `obs_ss`
// Member `obs_eys`
// Member `obs_eyaws`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
umv_msgs__msg__Obstacles__init(umv_msgs__msg__Obstacles * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    umv_msgs__msg__Obstacles__fini(msg);
    return false;
  }
  // obs_cnt
  // obs_xs
  if (!rosidl_runtime_c__double__Sequence__init(&msg->obs_xs, 0)) {
    umv_msgs__msg__Obstacles__fini(msg);
    return false;
  }
  // obs_ys
  if (!rosidl_runtime_c__double__Sequence__init(&msg->obs_ys, 0)) {
    umv_msgs__msg__Obstacles__fini(msg);
    return false;
  }
  // obs_ss
  if (!rosidl_runtime_c__double__Sequence__init(&msg->obs_ss, 0)) {
    umv_msgs__msg__Obstacles__fini(msg);
    return false;
  }
  // obs_eys
  if (!rosidl_runtime_c__double__Sequence__init(&msg->obs_eys, 0)) {
    umv_msgs__msg__Obstacles__fini(msg);
    return false;
  }
  // obs_eyaws
  if (!rosidl_runtime_c__double__Sequence__init(&msg->obs_eyaws, 0)) {
    umv_msgs__msg__Obstacles__fini(msg);
    return false;
  }
  return true;
}

void
umv_msgs__msg__Obstacles__fini(umv_msgs__msg__Obstacles * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // obs_cnt
  // obs_xs
  rosidl_runtime_c__double__Sequence__fini(&msg->obs_xs);
  // obs_ys
  rosidl_runtime_c__double__Sequence__fini(&msg->obs_ys);
  // obs_ss
  rosidl_runtime_c__double__Sequence__fini(&msg->obs_ss);
  // obs_eys
  rosidl_runtime_c__double__Sequence__fini(&msg->obs_eys);
  // obs_eyaws
  rosidl_runtime_c__double__Sequence__fini(&msg->obs_eyaws);
}

bool
umv_msgs__msg__Obstacles__are_equal(const umv_msgs__msg__Obstacles * lhs, const umv_msgs__msg__Obstacles * rhs)
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
  // obs_cnt
  if (lhs->obs_cnt != rhs->obs_cnt) {
    return false;
  }
  // obs_xs
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->obs_xs), &(rhs->obs_xs)))
  {
    return false;
  }
  // obs_ys
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->obs_ys), &(rhs->obs_ys)))
  {
    return false;
  }
  // obs_ss
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->obs_ss), &(rhs->obs_ss)))
  {
    return false;
  }
  // obs_eys
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->obs_eys), &(rhs->obs_eys)))
  {
    return false;
  }
  // obs_eyaws
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->obs_eyaws), &(rhs->obs_eyaws)))
  {
    return false;
  }
  return true;
}

bool
umv_msgs__msg__Obstacles__copy(
  const umv_msgs__msg__Obstacles * input,
  umv_msgs__msg__Obstacles * output)
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
  // obs_cnt
  output->obs_cnt = input->obs_cnt;
  // obs_xs
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->obs_xs), &(output->obs_xs)))
  {
    return false;
  }
  // obs_ys
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->obs_ys), &(output->obs_ys)))
  {
    return false;
  }
  // obs_ss
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->obs_ss), &(output->obs_ss)))
  {
    return false;
  }
  // obs_eys
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->obs_eys), &(output->obs_eys)))
  {
    return false;
  }
  // obs_eyaws
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->obs_eyaws), &(output->obs_eyaws)))
  {
    return false;
  }
  return true;
}

umv_msgs__msg__Obstacles *
umv_msgs__msg__Obstacles__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__Obstacles * msg = (umv_msgs__msg__Obstacles *)allocator.allocate(sizeof(umv_msgs__msg__Obstacles), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(umv_msgs__msg__Obstacles));
  bool success = umv_msgs__msg__Obstacles__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
umv_msgs__msg__Obstacles__destroy(umv_msgs__msg__Obstacles * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    umv_msgs__msg__Obstacles__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
umv_msgs__msg__Obstacles__Sequence__init(umv_msgs__msg__Obstacles__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__Obstacles * data = NULL;

  if (size) {
    data = (umv_msgs__msg__Obstacles *)allocator.zero_allocate(size, sizeof(umv_msgs__msg__Obstacles), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = umv_msgs__msg__Obstacles__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        umv_msgs__msg__Obstacles__fini(&data[i - 1]);
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
umv_msgs__msg__Obstacles__Sequence__fini(umv_msgs__msg__Obstacles__Sequence * array)
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
      umv_msgs__msg__Obstacles__fini(&array->data[i]);
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

umv_msgs__msg__Obstacles__Sequence *
umv_msgs__msg__Obstacles__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__Obstacles__Sequence * array = (umv_msgs__msg__Obstacles__Sequence *)allocator.allocate(sizeof(umv_msgs__msg__Obstacles__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = umv_msgs__msg__Obstacles__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
umv_msgs__msg__Obstacles__Sequence__destroy(umv_msgs__msg__Obstacles__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    umv_msgs__msg__Obstacles__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
umv_msgs__msg__Obstacles__Sequence__are_equal(const umv_msgs__msg__Obstacles__Sequence * lhs, const umv_msgs__msg__Obstacles__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!umv_msgs__msg__Obstacles__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
umv_msgs__msg__Obstacles__Sequence__copy(
  const umv_msgs__msg__Obstacles__Sequence * input,
  umv_msgs__msg__Obstacles__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(umv_msgs__msg__Obstacles);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    umv_msgs__msg__Obstacles * data =
      (umv_msgs__msg__Obstacles *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!umv_msgs__msg__Obstacles__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          umv_msgs__msg__Obstacles__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!umv_msgs__msg__Obstacles__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
