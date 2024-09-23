// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_H_
#define UMV_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_H_

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
// Member 'obs_xs'
// Member 'obs_ys'
// Member 'obs_ss'
// Member 'obs_eys'
// Member 'obs_eyaws'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Obstacles in the package umv_msgs.
typedef struct umv_msgs__msg__Obstacles
{
  std_msgs__msg__Header header;
  int32_t obs_cnt;
  rosidl_runtime_c__double__Sequence obs_xs;
  rosidl_runtime_c__double__Sequence obs_ys;
  rosidl_runtime_c__double__Sequence obs_ss;
  rosidl_runtime_c__double__Sequence obs_eys;
  rosidl_runtime_c__double__Sequence obs_eyaws;
} umv_msgs__msg__Obstacles;

// Struct for a sequence of umv_msgs__msg__Obstacles.
typedef struct umv_msgs__msg__Obstacles__Sequence
{
  umv_msgs__msg__Obstacles * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} umv_msgs__msg__Obstacles__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UMV_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_H_
