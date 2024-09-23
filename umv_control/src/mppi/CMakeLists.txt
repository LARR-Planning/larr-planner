cmake_minimum_required(VERSION 3.8)
project(mppi CUDA CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(umv_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# cuda
find_package(CUDA REQUIRED)


# include 디렉토리 설정
include_directories(
  include
  ${CUDA_INCLUDE_DIRS}
)
include(FindCUDA)


# CUDA를 사용하여 컴파일될 소스 파일
set(CUDA_SOURCE_FILES 
    src/yj_utils_project2_origin.cu
    # src/yj_utils_project.cu
    # src/hello.cu
)

# C++를 사용하여 컴파일될 소스 파일
set(CPP_SOURCE_FILES
    src/mppi.cpp
)


# 빌드된 실행 파일 이름 설정
set(EXECUTABLE_NAME mppi_manager)


# CUDA 컴파일러 및 플래그 설정
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)


# 실행 파일 생성
add_executable(${EXECUTABLE_NAME} 
  ${CPP_SOURCE_FILES} 
  ${CUDA_SOURCE_FILES}
)
ament_target_dependencies(mppi_manager rclcpp std_msgs umv_msgs sensor_msgs)


# 헤더 파일 설치
# install(DIRECTORY include/${PROJECT_NAME}/
#  DESTINATION include/${PROJECT_NAME}
# )

# 실행 파일 설치
# install(TARGETS mppi_manager
#   DESTINATION lib/${PROJECT_NAME}
# )


target_include_directories(mppi_manager PUBLIC
    include
    /usr/local/cuda-12.2/include
)

# add_dependencies(mppi_manager ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mppi_manager
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${OpenCV_LIBS} 
  ${CUDA_LIBRARIES}
  
  /usr/local/cuda-12.2/include
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
