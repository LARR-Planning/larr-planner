// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from umv_msgs:msg/HostVehicleFilter.idl
// generated code does not contain a copyright notice
#include "umv_msgs/msg/detail/host_vehicle_filter__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
umv_msgs__msg__HostVehicleFilter__init(umv_msgs__msg__HostVehicleFilter * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    umv_msgs__msg__HostVehicleFilter__fini(msg);
    return false;
  }
  // vx
  // yawrate
  // ax
  // sas
  return true;
}

void
umv_msgs__msg__HostVehicleFilter__fini(umv_msgs__msg__HostVehicleFilter * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // vx
  // yawrate
  // ax
  // sas
}

bool
umv_msgs__msg__HostVehicleFilter__are_equal(const umv_msgs__msg__HostVehicleFilter * lhs, const umv_msgs__msg__HostVehicleFilter * rhs)
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
  // vx
  if (lhs->vx != rhs->vx) {
    return false;
  }
  // yawrate
  if (lhs->yawrate != rhs->yawrate) {
    return false;
  }
  // ax
  if (lhs->ax != rhs->ax) {
    return false;
  }
  // sas
  if (lhs->sas != rhs->sas) {
    return false;
  }
  return true;
}

bool
umv_msgs__msg__HostVehicleFilter__copy(
  const umv_msgs__msg__HostVehicleFilter * input,
  umv_msgs__msg__HostVehicleFilter * output)
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
  // vx
  output->vx = input->vx;
  // yawrate
  output->yawrate = input->yawrate;
  // ax
  output->ax = input->ax;
  // sas
  output->sas = input->sas;
  return true;
}

umv_msgs__msg__HostVehicleFilter *
umv_msgs__msg__HostVehicleFilter__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__HostVehicleFilter * msg = (umv_msgs__msg__HostVehicleFilter *)allocator.allocate(sizeof(umv_msgs__msg__HostVehicleFilter), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(umv_msgs__msg__HostVehicleFilter));
  bool success = umv_msgs__msg__HostVehicleFilter__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
umv_msgs__msg__HostVehicleFilter__destroy(umv_msgs__msg__HostVehicleFilter * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    umv_msgs__msg__HostVehicleFilter__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
umv_msgs__msg__HostVehicleFilter__Sequence__init(umv_msgs__msg__HostVehicleFilter__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__HostVehicleFilter * data = NULL;

  if (size) {
    data = (umv_msgs__msg__HostVehicleFilter *)allocator.zero_allocate(size, sizeof(umv_msgs__msg__HostVehicleFilter), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = umv_msgs__msg__HostVehicleFilter__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        umv_msgs__msg__HostVehicleFilter__fini(&data[i - 1]);
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
umv_msgs__msg__HostVehicleFilter__Sequence__fini(umv_msgs__msg__HostVehicleFilter__Sequence * array)
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
      umv_msgs__msg__HostVehicleFilter__fini(&array->data[i]);
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

umv_msgs__msg__HostVehicleFilter__Sequence *
umv_msgs__msg__HostVehicleFilter__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  umv_msgs__msg__HostVehicleFilter__Sequence * array = (umv_msgs__msg__HostVehicleFilter__Sequence *)allocator.allocate(sizeof(umv_msgs__msg__HostVehicleFilter__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = umv_msgs__msg__HostVehicleFilter__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
umv_msgs__msg__HostVehicleFilter__Sequence__destroy(umv_msgs__msg__HostVehicleFilter__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    umv_msgs__msg__HostVehicleFilter__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
umv_msgs__msg__HostVehicleFilter__Sequence__are_equal(const umv_msgs__msg__HostVehicleFilter__Sequence * lhs, const umv_msgs__msg__HostVehicleFilter__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!umv_msgs__msg__HostVehicleFilter__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
umv_msgs__msg__HostVehicleFilter__Sequence__copy(
  const umv_msgs__msg__HostVehicleFilter__Sequence * input,
  umv_msgs__msg__HostVehicleFilter__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(umv_msgs__msg__HostVehicleFilter);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    umv_msgs__msg__HostVehicleFilter * data =
      (umv_msgs__msg__HostVehicleFilter *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!umv_msgs__msg__HostVehicleFilter__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          umv_msgs__msg__HostVehicleFilter__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!umv_msgs__msg__HostVehicleFilter__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
