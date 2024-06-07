// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice
#include "umv_msgs/msg/detail/local_ref_path__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `local_ref_xs`
// Member `local_ref_ys`
// Member `local_ref_ss`
// Member `local_ref_yaws`
// Member `local_ref_curvs`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
umv_msgs__msg__LocalRefPath__init(umv_msgs__msg__LocalRefPath * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    umv_msgs__msg__LocalRefPath__fini(msg);
    return false;
  }
  // local_ref_xs
  if (!rosidl_runtime_c__double__Sequence__init(&msg->local_ref_xs, 0)) {
    umv_msgs__msg__LocalRefPath__fini(msg);
    return false;
  }
  // local_ref_ys
  if (!rosidl_runtime_c__double__Sequence__init(&msg->local_ref_ys, 0)) {
    umv_msgs__msg__LocalRefPath__fini(msg);
    return false;
  }
  // local_ref_ss
  if (!rosidl_runtime_c__double__Sequence__init(&msg->local_ref_ss, 0)) {
    umv_msgs__msg__LocalRefPath__fini(msg);
    return false;
  }
  // local_ref_yaws
  if (!rosidl_runtime_c__double__Sequence__init(&msg->local_ref_yaws, 0)) {
    umv_msgs__msg__LocalRefPath__fini(msg);
    return false;
  }
  // local_ref_curvs
  if (!rosidl_runtime_c__double__Sequence__init(&msg->local_ref_curvs, 0)) {
    umv_msgs__msg__LocalRefPath__fini(msg);
    return false;
  }
  // ey
  // eyaw
  // ego_s
  return true;
}

void
umv_msgs__msg__LocalRefPath__fini(umv_msgs__msg__LocalRefPath * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // local_ref_xs
  rosidl_runtime_c__double__Sequence__fini(&msg->local_ref_xs);
  // local_ref_ys
  rosidl_runtime_c__double__Sequence__fini(&msg->local_ref_ys);
  // local_ref_ss
  rosidl_runtime_c__double__Sequence__fini(&msg->local_ref_ss);
  // local_ref_yaws
  rosidl_runtime_c__double__Sequence__fini(&msg->local_ref_yaws);
  // local_ref_curvs
  rosidl_runtime_c__double__Sequence__fini(&msg->local_ref_curvs);
  // ey
  // eyaw
  // ego_s
}

bool
umv_msgs__msg__LocalRefPath__are_equal(const umv_msgs__msg__LocalRefPath * lhs, const umv_msgs__msg__LocalRefPath * rhs)
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
  // local_ref_xs
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->local_ref_xs), &(rhs->local_ref_xs)))
  {
    return false;
  }
  // local_ref_ys
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->local_ref_ys), &(rhs->local_ref_ys)))
  {
    return false;
  }
  // local_ref_ss
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->local_ref_ss), &(rhs->local_ref_ss)))
  {
    return false;
  }
  // local_ref_yaws
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->local_ref_yaws), &(rhs->local_ref_yaws)))
  {
    return false;
  }
  // local_ref_curvs
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->local_ref_curvs), &(rhs->local_ref_curvs)))
  {
    return false;
  }
  // ey
  if (lhs->ey != rhs->ey) {
    return false;
  }
  // eyaw
  if (lhs->eyaw != rhs->eyaw) {
    return false;
  }
  // ego_s
  if (lhs->ego_s != rhs->ego_s) {
    return false;
  }
  return true;
}

bool
umv_msgs__msg__LocalRefPath__copy(
  const umv_msgs__msg__LocalRefPath * input,
  umv_msgs__msg__LocalRefPath * output)
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
  // local_ref_xs
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->local_ref_xs), &(output->local_ref_xs)))
  {
    return false;
  }
  // local_ref_ys
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->local_ref_ys), &(output->local_ref_ys)))
  {
    return false;
  }
  // local_ref_ss
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->local_ref_ss), &(output->local_ref_ss)))
  {
    return false;
  }
  // local_ref_yaws
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->local_ref_yaws), &(output->local_ref_yaws)))
  {
    return false;
  }
  // local_ref_curvs
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->local_ref_curvs), &(output->local_ref_curvs)))
  {
    return false;
  }
  // ey
  output->ey = input->ey;
  // eyaw
  output->eyaw = input->eyaw;
  // ego_s
  output->ego_s = input->ego_s;
  return true;
}

umv_msgs__msg__LocalRefPath *
umv_msgs__msg__LocalRefPath__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__LocalRefPath * msg = (umv_msgs__msg__LocalRefPath *)allocator.allocate(sizeof(umv_msgs__msg__LocalRefPath), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(umv_msgs__msg__LocalRefPath));
  bool success = umv_msgs__msg__LocalRefPath__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
umv_msgs__msg__LocalRefPath__destroy(umv_msgs__msg__LocalRefPath * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    umv_msgs__msg__LocalRefPath__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
umv_msgs__msg__LocalRefPath__Sequence__init(umv_msgs__msg__LocalRefPath__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__LocalRefPath * data = NULL;

  if (size) {
    data = (umv_msgs__msg__LocalRefPath *)allocator.zero_allocate(size, sizeof(umv_msgs__msg__LocalRefPath), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = umv_msgs__msg__LocalRefPath__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        umv_msgs__msg__LocalRefPath__fini(&data[i - 1]);
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
umv_msgs__msg__LocalRefPath__Sequence__fini(umv_msgs__msg__LocalRefPath__Sequence * array)
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
      umv_msgs__msg__LocalRefPath__fini(&array->data[i]);
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

umv_msgs__msg__LocalRefPath__Sequence *
umv_msgs__msg__LocalRefPath__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__LocalRefPath__Sequence * array = (umv_msgs__msg__LocalRefPath__Sequence *)allocator.allocate(sizeof(umv_msgs__msg__LocalRefPath__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = umv_msgs__msg__LocalRefPath__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
umv_msgs__msg__LocalRefPath__Sequence__destroy(umv_msgs__msg__LocalRefPath__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    umv_msgs__msg__LocalRefPath__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
umv_msgs__msg__LocalRefPath__Sequence__are_equal(const umv_msgs__msg__LocalRefPath__Sequence * lhs, const umv_msgs__msg__LocalRefPath__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!umv_msgs__msg__LocalRefPath__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
umv_msgs__msg__LocalRefPath__Sequence__copy(
  const umv_msgs__msg__LocalRefPath__Sequence * input,
  umv_msgs__msg__LocalRefPath__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(umv_msgs__msg__LocalRefPath);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    umv_msgs__msg__LocalRefPath * data =
      (umv_msgs__msg__LocalRefPath *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!umv_msgs__msg__LocalRefPath__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          umv_msgs__msg__LocalRefPath__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!umv_msgs__msg__LocalRefPath__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
