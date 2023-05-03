# Install script for directory: /home/hd/Desktop/Motor_Control/motor_controls.ws/src/coucou

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hd/Desktop/Motor_Control/motor_controls.ws/install/coucou")
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/coucou" TYPE EXECUTABLE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/talker")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker"
         OLD_RPATH "/home/hd/ros2_foxy/install/rclcpp/lib:/home/hd/Desktop/Motor_Control/motor_controls.ws/install/motor_control_interfaces/lib:/home/hd/ros2_foxy/install/libstatistics_collector/lib:/home/hd/ros2_foxy/install/std_msgs/lib:/home/hd/ros2_foxy/install/rcl/lib:/home/hd/ros2_foxy/install/rcl_interfaces/lib:/home/hd/ros2_foxy/install/rmw_implementation/lib:/home/hd/ros2_foxy/install/rmw/lib:/home/hd/ros2_foxy/install/rcl_logging_spdlog/lib:/home/hd/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/hd/ros2_foxy/install/libyaml_vendor/lib:/home/hd/ros2_foxy/install/rosgraph_msgs/lib:/home/hd/ros2_foxy/install/statistics_msgs/lib:/home/hd/ros2_foxy/install/builtin_interfaces/lib:/home/hd/ros2_foxy/install/tracetools/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_c/lib:/home/hd/ros2_foxy/install/rcpputils/lib:/home/hd/ros2_foxy/install/rosidl_runtime_c/lib:/home/hd/ros2_foxy/install/rcutils/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/talker")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/coucou" TYPE EXECUTABLE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/suscriber")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber"
         OLD_RPATH "/home/hd/ros2_foxy/install/rclcpp/lib:/home/hd/ros2_foxy/install/sensor_msgs/lib:/home/hd/Desktop/Motor_Control/motor_controls.ws/install/motor_control_interfaces/lib:/home/hd/ros2_foxy/install/libstatistics_collector/lib:/home/hd/ros2_foxy/install/rcl/lib:/home/hd/ros2_foxy/install/rcl_interfaces/lib:/home/hd/ros2_foxy/install/rmw_implementation/lib:/home/hd/ros2_foxy/install/rmw/lib:/home/hd/ros2_foxy/install/rcl_logging_spdlog/lib:/home/hd/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/hd/ros2_foxy/install/libyaml_vendor/lib:/home/hd/ros2_foxy/install/rosgraph_msgs/lib:/home/hd/ros2_foxy/install/statistics_msgs/lib:/home/hd/ros2_foxy/install/tracetools/lib:/home/hd/ros2_foxy/install/geometry_msgs/lib:/home/hd/ros2_foxy/install/std_msgs/lib:/home/hd/ros2_foxy/install/builtin_interfaces/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_c/lib:/home/hd/ros2_foxy/install/rcpputils/lib:/home/hd/ros2_foxy/install/rosidl_runtime_c/lib:/home/hd/ros2_foxy/install/rcutils/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/coucou" TYPE EXECUTABLE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/suscriber_test")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test"
         OLD_RPATH "/home/hd/ros2_foxy/install/rclcpp/lib:/home/hd/Desktop/Motor_Control/motor_controls.ws/install/motor_control_interfaces/lib:/home/hd/ros2_foxy/install/libstatistics_collector/lib:/home/hd/ros2_foxy/install/std_msgs/lib:/home/hd/ros2_foxy/install/rcl/lib:/home/hd/ros2_foxy/install/rcl_interfaces/lib:/home/hd/ros2_foxy/install/rmw_implementation/lib:/home/hd/ros2_foxy/install/rmw/lib:/home/hd/ros2_foxy/install/rcl_logging_spdlog/lib:/home/hd/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/hd/ros2_foxy/install/libyaml_vendor/lib:/home/hd/ros2_foxy/install/rosgraph_msgs/lib:/home/hd/ros2_foxy/install/statistics_msgs/lib:/home/hd/ros2_foxy/install/builtin_interfaces/lib:/home/hd/ros2_foxy/install/tracetools/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/hd/ros2_foxy/install/rosidl_typesupport_c/lib:/home/hd/ros2_foxy/install/rcpputils/lib:/home/hd/ros2_foxy/install/rosidl_runtime_c/lib:/home/hd/ros2_foxy/install/rcutils/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/coucou/suscriber_test")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/coucou")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/coucou")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou/environment" TYPE FILE FILES "/home/hd/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou/environment" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou/environment" TYPE FILE FILES "/home/hd/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou/environment" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_index/share/ament_index/resource_index/packages/coucou")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou/cmake" TYPE FILE FILES
    "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_core/coucouConfig.cmake"
    "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/ament_cmake_core/coucouConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/coucou" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/src/coucou/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/coucou/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
