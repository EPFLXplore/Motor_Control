cmake_minimum_required(VERSION 3.5)
project(message_logger LANGUAGES CXX)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

message(" AHHHHHHHHHHHHHHHHHH ${PROJECT_NAME}")

# Configure header file
configure_file(
  include/message_logger/log/log_messages_backend_config.hpp.in
  ${PROJECT_BINARY_DIR}/include/message_logger/log/log_messages_backend_config.hpp
)

# Add include directories
include_directories(
  include
  ${PROJECT_BINARY_DIR}/include
)

# Create a shared library
add_library(${PROJECT_NAME} SHARED
  src/time/Time.cpp
  src/time/TimeStd.cpp
)

# Link with ROS2 libraries
ament_target_dependencies(${PROJECT_NAME}
  "rclcpp"
  "std_msgs"
)

# Install library and header files
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)


# Add environment hooks
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_package()
