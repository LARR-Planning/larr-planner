// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__TRAITS_HPP_
#define UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "umv_msgs/msg/detail/local_ref_path__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace umv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const LocalRefPath & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: local_ref_xs
  {
    if (msg.local_ref_xs.size() == 0) {
      out << "local_ref_xs: []";
    } else {
      out << "local_ref_xs: [";
      size_t pending_items = msg.local_ref_xs.size();
      for (auto item : msg.local_ref_xs) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: local_ref_ys
  {
    if (msg.local_ref_ys.size() == 0) {
      out << "local_ref_ys: []";
    } else {
      out << "local_ref_ys: [";
      size_t pending_items = msg.local_ref_ys.size();
      for (auto item : msg.local_ref_ys) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: local_ref_ss
  {
    if (msg.local_ref_ss.size() == 0) {
      out << "local_ref_ss: []";
    } else {
      out << "local_ref_ss: [";
      size_t pending_items = msg.local_ref_ss.size();
      for (auto item : msg.local_ref_ss) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: local_ref_yaws
  {
    if (msg.local_ref_yaws.size() == 0) {
      out << "local_ref_yaws: []";
    } else {
      out << "local_ref_yaws: [";
      size_t pending_items = msg.local_ref_yaws.size();
      for (auto item : msg.local_ref_yaws) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: local_ref_curvs
  {
    if (msg.local_ref_curvs.size() == 0) {
      out << "local_ref_curvs: []";
    } else {
      out << "local_ref_curvs: [";
      size_t pending_items = msg.local_ref_curvs.size();
      for (auto item : msg.local_ref_curvs) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: ey
  {
    out << "ey: ";
    rosidl_generator_traits::value_to_yaml(msg.ey, out);
    out << ", ";
  }

  // member: eyaw
  {
    out << "eyaw: ";
    rosidl_generator_traits::value_to_yaml(msg.eyaw, out);
    out << ", ";
  }

  // member: ego_s
  {
    out << "ego_s: ";
    rosidl_generator_traits::value_to_yaml(msg.ego_s, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocalRefPath & msg,
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

  // member: local_ref_xs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.local_ref_xs.size() == 0) {
      out << "local_ref_xs: []\n";
    } else {
      out << "local_ref_xs:\n";
      for (auto item : msg.local_ref_xs) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: local_ref_ys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.local_ref_ys.size() == 0) {
      out << "local_ref_ys: []\n";
    } else {
      out << "local_ref_ys:\n";
      for (auto item : msg.local_ref_ys) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: local_ref_ss
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.local_ref_ss.size() == 0) {
      out << "local_ref_ss: []\n";
    } else {
      out << "local_ref_ss:\n";
      for (auto item : msg.local_ref_ss) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: local_ref_yaws
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.local_ref_yaws.size() == 0) {
      out << "local_ref_yaws: []\n";
    } else {
      out << "local_ref_yaws:\n";
      for (auto item : msg.local_ref_yaws) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: local_ref_curvs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.local_ref_curvs.size() == 0) {
      out << "local_ref_curvs: []\n";
    } else {
      out << "local_ref_curvs:\n";
      for (auto item : msg.local_ref_curvs) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: ey
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ey: ";
    rosidl_generator_traits::value_to_yaml(msg.ey, out);
    out << "\n";
  }

  // member: eyaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eyaw: ";
    rosidl_generator_traits::value_to_yaml(msg.eyaw, out);
    out << "\n";
  }

  // member: ego_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ego_s: ";
    rosidl_generator_traits::value_to_yaml(msg.ego_s, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocalRefPath & msg, bool use_flow_style = false)
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
  const umv_msgs::msg::LocalRefPath & msg,
  std::ostream & out, size_t indentation = 0)
{
  umv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use umv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const umv_msgs::msg::LocalRefPath & msg)
{
  return umv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<umv_msgs::msg::LocalRefPath>()
{
  return "umv_msgs::msg::LocalRefPath";
}

template<>
inline const char * name<umv_msgs::msg::LocalRefPath>()
{
  return "umv_msgs/msg/LocalRefPath";
}

template<>
struct has_fixed_size<umv_msgs::msg::LocalRefPath>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<umv_msgs::msg::LocalRefPath>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<umv_msgs::msg::LocalRefPath>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__TRAITS_HPP_
