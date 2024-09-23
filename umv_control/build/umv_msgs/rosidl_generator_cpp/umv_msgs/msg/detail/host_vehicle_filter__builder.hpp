// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from umv_msgs:msg/HostVehicleFilter.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__BUILDER_HPP_
#define UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "umv_msgs/msg/detail/host_vehicle_filter__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace umv_msgs
{

namespace msg
{

namespace builder
{

class Init_HostVehicleFilter_sas
{
public:
  explicit Init_HostVehicleFilter_sas(::umv_msgs::msg::HostVehicleFilter & msg)
  : msg_(msg)
  {}
  ::umv_msgs::msg::HostVehicleFilter sas(::umv_msgs::msg::HostVehicleFilter::_sas_type arg)
  {
    msg_.sas = std::move(arg);
    return std::move(msg_);
  }

private:
  ::umv_msgs::msg::HostVehicleFilter msg_;
};

class Init_HostVehicleFilter_ax
{
public:
  explicit Init_HostVehicleFilter_ax(::umv_msgs::msg::HostVehicleFilter & msg)
  : msg_(msg)
  {}
  Init_HostVehicleFilter_sas ax(::umv_msgs::msg::HostVehicleFilter::_ax_type arg)
  {
    msg_.ax = std::move(arg);
    return Init_HostVehicleFilter_sas(msg_);
  }

private:
  ::umv_msgs::msg::HostVehicleFilter msg_;
};

class Init_HostVehicleFilter_yawrate
{
public:
  explicit Init_HostVehicleFilter_yawrate(::umv_msgs::msg::HostVehicleFilter & msg)
  : msg_(msg)
  {}
  Init_HostVehicleFilter_ax yawrate(::umv_msgs::msg::HostVehicleFilter::_yawrate_type arg)
  {
    msg_.yawrate = std::move(arg);
    return Init_HostVehicleFilter_ax(msg_);
  }

private:
  ::umv_msgs::msg::HostVehicleFilter msg_;
};

class Init_HostVehicleFilter_vx
{
public:
  explicit Init_HostVehicleFilter_vx(::umv_msgs::msg::HostVehicleFilter & msg)
  : msg_(msg)
  {}
  Init_HostVehicleFilter_yawrate vx(::umv_msgs::msg::HostVehicleFilter::_vx_type arg)
  {
    msg_.vx = std::move(arg);
    return Init_HostVehicleFilter_yawrate(msg_);
  }

private:
  ::umv_msgs::msg::HostVehicleFilter msg_;
};

class Init_HostVehicleFilter_header
{
public:
  Init_HostVehicleFilter_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HostVehicleFilter_vx header(::umv_msgs::msg::HostVehicleFilter::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HostVehicleFilter_vx(msg_);
  }

private:
  ::umv_msgs::msg::HostVehicleFilter msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::umv_msgs::msg::HostVehicleFilter>()
{
  return umv_msgs::msg::builder::Init_HostVehicleFilter_header();
}

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__BUILDER_HPP_
