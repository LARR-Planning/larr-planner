// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__STRUCT_H_
#define UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__STRUCT_H_

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
// Member 'local_ref_xs'
// Member 'local_ref_ys'
// Member 'local_ref_ss'
// Member 'local_ref_yaws'
// Member 'local_ref_curvs'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/LocalRefPath in the package umv_msgs.
typedef struct umv_msgs__msg__LocalRefPath
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__double__Sequence local_ref_xs;
  rosidl_runtime_c__double__Sequence local_ref_ys;
  rosidl_runtime_c__double__Sequence local_ref_ss;
  rosidl_runtime_c__double__Sequence local_ref_yaws;
  rosidl_runtime_c__double__Sequence local_ref_curvs;
  double ey;
  double eyaw;
  double ego_s;
} umv_msgs__msg__LocalRefPath;

// Struct for a sequence of umv_msgs__msg__LocalRefPath.
typedef struct umv_msgs__msg__LocalRefPath__Sequence
{
  umv_msgs__msg__LocalRefPath * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} umv_msgs__msg__LocalRefPath__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__STRUCT_H_
