// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "umv_msgs/msg/detail/local_ref_path__struct.hpp"
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

void LocalRefPath_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) umv_msgs::msg::LocalRefPath(_init);
}

void LocalRefPath_fini_function(void * message_memory)
{
  auto typed_message = static_cast<umv_msgs::msg::LocalRefPath *>(message_memory);
  typed_message->~LocalRefPath();
}

size_t size_function__LocalRefPath__local_ref_xs(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LocalRefPath__local_ref_xs(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__LocalRefPath__local_ref_xs(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__LocalRefPath__local_ref_xs(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LocalRefPath__local_ref_xs(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LocalRefPath__local_ref_xs(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LocalRefPath__local_ref_xs(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__LocalRefPath__local_ref_xs(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__LocalRefPath__local_ref_ys(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LocalRefPath__local_ref_ys(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__LocalRefPath__local_ref_ys(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__LocalRefPath__local_ref_ys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LocalRefPath__local_ref_ys(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LocalRefPath__local_ref_ys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LocalRefPath__local_ref_ys(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__LocalRefPath__local_ref_ys(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__LocalRefPath__local_ref_ss(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LocalRefPath__local_ref_ss(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__LocalRefPath__local_ref_ss(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__LocalRefPath__local_ref_ss(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LocalRefPath__local_ref_ss(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LocalRefPath__local_ref_ss(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LocalRefPath__local_ref_ss(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__LocalRefPath__local_ref_ss(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__LocalRefPath__local_ref_yaws(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LocalRefPath__local_ref_yaws(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__LocalRefPath__local_ref_yaws(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__LocalRefPath__local_ref_yaws(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LocalRefPath__local_ref_yaws(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LocalRefPath__local_ref_yaws(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LocalRefPath__local_ref_yaws(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__LocalRefPath__local_ref_yaws(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__LocalRefPath__local_ref_curvs(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LocalRefPath__local_ref_curvs(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__LocalRefPath__local_ref_curvs(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__LocalRefPath__local_ref_curvs(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LocalRefPath__local_ref_curvs(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LocalRefPath__local_ref_curvs(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LocalRefPath__local_ref_curvs(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__LocalRefPath__local_ref_curvs(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LocalRefPath_message_member_array[9] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "local_ref_xs",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, local_ref_xs),  // bytes offset in struct
    nullptr,  // default value
    size_function__LocalRefPath__local_ref_xs,  // size() function pointer
    get_const_function__LocalRefPath__local_ref_xs,  // get_const(index) function pointer
    get_function__LocalRefPath__local_ref_xs,  // get(index) function pointer
    fetch_function__LocalRefPath__local_ref_xs,  // fetch(index, &value) function pointer
    assign_function__LocalRefPath__local_ref_xs,  // assign(index, value) function pointer
    resize_function__LocalRefPath__local_ref_xs  // resize(index) function pointer
  },
  {
    "local_ref_ys",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, local_ref_ys),  // bytes offset in struct
    nullptr,  // default value
    size_function__LocalRefPath__local_ref_ys,  // size() function pointer
    get_const_function__LocalRefPath__local_ref_ys,  // get_const(index) function pointer
    get_function__LocalRefPath__local_ref_ys,  // get(index) function pointer
    fetch_function__LocalRefPath__local_ref_ys,  // fetch(index, &value) function pointer
    assign_function__LocalRefPath__local_ref_ys,  // assign(index, value) function pointer
    resize_function__LocalRefPath__local_ref_ys  // resize(index) function pointer
  },
  {
    "local_ref_ss",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, local_ref_ss),  // bytes offset in struct
    nullptr,  // default value
    size_function__LocalRefPath__local_ref_ss,  // size() function pointer
    get_const_function__LocalRefPath__local_ref_ss,  // get_const(index) function pointer
    get_function__LocalRefPath__local_ref_ss,  // get(index) function pointer
    fetch_function__LocalRefPath__local_ref_ss,  // fetch(index, &value) function pointer
    assign_function__LocalRefPath__local_ref_ss,  // assign(index, value) function pointer
    resize_function__LocalRefPath__local_ref_ss  // resize(index) function pointer
  },
  {
    "local_ref_yaws",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, local_ref_yaws),  // bytes offset in struct
    nullptr,  // default value
    size_function__LocalRefPath__local_ref_yaws,  // size() function pointer
    get_const_function__LocalRefPath__local_ref_yaws,  // get_const(index) function pointer
    get_function__LocalRefPath__local_ref_yaws,  // get(index) function pointer
    fetch_function__LocalRefPath__local_ref_yaws,  // fetch(index, &value) function pointer
    assign_function__LocalRefPath__local_ref_yaws,  // assign(index, value) function pointer
    resize_function__LocalRefPath__local_ref_yaws  // resize(index) function pointer
  },
  {
    "local_ref_curvs",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, local_ref_curvs),  // bytes offset in struct
    nullptr,  // default value
    size_function__LocalRefPath__local_ref_curvs,  // size() function pointer
    get_const_function__LocalRefPath__local_ref_curvs,  // get_const(index) function pointer
    get_function__LocalRefPath__local_ref_curvs,  // get(index) function pointer
    fetch_function__LocalRefPath__local_ref_curvs,  // fetch(index, &value) function pointer
    assign_function__LocalRefPath__local_ref_curvs,  // assign(index, value) function pointer
    resize_function__LocalRefPath__local_ref_curvs  // resize(index) function pointer
  },
  {
    "ey",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, ey),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "eyaw",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, eyaw),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "ego_s",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(umv_msgs::msg::LocalRefPath, ego_s),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LocalRefPath_message_members = {
  "umv_msgs::msg",  // message namespace
  "LocalRefPath",  // message name
  9,  // number of fields
  sizeof(umv_msgs::msg::LocalRefPath),
  LocalRefPath_message_member_array,  // message members
  LocalRefPath_init_function,  // function to initialize message memory (memory has to be allocated)
  LocalRefPath_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LocalRefPath_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LocalRefPath_message_members,
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
get_message_type_support_handle<umv_msgs::msg::LocalRefPath>()
{
  return &::umv_msgs::msg::rosidl_typesupport_introspection_cpp::LocalRefPath_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, umv_msgs, msg, LocalRefPath)() {
  return &::umv_msgs::msg::rosidl_typesupport_introspection_cpp::LocalRefPath_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
