// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from umv_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_HPP_
#define UMV_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_HPP_

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
# define DEPRECATED__umv_msgs__msg__Obstacles __attribute__((deprecated))
#else
# define DEPRECATED__umv_msgs__msg__Obstacles __declspec(deprecated)
#endif

namespace umv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Obstacles_
{
  using Type = Obstacles_<ContainerAllocator>;

  explicit Obstacles_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->obs_cnt = 0l;
    }
  }

  explicit Obstacles_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->obs_cnt = 0l;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _obs_cnt_type =
    int32_t;
  _obs_cnt_type obs_cnt;
  using _obs_xs_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _obs_xs_type obs_xs;
  using _obs_ys_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _obs_ys_type obs_ys;
  using _obs_ss_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _obs_ss_type obs_ss;
  using _obs_eys_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _obs_eys_type obs_eys;
  using _obs_eyaws_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _obs_eyaws_type obs_eyaws;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__obs_cnt(
    const int32_t & _arg)
  {
    this->obs_cnt = _arg;
    return *this;
  }
  Type & set__obs_xs(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->obs_xs = _arg;
    return *this;
  }
  Type & set__obs_ys(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->obs_ys = _arg;
    return *this;
  }
  Type & set__obs_ss(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->obs_ss = _arg;
    return *this;
  }
  Type & set__obs_eys(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->obs_eys = _arg;
    return *this;
  }
  Type & set__obs_eyaws(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->obs_eyaws = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    umv_msgs::msg::Obstacles_<ContainerAllocator> *;
  using ConstRawPtr =
    const umv_msgs::msg::Obstacles_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::Obstacles_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::Obstacles_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__umv_msgs__msg__Obstacles
    std::shared_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__umv_msgs__msg__Obstacles
    std::shared_ptr<umv_msgs::msg::Obstacles_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Obstacles_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->obs_cnt != other.obs_cnt) {
      return false;
    }
    if (this->obs_xs != other.obs_xs) {
      return false;
    }
    if (this->obs_ys != other.obs_ys) {
      return false;
    }
    if (this->obs_ss != other.obs_ss) {
      return false;
    }
    if (this->obs_eys != other.obs_eys) {
      return false;
    }
    if (this->obs_eyaws != other.obs_eyaws) {
      return false;
    }
    return true;
  }
  bool operator!=(const Obstacles_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Obstacles_

// alias to use template instance with default allocator
using Obstacles =
  umv_msgs::msg::Obstacles_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_HPP_
