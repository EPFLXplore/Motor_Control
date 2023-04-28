# Install script for directory: /home/hd/Desktop/Motor_Control/motor_controls.ws/src/ethercat_device_configurator/maxon_epos_ethercat_sdk

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hd/Desktop/Motor_Control/motor_controls.ws/install/ethercat_device_configurator")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/maxon_epos_ethercat_sdk/libmaxon_epos_ethercat_sdk.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/maxon_epos_ethercat_sdk" TYPE DIRECTORY FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/src/ethercat_device_configurator/maxon_epos_ethercat_sdk/include/maxon_epos_ethercat_sdk/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/maxon_epos_ethercat_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/maxon_epos_ethercat_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk/environment" TYPE FILE FILES "/home/hd/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk/environment" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk/environment" TYPE FILE FILES "/home/hd/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk/environment" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/ament_cmake_index/share/ament_index/resource_index/packages/maxon_epos_ethercat_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk/cmake" TYPE FILE FILES
    "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/maxon_epos_ethercat_sdk/ament_cmake_core/maxon_epos_ethercat_sdkConfig.cmake"
    "/home/hd/Desktop/Motor_Control/motor_controls.ws/build/ethercat_device_configurator/maxon_epos_ethercat_sdk/ament_cmake_core/maxon_epos_ethercat_sdkConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/maxon_epos_ethercat_sdk" TYPE FILE FILES "/home/hd/Desktop/Motor_Control/motor_controls.ws/src/ethercat_device_configurator/maxon_epos_ethercat_sdk/package.xml")
endif()

