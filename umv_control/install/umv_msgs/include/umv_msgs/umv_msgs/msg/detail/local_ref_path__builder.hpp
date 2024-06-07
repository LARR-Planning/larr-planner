// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__BUILDER_HPP_
#define UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "umv_msgs/msg/detail/local_ref_path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace umv_msgs
{

namespace msg
{

namespace builder
{

class Init_LocalRefPath_ego_s
{
public:
  explicit Init_LocalRefPath_ego_s(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  ::umv_msgs::msg::LocalRefPath ego_s(::umv_msgs::msg::LocalRefPath::_ego_s_type arg)
  {
    msg_.ego_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_eyaw
{
public:
  explicit Init_LocalRefPath_eyaw(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_ego_s eyaw(::umv_msgs::msg::LocalRefPath::_eyaw_type arg)
  {
    msg_.eyaw = std::move(arg);
    return Init_LocalRefPath_ego_s(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_ey
{
public:
  explicit Init_LocalRefPath_ey(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_eyaw ey(::umv_msgs::msg::LocalRefPath::_ey_type arg)
  {
    msg_.ey = std::move(arg);
    return Init_LocalRefPath_eyaw(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_local_ref_curvs
{
public:
  explicit Init_LocalRefPath_local_ref_curvs(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_ey local_ref_curvs(::umv_msgs::msg::LocalRefPath::_local_ref_curvs_type arg)
  {
    msg_.local_ref_curvs = std::move(arg);
    return Init_LocalRefPath_ey(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_local_ref_yaws
{
public:
  explicit Init_LocalRefPath_local_ref_yaws(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_local_ref_curvs local_ref_yaws(::umv_msgs::msg::LocalRefPath::_local_ref_yaws_type arg)
  {
    msg_.local_ref_yaws = std::move(arg);
    return Init_LocalRefPath_local_ref_curvs(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_local_ref_ss
{
public:
  explicit Init_LocalRefPath_local_ref_ss(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_local_ref_yaws local_ref_ss(::umv_msgs::msg::LocalRefPath::_local_ref_ss_type arg)
  {
    msg_.local_ref_ss = std::move(arg);
    return Init_LocalRefPath_local_ref_yaws(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_local_ref_ys
{
public:
  explicit Init_LocalRefPath_local_ref_ys(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_local_ref_ss local_ref_ys(::umv_msgs::msg::LocalRefPath::_local_ref_ys_type arg)
  {
    msg_.local_ref_ys = std::move(arg);
    return Init_LocalRefPath_local_ref_ss(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_local_ref_xs
{
public:
  explicit Init_LocalRefPath_local_ref_xs(::umv_msgs::msg::LocalRefPath & msg)
  : msg_(msg)
  {}
  Init_LocalRefPath_local_ref_ys local_ref_xs(::umv_msgs::msg::LocalRefPath::_local_ref_xs_type arg)
  {
    msg_.local_ref_xs = std::move(arg);
    return Init_LocalRefPath_local_ref_ys(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

class Init_LocalRefPath_header
{
public:
  Init_LocalRefPath_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocalRefPath_local_ref_xs header(::umv_msgs::msg::LocalRefPath::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LocalRefPath_local_ref_xs(msg_);
  }

private:
  ::umv_msgs::msg::LocalRefPath msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::umv_msgs::msg::LocalRefPath>()
{
  return umv_msgs::msg::builder::Init_LocalRefPath_header();
}

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__BUILDER_HPP_
