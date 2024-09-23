// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from umv_msgs:msg/GlobalPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__TRAITS_HPP_
#define UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "umv_msgs/msg/detail/global_path__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace umv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const GlobalPath & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: global_xs
  {
    if (msg.global_xs.size() == 0) {
      out << "global_xs: []";
    } else {
      out << "global_xs: [";
      size_t pending_items = msg.global_xs.size();
      for (auto item : msg.global_xs) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: global_ys
  {
    if (msg.global_ys.size() == 0) {
      out << "global_ys: []";
    } else {
      out << "global_ys: [";
      size_t pending_items = msg.global_ys.size();
      for (auto item : msg.global_ys) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: distance_interval
  {
    out << "distance_interval: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_interval, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GlobalPath & msg,
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

  // member: global_xs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.global_xs.size() == 0) {
      out << "global_xs: []\n";
    } else {
      out << "global_xs:\n";
      for (auto item : msg.global_xs) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: global_ys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.global_ys.size() == 0) {
      out << "global_ys: []\n";
    } else {
      out << "global_ys:\n";
      for (auto item : msg.global_ys) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: distance_interval
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_interval: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_interval, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GlobalPath & msg, bool use_flow_style = false)
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
  const umv_msgs::msg::GlobalPath & msg,
  std::ostream & out, size_t indentation = 0)
{
  umv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use umv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const umv_msgs::msg::GlobalPath & msg)
{
  return umv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<umv_msgs::msg::GlobalPath>()
{
  return "umv_msgs::msg::GlobalPath";
}

template<>
inline const char * name<umv_msgs::msg::GlobalPath>()
{
  return "umv_msgs/msg/GlobalPath";
}

template<>
struct has_fixed_size<umv_msgs::msg::GlobalPath>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<umv_msgs::msg::GlobalPath>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<umv_msgs::msg::GlobalPath>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__TRAITS_HPP_
