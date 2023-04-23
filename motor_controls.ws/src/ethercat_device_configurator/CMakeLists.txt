cmake_minimum_required(VERSION 3.8)
project(ethercat_device_configurator)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -std=c++1z -Wno-error)
endif()

# find dependencies
find_package(rclcpp REQUIRED)
#find_package(yaml-cpp REQUIRED)
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


find_package(message_logger)
find_package(soem_interface)
find_package(ethercat_sdk_master)
find_package(maxon_epos_ethercat_sdk)

add_subdirectory(yaml-cpp/yaml-cpp)
add_subdirectory(ethercat_sdk_master)
add_subdirectory(maxon_epos_ethercat_sdk)
add_subdirectory(message_logger)
add_subdirectory(soem_interface/soem)
add_subdirectory(soem_interface/soem_interface)

include_directories( 
  include
  include/ethercat_device_configurator
  ${rclcpp_INCLUDE_DIRS}
)

find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/motor_command.msg"
  "msg/motor_param.msg"
)

add_executable(standalone src/standalone.cpp src/EthercatDeviceConfigurator.cpp 
  include/ethercat_device_configurator/soem/soem/ethercatconfig.c
  include/ethercat_device_configurator/soem/soem/ethercatprint.c
  include/ethercat_device_configurator/soem/soem/ethercatdc.c)
  
#ament_target_dependencies(standalone rclcpp yaml-cpp)
target_link_libraries(standalone
  PUBLIC
  ${rclcpp_LIBRARIES}
  PRIVATE
  yaml-cpp
  ethercat_sdk_master
  maxon_epos_ethercat_sdk
  message_logger
  soem
  soem_interface
)

install(TARGETS standalone
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  #ament_lint_auto_find_test_dependencies()
endif()

ament_package()
