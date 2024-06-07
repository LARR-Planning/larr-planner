// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from umv_msgs:msg/AcuCmd.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__ACU_CMD__BUILDER_HPP_
#define UMV_MSGS__MSG__DETAIL__ACU_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "umv_msgs/msg/detail/acu_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace umv_msgs
{

namespace msg
{

namespace builder
{

class Init_AcuCmd_sas
{
public:
  explicit Init_AcuCmd_sas(::umv_msgs::msg::AcuCmd & msg)
  : msg_(msg)
  {}
  ::umv_msgs::msg::AcuCmd sas(::umv_msgs::msg::AcuCmd::_sas_type arg)
  {
    msg_.sas = std::move(arg);
    return std::move(msg_);
  }

private:
  ::umv_msgs::msg::AcuCmd msg_;
};

class Init_AcuCmd_ax
{
public:
  explicit Init_AcuCmd_ax(::umv_msgs::msg::AcuCmd & msg)
  : msg_(msg)
  {}
  Init_AcuCmd_sas ax(::umv_msgs::msg::AcuCmd::_ax_type arg)
  {
    msg_.ax = std::move(arg);
    return Init_AcuCmd_sas(msg_);
  }

private:
  ::umv_msgs::msg::AcuCmd msg_;
};

class Init_AcuCmd_header
{
public:
  Init_AcuCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AcuCmd_ax header(::umv_msgs::msg::AcuCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AcuCmd_ax(msg_);
  }

private:
  ::umv_msgs::msg::AcuCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::umv_msgs::msg::AcuCmd>()
{
  return umv_msgs::msg::builder::Init_AcuCmd_header();
}

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__ACU_CMD__BUILDER_HPP_
