// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from umv_msgs:msg/LocalRefPath.idl
// generated code does not contain a copyright notice
#include "umv_msgs/msg/detail/local_ref_path__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "umv_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "umv_msgs/msg/detail/local_ref_path__struct.h"
#include "umv_msgs/msg/detail/local_ref_path__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // local_ref_curvs, local_ref_ss, local_ref_xs, local_ref_yaws, local_ref_ys
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // local_ref_curvs, local_ref_ss, local_ref_xs, local_ref_yaws, local_ref_ys
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_umv_msgs
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_umv_msgs
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_umv_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _LocalRefPath__ros_msg_type = umv_msgs__msg__LocalRefPath;

static bool _LocalRefPath__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _LocalRefPath__ros_msg_type * ros_message = static_cast<const _LocalRefPath__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: local_ref_xs
  {
    size_t size = ros_message->local_ref_xs.size;
    auto array_ptr = ros_message->local_ref_xs.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: local_ref_ys
  {
    size_t size = ros_message->local_ref_ys.size;
    auto array_ptr = ros_message->local_ref_ys.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: local_ref_ss
  {
    size_t size = ros_message->local_ref_ss.size;
    auto array_ptr = ros_message->local_ref_ss.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: local_ref_yaws
  {
    size_t size = ros_message->local_ref_yaws.size;
    auto array_ptr = ros_message->local_ref_yaws.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: local_ref_curvs
  {
    size_t size = ros_message->local_ref_curvs.size;
    auto array_ptr = ros_message->local_ref_curvs.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: ey
  {
    cdr << ros_message->ey;
  }

  // Field name: eyaw
  {
    cdr << ros_message->eyaw;
  }

  // Field name: ego_s
  {
    cdr << ros_message->ego_s;
  }

  return true;
}

static bool _LocalRefPath__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _LocalRefPath__ros_msg_type * ros_message = static_cast<_LocalRefPath__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: local_ref_xs
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->local_ref_xs.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->local_ref_xs);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->local_ref_xs, size)) {
      fprintf(stderr, "failed to create array for field 'local_ref_xs'");
      return false;
    }
    auto array_ptr = ros_message->local_ref_xs.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: local_ref_ys
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->local_ref_ys.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->local_ref_ys);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->local_ref_ys, size)) {
      fprintf(stderr, "failed to create array for field 'local_ref_ys'");
      return false;
    }
    auto array_ptr = ros_message->local_ref_ys.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: local_ref_ss
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->local_ref_ss.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->local_ref_ss);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->local_ref_ss, size)) {
      fprintf(stderr, "failed to create array for field 'local_ref_ss'");
      return false;
    }
    auto array_ptr = ros_message->local_ref_ss.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: local_ref_yaws
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->local_ref_yaws.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->local_ref_yaws);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->local_ref_yaws, size)) {
      fprintf(stderr, "failed to create array for field 'local_ref_yaws'");
      return false;
    }
    auto array_ptr = ros_message->local_ref_yaws.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: local_ref_curvs
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->local_ref_curvs.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->local_ref_curvs);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->local_ref_curvs, size)) {
      fprintf(stderr, "failed to create array for field 'local_ref_curvs'");
      return false;
    }
    auto array_ptr = ros_message->local_ref_curvs.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: ey
  {
    cdr >> ros_message->ey;
  }

  // Field name: eyaw
  {
    cdr >> ros_message->eyaw;
  }

  // Field name: ego_s
  {
    cdr >> ros_message->ego_s;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_umv_msgs
size_t get_serialized_size_umv_msgs__msg__LocalRefPath(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _LocalRefPath__ros_msg_type * ros_message = static_cast<const _LocalRefPath__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name local_ref_xs
  {
    size_t array_size = ros_message->local_ref_xs.size;
    auto array_ptr = ros_message->local_ref_xs.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_ref_ys
  {
    size_t array_size = ros_message->local_ref_ys.size;
    auto array_ptr = ros_message->local_ref_ys.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_ref_ss
  {
    size_t array_size = ros_message->local_ref_ss.size;
    auto array_ptr = ros_message->local_ref_ss.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_ref_yaws
  {
    size_t array_size = ros_message->local_ref_yaws.size;
    auto array_ptr = ros_message->local_ref_yaws.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_ref_curvs
  {
    size_t array_size = ros_message->local_ref_curvs.size;
    auto array_ptr = ros_message->local_ref_curvs.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ey
  {
    size_t item_size = sizeof(ros_message->ey);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name eyaw
  {
    size_t item_size = sizeof(ros_message->eyaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ego_s
  {
    size_t item_size = sizeof(ros_message->ego_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _LocalRefPath__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_umv_msgs__msg__LocalRefPath(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_umv_msgs
size_t max_serialized_size_umv_msgs__msg__LocalRefPath(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: local_ref_xs
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: local_ref_ys
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: local_ref_ss
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: local_ref_yaws
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: local_ref_curvs
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: ey
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: eyaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: ego_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = umv_msgs__msg__LocalRefPath;
    is_plain =
      (
      offsetof(DataType, ego_s) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _LocalRefPath__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_umv_msgs__msg__LocalRefPath(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_LocalRefPath = {
  "umv_msgs::msg",
  "LocalRefPath",
  _LocalRefPath__cdr_serialize,
  _LocalRefPath__cdr_deserialize,
  _LocalRefPath__get_serialized_size,
  _LocalRefPath__max_serialized_size
};

static rosidl_message_type_support_t _LocalRefPath__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_LocalRefPath,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, umv_msgs, msg, LocalRefPath)() {
  return &_LocalRefPath__type_support;
}

#if defined(__cplusplus)
}
#endif
