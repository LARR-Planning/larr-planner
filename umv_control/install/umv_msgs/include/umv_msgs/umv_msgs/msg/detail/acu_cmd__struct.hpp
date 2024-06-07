// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from umv_msgs:msg/AcuCmd.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__ACU_CMD__STRUCT_HPP_
#define UMV_MSGS__MSG__DETAIL__ACU_CMD__STRUCT_HPP_

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
# define DEPRECATED__umv_msgs__msg__AcuCmd __attribute__((deprecated))
#else
# define DEPRECATED__umv_msgs__msg__AcuCmd __declspec(deprecated)
#endif

namespace umv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AcuCmd_
{
  using Type = AcuCmd_<ContainerAllocator>;

  explicit AcuCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ax = 0.0f;
      this->sas = 0.0f;
    }
  }

  explicit AcuCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ax = 0.0f;
      this->sas = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _ax_type =
    float;
  _ax_type ax;
  using _sas_type =
    float;
  _sas_type sas;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__ax(
    const float & _arg)
  {
    this->ax = _arg;
    return *this;
  }
  Type & set__sas(
    const float & _arg)
  {
    this->sas = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    umv_msgs::msg::AcuCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const umv_msgs::msg::AcuCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::AcuCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      umv_msgs::msg::AcuCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__umv_msgs__msg__AcuCmd
    std::shared_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__umv_msgs__msg__AcuCmd
    std::shared_ptr<umv_msgs::msg::AcuCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AcuCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->ax != other.ax) {
      return false;
    }
    if (this->sas != other.sas) {
      return false;
    }
    return true;
  }
  bool operator!=(const AcuCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AcuCmd_

// alias to use template instance with default allocator
using AcuCmd =
  umv_msgs::msg::AcuCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace umv_msgs

#endif  // UMV_MSGS__MSG__DETAIL__ACU_CMD__STRUCT_HPP_
