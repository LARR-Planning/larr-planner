cmake_minimum_required(VERSION 3.5)
project(larr_planner)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_CXX_STANDARD 17)
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED COMPONENTS common)

file(GLOB_RECURSE LIBRARY_HDRS "include/larr_planner/*.h")
file(GLOB_RECURSE LIBRARY_SRCS "src/*.cc")

add_library(${PROJECT_NAME} STATIC ${LIBRARY_SRCS} ${LIBRARY_HDRS})
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} pthread)
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC ${EIGEN_INCLUDE_DIR} ${PCL_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION .)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config)
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)