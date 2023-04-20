cmake_minimum_required(VERSION 3.5)
project(soem_interface)

add_definitions(-std=c++14 -Wall)
add_definitions(-DMELO_USE_COUT)

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
find_package(soem_rsl)
find_package(message_logger)

include_directories(
  ../soem/include
  ../../message_logger/include
  include
)


add_library(
  ${PROJECT_NAME}
  src/${PROJECT_NAME}/common/ThreadSleep.cpp
  src/${PROJECT_NAME}/common/Macros.cpp
  src/${PROJECT_NAME}/EthercatSlaveBase.cpp
  src/${PROJECT_NAME}/EthercatBusManagerBase.cpp
  src/${PROJECT_NAME}/EthercatBusBase.cpp
  ../../message_logger/src/time/Time.cpp
  ../../message_logger/src/time/TimeStd.cpp
  
)

install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include
)

ament_package()
