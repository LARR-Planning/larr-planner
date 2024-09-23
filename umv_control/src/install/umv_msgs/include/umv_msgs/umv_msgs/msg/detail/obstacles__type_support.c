// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "umv_msgs/msg/detail/obstacles__rosidl_typesupport_introspection_c.h"
#include "umv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "umv_msgs/msg/detail/obstacles__functions.h"
#include "umv_msgs/msg/detail/obstacles__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `obs_xs`
// Member `obs_ys`
// Member `obs_ss`
// Member `obs_eys`
// Member `obs_eyaws`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  umv_msgs__msg__Obstacles__init(message_memory);
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_fini_function(void * message_memory)
{
  umv_msgs__msg__Obstacles__fini(message_memory);
}

size_t umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_xs(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_xs(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_xs(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_xs(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_xs(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_xs(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_xs(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_xs(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_ys(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_ys(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_ys(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_ys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_ys(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_ys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_ys(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_ys(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_ss(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_ss(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_ss(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_ss(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_ss(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_ss(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_ss(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_ss(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_eys(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_eys(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_eys(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_eys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_eys(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_eys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_eys(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_eys(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_eyaws(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_eyaws(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_eyaws(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_eyaws(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_eyaws(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_eyaws(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_eyaws(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_eyaws(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_member_array[7] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "obs_cnt",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, obs_cnt),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "obs_xs",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, obs_xs),  // bytes offset in struct
    NULL,  // default value
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_xs,  // size() function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_xs,  // get_const(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_xs,  // get(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_xs,  // fetch(index, &value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_xs,  // assign(index, value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_xs  // resize(index) function pointer
  },
  {
    "obs_ys",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, obs_ys),  // bytes offset in struct
    NULL,  // default value
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_ys,  // size() function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_ys,  // get_const(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_ys,  // get(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_ys,  // fetch(index, &value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_ys,  // assign(index, value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_ys  // resize(index) function pointer
  },
  {
    "obs_ss",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, obs_ss),  // bytes offset in struct
    NULL,  // default value
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_ss,  // size() function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_ss,  // get_const(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_ss,  // get(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_ss,  // fetch(index, &value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_ss,  // assign(index, value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_ss  // resize(index) function pointer
  },
  {
    "obs_eys",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, obs_eys),  // bytes offset in struct
    NULL,  // default value
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_eys,  // size() function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_eys,  // get_const(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_eys,  // get(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_eys,  // fetch(index, &value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_eys,  // assign(index, value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_eys  // resize(index) function pointer
  },
  {
    "obs_eyaws",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__Obstacles, obs_eyaws),  // bytes offset in struct
    NULL,  // default value
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__size_function__Obstacles__obs_eyaws,  // size() function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_const_function__Obstacles__obs_eyaws,  // get_const(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__get_function__Obstacles__obs_eyaws,  // get(index) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__fetch_function__Obstacles__obs_eyaws,  // fetch(index, &value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__assign_function__Obstacles__obs_eyaws,  // assign(index, value) function pointer
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__resize_function__Obstacles__obs_eyaws  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_members = {
  "umv_msgs__msg",  // message namespace
  "Obstacles",  // message name
  7,  // number of fields
  sizeof(umv_msgs__msg__Obstacles),
  umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_member_array,  // message members
  umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_init_function,  // function to initialize message memory (memory has to be allocated)
  umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_type_support_handle = {
  0,
  &umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_umv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, umv_msgs, msg, Obstacles)() {
  umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_type_support_handle.typesupport_identifier) {
    umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &umv_msgs__msg__Obstacles__rosidl_typesupport_introspection_c__Obstacles_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
