cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
project(soem_rsl)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

if(DEFINED HOST_INSTALL)
   set(SOEM_INCLUDE_INSTALL_DIR include/soem/soem)
else()
   #set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
   set(SOEM_INCLUDE_INSTALL_DIR include)
endif()

if(WIN32)
   set(OS "win32")
   include_directories(include_win32/soem/oshw/wpcap/Include)
   link_directories(${CMAKE_SOURCE_DIR}/include_win32/soem/oshw/wpcap/Lib)
elseif(UNIX)
   set(OS "linux")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "rt-kernel")
   set(OS "rtk")
#   message("ARCH is ${ARCH}")
#   message("BSP is ${BSP}")
   include_directories(include_${OS}/soem/oshw/${ARCH})
   add_definitions("-Wno-unused-but-set-variable")
   add_definitions("-Wno-unused-function")
   add_definitions("-Wno-format")
endif()

include_directories(
  include
  include_${OS}
)

if (MSVC)
  set(CMAKE_C_FLAGS_RELEASE "/D _CRT_SECURE_NO_WARNINGS /EHsc")
  set(CMAKE_C_FLAGS_DEBUG "/D _CRT_SECURE_NO_WARNINGS /EHsc /ZI /Od")
endif()

file(GLOB SOEM_SOURCES include/soem/soem/*.c)
file(GLOB OSAL_SOURCES include_${OS}/soem/osal/*.c)
file(GLOB OSHW_SOURCES include_${OS}/soem/oshw/*.c)

if(WIN32)
  set(SOEM_SOURCES ${SOEM_SOURCES})
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "rt-kernel")
  file(GLOB OSHW_ARCHSOURCES include_${OS}/soem/oshw/${ARCH}/*.c)
endif()

add_library(soem ${SOEM_SOURCES} ${OSAL_SOURCES} ${OSHW_SOURCES} ${OSHW_ARCHSOURCES})
if(WIN32)
  target_link_libraries(soem wpcap.lib Packet.lib Ws2_32.lib Winmm.lib ${HDF5_LIBRARIES})
elseif(UNIX)
  #target_link_libraries(soem pthread rt soem)
endif()

ament_package()















