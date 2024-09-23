// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "umv_msgs/msg/detail/obstacles__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace umv_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Obstacles_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) umv_msgs::msg::Obstacles(_init);
}

void Obstacles_fini_function(void * message_memory)
{
  auto typed_message = static_cast<umv_msgs::msg::Obstacles *>(message_memory);
  typed_message->~Obstacles();
}

size_t size_function__Obstacles__obs_xs(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Obstacles__obs_xs(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__Obstacles__obs_xs(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__Obstacles__obs_xs(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__Obstacles__obs_xs(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__Obstacles__obs_xs(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__Obstacles__obs_xs(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__Obstacles__obs_xs(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__Obstacles__obs_ys(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Obstacles__obs_ys(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__Obstacles__obs_ys(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__Obstacles__obs_ys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__Obstacles__obs_ys(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__Obstacles__obs_ys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__Obstacles__obs_ys(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__Obstacles__obs_ys(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__Obstacles__obs_ss(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Obstacles__obs_ss(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__Obstacles__obs_ss(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__Obstacles__obs_ss(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__Obstacles__obs_ss(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__Obstacles__obs_ss(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__Obstacles__obs_ss(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__Obstacles__obs_ss(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__Obstacles__obs_eys(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Obstacles__obs_eys(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__Obstacles__obs_eys(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__Obstacles__obs_eys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__Obstacles__obs_eys(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__Obstacles__obs_eys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__Obstacles__obs_eys(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__Obstacles__obs_eys(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__Obstacles__obs_eyaws(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Obstacles__obs_eyaws(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__Obstacles__obs_eyaws(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__Obstacles__obs_eyaws(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__Obstacles__obs_eyaws(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__Obstacles__obs_eyaws(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__Obstacles__obs_eyaws(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__Obstacles__obs_eyaws(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Obstacles_message_member_array[7] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "obs_cnt",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, obs_cnt),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "obs_xs",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, obs_xs),  // bytes offset in struct
    nullptr,  // default value
    size_function__Obstacles__obs_xs,  // size() function pointer
    get_const_function__Obstacles__obs_xs,  // get_const(index) function pointer
    get_function__Obstacles__obs_xs,  // get(index) function pointer
    fetch_function__Obstacles__obs_xs,  // fetch(index, &value) function pointer
    assign_function__Obstacles__obs_xs,  // assign(index, value) function pointer
    resize_function__Obstacles__obs_xs  // resize(index) function pointer
  },
  {
    "obs_ys",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, obs_ys),  // bytes offset in struct
    nullptr,  // default value
    size_function__Obstacles__obs_ys,  // size() function pointer
    get_const_function__Obstacles__obs_ys,  // get_const(index) function pointer
    get_function__Obstacles__obs_ys,  // get(index) function pointer
    fetch_function__Obstacles__obs_ys,  // fetch(index, &value) function pointer
    assign_function__Obstacles__obs_ys,  // assign(index, value) function pointer
    resize_function__Obstacles__obs_ys  // resize(index) function pointer
  },
  {
    "obs_ss",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, obs_ss),  // bytes offset in struct
    nullptr,  // default value
    size_function__Obstacles__obs_ss,  // size() function pointer
    get_const_function__Obstacles__obs_ss,  // get_const(index) function pointer
    get_function__Obstacles__obs_ss,  // get(index) function pointer
    fetch_function__Obstacles__obs_ss,  // fetch(index, &value) function pointer
    assign_function__Obstacles__obs_ss,  // assign(index, value) function pointer
    resize_function__Obstacles__obs_ss  // resize(index) function pointer
  },
  {
    "obs_eys",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, obs_eys),  // bytes offset in struct
    nullptr,  // default value
    size_function__Obstacles__obs_eys,  // size() function pointer
    get_const_function__Obstacles__obs_eys,  // get_const(index) function pointer
    get_function__Obstacles__obs_eys,  // get(index) function pointer
    fetch_function__Obstacles__obs_eys,  // fetch(index, &value) function pointer
    assign_function__Obstacles__obs_eys,  // assign(index, value) function pointer
    resize_function__Obstacles__obs_eys  // resize(index) function pointer
  },
  {
    "obs_eyaws",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::Obstacles, obs_eyaws),  // bytes offset in struct
    nullptr,  // default value
    size_function__Obstacles__obs_eyaws,  // size() function pointer
    get_const_function__Obstacles__obs_eyaws,  // get_const(index) function pointer
    get_function__Obstacles__obs_eyaws,  // get(index) function pointer
    fetch_function__Obstacles__obs_eyaws,  // fetch(index, &value) function pointer
    assign_function__Obstacles__obs_eyaws,  // assign(index, value) function pointer
    resize_function__Obstacles__obs_eyaws  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Obstacles_message_members = {
  "umv_msgs::msg",  // message namespace
  "Obstacles",  // message name
  7,  // number of fields
  sizeof(umv_msgs::msg::Obstacles),
  Obstacles_message_member_array,  // message members
  Obstacles_init_function,  // function to initialize message memory (memory has to be allocated)
  Obstacles_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Obstacles_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Obstacles_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace umv_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<umv_msgs::msg::Obstacles>()
{
  return &::umv_msgs::msg::rosidl_typesupport_introspection_cpp::Obstacles_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, umv_msgs, msg, Obstacles)() {
  return &::umv_msgs::msg::rosidl_typesupport_introspection_cpp::Obstacles_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
