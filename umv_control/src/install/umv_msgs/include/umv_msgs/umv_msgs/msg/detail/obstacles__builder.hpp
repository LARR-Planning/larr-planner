// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__OBSTACLES__BUILDER_HPP_
#define UMV_MSGS__MSG__DETAIL__OBSTACLES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "umv_msgs/msg/detail/obstacles__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace umv_msgs
{

namespace msg
{

namespace builder
{

class Init_Obstacles_obs_eyaws
{
public:
  explicit Init_Obstacles_obs_eyaws(::umv_msgs::msg::Obstacles & msg)
  : msg_(msg)
  {}
  ::umv_msgs::msg::Obstacles obs_eyaws(::umv_msgs::msg::Obstacles::_obs_eyaws_type arg)
  {
    msg_.obs_eyaws = std::move(arg);
    return std::move(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

class Init_Obstacles_obs_eys
{
public:
  explicit Init_Obstacles_obs_eys(::umv_msgs::msg::Obstacles & msg)
  : msg_(msg)
  {}
  Init_Obstacles_obs_eyaws obs_eys(::umv_msgs::msg::Obstacles::_obs_eys_type arg)
  {
    msg_.obs_eys = std::move(arg);
    return Init_Obstacles_obs_eyaws(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

class Init_Obstacles_obs_ss
{
public:
  explicit Init_Obstacles_obs_ss(::umv_msgs::msg::Obstacles & msg)
  : msg_(msg)
  {}
  Init_Obstacles_obs_eys obs_ss(::umv_msgs::msg::Obstacles::_obs_ss_type arg)
  {
    msg_.obs_ss = std::move(arg);
    return Init_Obstacles_obs_eys(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

class Init_Obstacles_obs_ys
{
public:
  explicit Init_Obstacles_obs_ys(::umv_msgs::msg::Obstacles & msg)
  : msg_(msg)
  {}
  Init_Obstacles_obs_ss obs_ys(::umv_msgs::msg::Obstacles::_obs_ys_type arg)
  {
    msg_.obs_ys = std::move(arg);
    return Init_Obstacles_obs_ss(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

class Init_Obstacles_obs_xs
{
public:
  explicit Init_Obstacles_obs_xs(::umv_msgs::msg::Obstacles & msg)
  : msg_(msg)
  {}
  Init_Obstacles_obs_ys obs_xs(::umv_msgs::msg::Obstacles::_obs_xs_type arg)
  {
    msg_.obs_xs = std::move(arg);
    return Init_Obstacles_obs_ys(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

class Init_Obstacles_obs_cnt
{
public:
  explicit Init_Obstacles_obs_cnt(::umv_msgs::msg::Obstacles & msg)
  : msg_(msg)
  {}
  Init_Obstacles_obs_xs obs_cnt(::umv_msgs::msg::Obstacles::_obs_cnt_type arg)
  {
    msg_.obs_cnt = std::move(arg);
    return Init_Obstacles_obs_xs(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

class Init_Obstacles_header
{
public:
  Init_Obstacles_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Obstacles_obs_cnt header(::umv_msgs::msg::Obstacles::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Obstacles_obs_cnt(msg_);
  }

private:
  ::umv_msgs::msg::Obstacles msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::umv_msgs::msg::Obstacles>()
{
  return umv_msgs::msg::builder::Init_Obstacles_header();
}

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__OBSTACLES__BUILDER_HPP_
