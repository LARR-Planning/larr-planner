// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from umv_msgs:msg/AcuCmd.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__ACU_CMD__FUNCTIONS_H_
#define UMV_MSGS__MSG__DETAIL__ACU_CMD__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "umv_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "umv_msgs/msg/detail/acu_cmd__struct.h"

/// Initialize msg/AcuCmd message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * umv_msgs__msg__AcuCmd
 * )) before or use
 * umv_msgs__msg__AcuCmd__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__AcuCmd__init(umv_msgs__msg__AcuCmd * msg);

/// Finalize msg/AcuCmd message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__AcuCmd__fini(umv_msgs__msg__AcuCmd * msg);

/// Create msg/AcuCmd message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * umv_msgs__msg__AcuCmd__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
umv_msgs__msg__AcuCmd *
umv_msgs__msg__AcuCmd__create();

/// Destroy msg/AcuCmd message.
/**
 * It calls
 * umv_msgs__msg__AcuCmd__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__AcuCmd__destroy(umv_msgs__msg__AcuCmd * msg);

/// Check for msg/AcuCmd message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__AcuCmd__are_equal(const umv_msgs__msg__AcuCmd * lhs, const umv_msgs__msg__AcuCmd * rhs);

/// Copy a msg/AcuCmd message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__AcuCmd__copy(
  const umv_msgs__msg__AcuCmd * input,
  umv_msgs__msg__AcuCmd * output);

/// Initialize array of msg/AcuCmd messages.
/**
 * It allocates the memory for the number of elements and calls
 * umv_msgs__msg__AcuCmd__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__AcuCmd__Sequence__init(umv_msgs__msg__AcuCmd__Sequence * array, size_t size);

/// Finalize array of msg/AcuCmd messages.
/**
 * It calls
 * umv_msgs__msg__AcuCmd__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__AcuCmd__Sequence__fini(umv_msgs__msg__AcuCmd__Sequence * array);

/// Create array of msg/AcuCmd messages.
/**
 * It allocates the memory for the array and calls
 * umv_msgs__msg__AcuCmd__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
umv_msgs__msg__AcuCmd__Sequence *
umv_msgs__msg__AcuCmd__Sequence__create(size_t size);

/// Destroy array of msg/AcuCmd messages.
/**
 * It calls
 * umv_msgs__msg__AcuCmd__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__AcuCmd__Sequence__destroy(umv_msgs__msg__AcuCmd__Sequence * array);

/// Check for msg/AcuCmd message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__AcuCmd__Sequence__are_equal(const umv_msgs__msg__AcuCmd__Sequence * lhs, const umv_msgs__msg__AcuCmd__Sequence * rhs);

/// Copy an array of msg/AcuCmd messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__AcuCmd__Sequence__copy(
  const umv_msgs__msg__AcuCmd__Sequence * input,
  umv_msgs__msg__AcuCmd__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UMV_MSGS__MSG__DETAIL__ACU_CMD__FUNCTIONS_H_
