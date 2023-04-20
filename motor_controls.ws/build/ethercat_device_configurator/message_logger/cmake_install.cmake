# Install script for directory: /home/hd/Desktop/motor_controls.ws/src/ethercat_device_configurator/message_logger

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hd/Desktop/motor_controls.ws/install/ethercat_device_configurator")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/message_logger/libmessage_logger.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so"
         OLD_RPATH "/home/hd/ros2_foxy/install/rclcpp/lib:/home/hd/ros2_foxy/install/libstatistics_collector/lib:/home/hd/ros2_foxy/install/std_msgs/lib:/home/hd/ros2_foxy/install/rcl/lib:/home/hd/ros2_foxy/install/rcl_interfaces/lib:/home/hd/ros2_foxy/install/rmw_implementation/lib:/home/hd/ros2_foxy/install/rmw/lib:/home/hd/ros2_foxy/install/rcl_logging_spdlog/lib:/home/hd/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/hd/ros2_foxy/install/libyaml_vendor/lib:/home/hd/ros2_foxy/install/rosgraph_msgs/lib:/home/hd/ros2_foxy/install/statistics_msgs/lib:/home/hd/ros2_foxy/install/builtin_interfaces/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_c/lib:/home/hd/ros2_foxy/install/rcpputils/lib:/home/hd/ros2_foxy/install/rosidl_runtime_c/lib:/home/hd/ros2_foxy/install/rcutils/lib:/home/hd/ros2_foxy/install/tracetools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmessage_logger.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/message_logger" TYPE DIRECTORY FILES "/home/hd/Desktop/motor_controls.ws/src/ethercat_device_configurator/message_logger/include/message_logger/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/environment" TYPE FILE FILES "/home/hd/ros2_foxy/build/ament_package/ament_package/template/environment_hook/library_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/environment" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/library_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/message_logger")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/message_logger")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/environment" TYPE FILE FILES "/home/hd/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/environment" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/environment" TYPE FILE FILES "/home/hd/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/environment" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_index/share/ament_index/resource_index/packages/message_logger")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/cmake" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/message_logger/ament_cmake_export_include_directories/ament_cmake_export_include_directories-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/cmake" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/message_logger/ament_cmake_export_libraries/ament_cmake_export_libraries-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger/cmake" TYPE FILE FILES
    "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/message_logger/ament_cmake_core/message_loggerConfig.cmake"
    "/home/hd/Desktop/motor_controls.ws/build/ethercat_device_configurator/message_logger/ament_cmake_core/message_loggerConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_logger" TYPE FILE FILES "/home/hd/Desktop/motor_controls.ws/src/ethercat_device_configurator/message_logger/package.xml")
endif()

