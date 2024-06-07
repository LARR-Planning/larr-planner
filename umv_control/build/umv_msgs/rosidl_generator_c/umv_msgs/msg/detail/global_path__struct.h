// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from umv_msgs:msg/GlobalPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__STRUCT_H_
#define UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__STRUCT_H_

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
// Member 'global_xs'
// Member 'global_ys'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/GlobalPath in the package umv_msgs.
typedef struct umv_msgs__msg__GlobalPath
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__double__Sequence global_xs;
  rosidl_runtime_c__double__Sequence global_ys;
  double distance_interval;
} umv_msgs__msg__GlobalPath;

// Struct for a sequence of umv_msgs__msg__GlobalPath.
typedef struct umv_msgs__msg__GlobalPath__Sequence
{
  umv_msgs__msg__GlobalPath * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} umv_msgs__msg__GlobalPath__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__STRUCT_H_
