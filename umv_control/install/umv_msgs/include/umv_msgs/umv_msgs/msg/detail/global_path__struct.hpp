// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from umv_msgs:msg/GlobalPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__STRUCT_HPP_
#define UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__umv_msgs__msg__GlobalPath __attribute__((deprecated))
#else
# define DEPRECATED__umv_msgs__msg__GlobalPath __declspec(deprecated)
#endif

namespace umv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GlobalPath_
{
  using Type = GlobalPath_<ContainerAllocator>;

  explicit GlobalPath_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance_interval = 0.0;
    }
  }

  explicit GlobalPath_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance_interval = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _global_xs_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _global_xs_type global_xs;
  using _global_ys_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _global_ys_type global_ys;
  using _distance_interval_type =
    double;
  _distance_interval_type distance_interval;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__global_xs(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->global_xs = _arg;
    return *this;
  }
  Type & set__global_ys(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->global_ys = _arg;
    return *this;
  }
  Type & set__distance_interval(
    const double & _arg)
  {
    this->distance_interval = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    umv_msgs::msg::GlobalPath_<ContainerAllocator> *;
  using ConstRawPtr =
    const umv_msgs::msg::GlobalPath_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::GlobalPath_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::GlobalPath_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__umv_msgs__msg__GlobalPath
    std::shared_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__umv_msgs__msg__GlobalPath
    std::shared_ptr<umv_msgs::msg::GlobalPath_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GlobalPath_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->global_xs != other.global_xs) {
      return false;
    }
    if (this->global_ys != other.global_ys) {
      return false;
    }
    if (this->distance_interval != other.distance_interval) {
      return false;
    }
    return true;
  }
  bool operator!=(const GlobalPath_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GlobalPath_

// alias to use template instance with default allocator
using GlobalPath =
  umv_msgs::msg::GlobalPath_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__GLOBAL_PATH__STRUCT_HPP_
