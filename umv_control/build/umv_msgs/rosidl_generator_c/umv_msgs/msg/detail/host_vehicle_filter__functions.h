// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from umv_msgs:msg/HostVehicleFilter.idl
// generated code does not contain a copyright notice

#ifndef UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__FUNCTIONS_H_
#define UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "umv_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "umv_msgs/msg/detail/host_vehicle_filter__struct.h"

/// Initialize msg/HostVehicleFilter message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * umv_msgs__msg__HostVehicleFilter
 * )) before or use
 * umv_msgs__msg__HostVehicleFilter__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__HostVehicleFilter__init(umv_msgs__msg__HostVehicleFilter * msg);

/// Finalize msg/HostVehicleFilter message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__HostVehicleFilter__fini(umv_msgs__msg__HostVehicleFilter * msg);

/// Create msg/HostVehicleFilter message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * umv_msgs__msg__HostVehicleFilter__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
umv_msgs__msg__HostVehicleFilter *
umv_msgs__msg__HostVehicleFilter__create();

/// Destroy msg/HostVehicleFilter message.
/**
 * It calls
 * umv_msgs__msg__HostVehicleFilter__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__HostVehicleFilter__destroy(umv_msgs__msg__HostVehicleFilter * msg);

/// Check for msg/HostVehicleFilter message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__HostVehicleFilter__are_equal(const umv_msgs__msg__HostVehicleFilter * lhs, const umv_msgs__msg__HostVehicleFilter * rhs);

/// Copy a msg/HostVehicleFilter message.
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
umv_msgs__msg__HostVehicleFilter__copy(
  const umv_msgs__msg__HostVehicleFilter * input,
  umv_msgs__msg__HostVehicleFilter * output);

/// Initialize array of msg/HostVehicleFilter messages.
/**
 * It allocates the memory for the number of elements and calls
 * umv_msgs__msg__HostVehicleFilter__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__HostVehicleFilter__Sequence__init(umv_msgs__msg__HostVehicleFilter__Sequence * array, size_t size);

/// Finalize array of msg/HostVehicleFilter messages.
/**
 * It calls
 * umv_msgs__msg__HostVehicleFilter__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__HostVehicleFilter__Sequence__fini(umv_msgs__msg__HostVehicleFilter__Sequence * array);

/// Create array of msg/HostVehicleFilter messages.
/**
 * It allocates the memory for the array and calls
 * umv_msgs__msg__HostVehicleFilter__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
umv_msgs__msg__HostVehicleFilter__Sequence *
umv_msgs__msg__HostVehicleFilter__Sequence__create(size_t size);

/// Destroy array of msg/HostVehicleFilter messages.
/**
 * It calls
 * umv_msgs__msg__HostVehicleFilter__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
void
umv_msgs__msg__HostVehicleFilter__Sequence__destroy(umv_msgs__msg__HostVehicleFilter__Sequence * array);

/// Check for msg/HostVehicleFilter message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_umv_msgs
bool
umv_msgs__msg__HostVehicleFilter__Sequence__are_equal(const umv_msgs__msg__HostVehicleFilter__Sequence * lhs, const umv_msgs__msg__HostVehicleFilter__Sequence * rhs);

/// Copy an array of msg/HostVehicleFilter messages.
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
umv_msgs__msg__HostVehicleFilter__Sequence__copy(
  const umv_msgs__msg__HostVehicleFilter__Sequence * input,
  umv_msgs__msg__HostVehicleFilter__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UMV_MSGS__MSG__DETAIL__HOST_VEHICLE_FILTER__FUNCTIONS_H_
