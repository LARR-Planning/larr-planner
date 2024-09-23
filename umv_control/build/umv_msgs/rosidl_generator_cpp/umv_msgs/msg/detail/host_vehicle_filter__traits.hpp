// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from umv_msgs:msg/HostVehicleFilter.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__TRAITS_HPP_
#define UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "umv_msgs/msg/detail/host_vehicle_filter__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace umv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HostVehicleFilter & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: vx
  {
    out << "vx: ";
    rosidl_generator_traits::value_to_yaml(msg.vx, out);
    out << ", ";
  }

  // member: yawrate
  {
    out << "yawrate: ";
    rosidl_generator_traits::value_to_yaml(msg.yawrate, out);
    out << ", ";
  }

  // member: ax
  {
    out << "ax: ";
    rosidl_generator_traits::value_to_yaml(msg.ax, out);
    out << ", ";
  }

  // member: sas
  {
    out << "sas: ";
    rosidl_generator_traits::value_to_yaml(msg.sas, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HostVehicleFilter & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: vx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vx: ";
    rosidl_generator_traits::value_to_yaml(msg.vx, out);
    out << "\n";
  }

  // member: yawrate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yawrate: ";
    rosidl_generator_traits::value_to_yaml(msg.yawrate, out);
    out << "\n";
  }

  // member: ax
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ax: ";
    rosidl_generator_traits::value_to_yaml(msg.ax, out);
    out << "\n";
  }

  // member: sas
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sas: ";
    rosidl_generator_traits::value_to_yaml(msg.sas, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HostVehicleFilter & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace umv_msgs

namespace rosidl_generator_traits
{

[[deprecated("use umv_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const umv_msgs::msg::HostVehicleFilter & msg,
  std::ostream & out, size_t indentation = 0)
{
  umv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use umv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const umv_msgs::msg::HostVehicleFilter & msg)
{
  return umv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<umv_msgs::msg::HostVehicleFilter>()
{
  return "umv_msgs::msg::HostVehicleFilter";
}

template<>
inline const char * name<umv_msgs::msg::HostVehicleFilter>()
{
  return "umv_msgs/msg/HostVehicleFilter";
}

template<>
struct has_fixed_size<umv_msgs::msg::HostVehicleFilter>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<umv_msgs::msg::HostVehicleFilter>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<umv_msgs::msg::HostVehicleFilter>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__TRAITS_HPP_
