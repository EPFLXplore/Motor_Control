cmake_minimum_required(VERSION 3.5)
project(coucou)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/send.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})


add_executable(suscriber src/read.cpp)
ament_target_dependencies(suscriber rclcpp std_msgs)

install(TARGETS
  suscriber
  DESTINATION lib/${PROJECT_NAME})
  

ament_package()
