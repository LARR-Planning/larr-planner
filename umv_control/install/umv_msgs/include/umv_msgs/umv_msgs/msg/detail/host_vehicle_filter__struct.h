// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from umv_msgs:msg/HostVehicleFilter.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__STRUCT_H_
#define UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/HostVehicleFilter in the package umv_msgs.
typedef struct umv_msgs__msg__HostVehicleFilter
{
  std_msgs__msg__Header header;
  float vx;
  float yawrate;
  float ax;
  float sas;
} umv_msgs__msg__HostVehicleFilter;

// Struct for a sequence of umv_msgs__msg__HostVehicleFilter.
typedef struct umv_msgs__msg__HostVehicleFilter__Sequence
{
  umv_msgs__msg__HostVehicleFilter * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} umv_msgs__msg__HostVehicleFilter__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__STRUCT_H_
