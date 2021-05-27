cmake_minimum_required(VERSION 3.0.2)
project(image_undistort)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  cv_bridge
)

catkin_package()


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

find_package(Eigen3)
find_package(OpenCV REQUIRED)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

add_executable(image_undistort_node
    src/image_undistort_node.cpp
    )

target_link_libraries(image_undistort_node ${catkin_LIBRARIES} ${OpenCV_LIBS})