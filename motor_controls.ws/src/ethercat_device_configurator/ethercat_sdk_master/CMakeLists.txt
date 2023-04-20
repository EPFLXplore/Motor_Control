cmake_minimum_required(VERSION 3.8)
project(ethercat_sdk_master)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)



#=========================================================================
#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  set(CMAKE_C_COMPILER_LAUNCHER   ${CCACHE_PROGRAM})
endif()

set(CMAKE_CXX_STANDARD 14)

## Enable all compiler warnings and treat them as errors.
add_compile_options(-Wall -Wextra -Wpedantic)

set(CATKIN_PACKAGE_DEPENDENCIES
  soem_interface
)

find_package(Threads)


###########
## Build ##
###########
include_directories(
  ../soem_interface/soem_interface/include
  ../soem_interface/soem/include
  ../message_logger/include
  include
  SYSTEM
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/EthercatMaster.cpp
  src/${PROJECT_NAME}/EthercatDevice.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  ${YAML_CPP_LIBRARIES}
  Threads::Threads

)


ament_target_dependencies(${PROJECT_NAME}
  "rclcpp"
)

#############
## Install ##
#############
install(
  TARGETS
    ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(
  DIRECTORY
    include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#=========================================================================


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
