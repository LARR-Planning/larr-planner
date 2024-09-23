// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from umv_msgs:msg/GlobalPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__BUILDER_HPP_
#define UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "umv_msgs/msg/detail/global_path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace umv_msgs
{

namespace msg
{

namespace builder
{

class Init_GlobalPath_distance_interval
{
public:
  explicit Init_GlobalPath_distance_interval(::umv_msgs::msg::GlobalPath & msg)
  : msg_(msg)
  {}
  ::umv_msgs::msg::GlobalPath distance_interval(::umv_msgs::msg::GlobalPath::_distance_interval_type arg)
  {
    msg_.distance_interval = std::move(arg);
    return std::move(msg_);
  }

private:
  ::umv_msgs::msg::GlobalPath msg_;
};

class Init_GlobalPath_global_ys
{
public:
  explicit Init_GlobalPath_global_ys(::umv_msgs::msg::GlobalPath & msg)
  : msg_(msg)
  {}
  Init_GlobalPath_distance_interval global_ys(::umv_msgs::msg::GlobalPath::_global_ys_type arg)
  {
    msg_.global_ys = std::move(arg);
    return Init_GlobalPath_distance_interval(msg_);
  }

private:
  ::umv_msgs::msg::GlobalPath msg_;
};

class Init_GlobalPath_global_xs
{
public:
  explicit Init_GlobalPath_global_xs(::umv_msgs::msg::GlobalPath & msg)
  : msg_(msg)
  {}
  Init_GlobalPath_global_ys global_xs(::umv_msgs::msg::GlobalPath::_global_xs_type arg)
  {
    msg_.global_xs = std::move(arg);
    return Init_GlobalPath_global_ys(msg_);
  }

private:
  ::umv_msgs::msg::GlobalPath msg_;
};

class Init_GlobalPath_header
{
public:
  Init_GlobalPath_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GlobalPath_global_xs header(::umv_msgs::msg::GlobalPath::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GlobalPath_global_xs(msg_);
  }

private:
  ::umv_msgs::msg::GlobalPath msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::umv_msgs::msg::GlobalPath>()
{
  return umv_msgs::msg::builder::Init_GlobalPath_header();
}

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__BUILDER_HPP_
