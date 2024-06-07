// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from umv_msgs:msg/HostVehicleFilter.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "umv_msgs/msg/detail/host_vehicle_filter__rosidl_typesupport_introspection_c.h"
#include "umv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "umv_msgs/msg/detail/host_vehicle_filter__functions.h"
#include "umv_msgs/msg/detail/host_vehicle_filter__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  umv_msgs__msg__HostVehicleFilter__init(message_memory);
}

void umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_fini_function(void * message_memory)
{
  umv_msgs__msg__HostVehicleFilter__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__HostVehicleFilter, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vx",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__HostVehicleFilter, vx),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yawrate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__HostVehicleFilter, yawrate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ax",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__HostVehicleFilter, ax),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sas",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs__msg__HostVehicleFilter, sas),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_members = {
  "umv_msgs__msg",  // message namespace
  "HostVehicleFilter",  // message name
  5,  // number of fields
  sizeof(umv_msgs__msg__HostVehicleFilter),
  umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_member_array,  // message members
  umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_init_function,  // function to initialize message memory (memory has to be allocated)
  umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_type_support_handle = {
  0,
  &umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_umv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, umv_msgs, msg, HostVehicleFilter)() {
  umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_type_support_handle.typesupport_identifier) {
    umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &umv_msgs__msg__HostVehicleFilter__rosidl_typesupport_introspection_c__HostVehicleFilter_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
