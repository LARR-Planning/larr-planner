// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__STRUCT_HPP_
#define UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__STRUCT_HPP_

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
# define DEPRECATED__umv_msgs__msg__LocalRefPath __attribute__((deprecated))
#else
# define DEPRECATED__umv_msgs__msg__LocalRefPath __declspec(deprecated)
#endif

namespace umv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LocalRefPath_
{
  using Type = LocalRefPath_<ContainerAllocator>;

  explicit LocalRefPath_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ey = 0.0;
      this->eyaw = 0.0;
      this->ego_s = 0.0;
    }
  }

  explicit LocalRefPath_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ey = 0.0;
      this->eyaw = 0.0;
      this->ego_s = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _local_ref_xs_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _local_ref_xs_type local_ref_xs;
  using _local_ref_ys_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _local_ref_ys_type local_ref_ys;
  using _local_ref_ss_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _local_ref_ss_type local_ref_ss;
  using _local_ref_yaws_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _local_ref_yaws_type local_ref_yaws;
  using _local_ref_curvs_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _local_ref_curvs_type local_ref_curvs;
  using _ey_type =
    double;
  _ey_type ey;
  using _eyaw_type =
    double;
  _eyaw_type eyaw;
  using _ego_s_type =
    double;
  _ego_s_type ego_s;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__local_ref_xs(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->local_ref_xs = _arg;
    return *this;
  }
  Type & set__local_ref_ys(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->local_ref_ys = _arg;
    return *this;
  }
  Type & set__local_ref_ss(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->local_ref_ss = _arg;
    return *this;
  }
  Type & set__local_ref_yaws(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->local_ref_yaws = _arg;
    return *this;
  }
  Type & set__local_ref_curvs(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->local_ref_curvs = _arg;
    return *this;
  }
  Type & set__ey(
    const double & _arg)
  {
    this->ey = _arg;
    return *this;
  }
  Type & set__eyaw(
    const double & _arg)
  {
    this->eyaw = _arg;
    return *this;
  }
  Type & set__ego_s(
    const double & _arg)
  {
    this->ego_s = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    umv_msgs::msg::LocalRefPath_<ContainerAllocator> *;
  using ConstRawPtr =
    const umv_msgs::msg::LocalRefPath_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::LocalRefPath_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::LocalRefPath_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__umv_msgs__msg__LocalRefPath
    std::shared_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__umv_msgs__msg__LocalRefPath
    std::shared_ptr<umv_msgs::msg::LocalRefPath_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalRefPath_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->local_ref_xs != other.local_ref_xs) {
      return false;
    }
    if (this->local_ref_ys != other.local_ref_ys) {
      return false;
    }
    if (this->local_ref_ss != other.local_ref_ss) {
      return false;
    }
    if (this->local_ref_yaws != other.local_ref_yaws) {
      return false;
    }
    if (this->local_ref_curvs != other.local_ref_curvs) {
      return false;
    }
    if (this->ey != other.ey) {
      return false;
    }
    if (this->eyaw != other.eyaw) {
      return false;
    }
    if (this->ego_s != other.ego_s) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocalRefPath_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalRefPath_

// alias to use template instance with default allocator
using LocalRefPath =
  umv_msgs::msg::LocalRefPath_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__LOCAL_REF_PATH__STRUCT_HPP_
