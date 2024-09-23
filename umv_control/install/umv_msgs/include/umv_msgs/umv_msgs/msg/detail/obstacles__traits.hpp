// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__OBSTACLES__TRAITS_HPP_
#define UMV_MSGS__MSG__DETAIL__OBSTACLES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "umv_msgs/msg/detail/obstacles__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace umv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Obstacles & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: obs_cnt
  {
    out << "obs_cnt: ";
    rosidl_generator_traits::value_to_yaml(msg.obs_cnt, out);
    out << ", ";
  }

  // member: obs_xs
  {
    if (msg.obs_xs.size() == 0) {
      out << "obs_xs: []";
    } else {
      out << "obs_xs: [";
      size_t pending_items = msg.obs_xs.size();
      for (auto item : msg.obs_xs) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: obs_ys
  {
    if (msg.obs_ys.size() == 0) {
      out << "obs_ys: []";
    } else {
      out << "obs_ys: [";
      size_t pending_items = msg.obs_ys.size();
      for (auto item : msg.obs_ys) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: obs_ss
  {
    if (msg.obs_ss.size() == 0) {
      out << "obs_ss: []";
    } else {
      out << "obs_ss: [";
      size_t pending_items = msg.obs_ss.size();
      for (auto item : msg.obs_ss) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: obs_eys
  {
    if (msg.obs_eys.size() == 0) {
      out << "obs_eys: []";
    } else {
      out << "obs_eys: [";
      size_t pending_items = msg.obs_eys.size();
      for (auto item : msg.obs_eys) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: obs_eyaws
  {
    if (msg.obs_eyaws.size() == 0) {
      out << "obs_eyaws: []";
    } else {
      out << "obs_eyaws: [";
      size_t pending_items = msg.obs_eyaws.size();
      for (auto item : msg.obs_eyaws) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Obstacles & msg,
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

  // member: obs_cnt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "obs_cnt: ";
    rosidl_generator_traits::value_to_yaml(msg.obs_cnt, out);
    out << "\n";
  }

  // member: obs_xs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.obs_xs.size() == 0) {
      out << "obs_xs: []\n";
    } else {
      out << "obs_xs:\n";
      for (auto item : msg.obs_xs) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: obs_ys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.obs_ys.size() == 0) {
      out << "obs_ys: []\n";
    } else {
      out << "obs_ys:\n";
      for (auto item : msg.obs_ys) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: obs_ss
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.obs_ss.size() == 0) {
      out << "obs_ss: []\n";
    } else {
      out << "obs_ss:\n";
      for (auto item : msg.obs_ss) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: obs_eys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.obs_eys.size() == 0) {
      out << "obs_eys: []\n";
    } else {
      out << "obs_eys:\n";
      for (auto item : msg.obs_eys) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: obs_eyaws
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.obs_eyaws.size() == 0) {
      out << "obs_eyaws: []\n";
    } else {
      out << "obs_eyaws:\n";
      for (auto item : msg.obs_eyaws) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Obstacles & msg, bool use_flow_style = false)
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
  const umv_msgs::msg::Obstacles & msg,
  std::ostream & out, size_t indentation = 0)
{
  umv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use umv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const umv_msgs::msg::Obstacles & msg)
{
  return umv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<umv_msgs::msg::Obstacles>()
{
  return "umv_msgs::msg::Obstacles";
}

template<>
inline const char * name<umv_msgs::msg::Obstacles>()
{
  return "umv_msgs/msg/Obstacles";
}

template<>
struct has_fixed_size<umv_msgs::msg::Obstacles>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<umv_msgs::msg::Obstacles>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<umv_msgs::msg::Obstacles>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UMV_MSGS__MSG__DETAIL__OBSTACLES__TRAITS_HPP_
