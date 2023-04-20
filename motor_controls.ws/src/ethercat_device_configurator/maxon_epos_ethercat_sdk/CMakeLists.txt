cmake_minimum_required(VERSION 3.8)
project(maxon_epos_ethercat_sdk)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#=========================================================================
#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



## Set the C++ standard.
set(CMAKE_CXX_STANDARD 14)

## Enable all compiler warnings and treat them as errors.
add_compile_options(-Wall -Wextra -Wpedantic)

## Export compile commands for clang.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CATKIN_PACKAGE_DEPENDENCIES
  message_logger
  ethercat_sdk_master
)

find_package(ament_cmake REQUIRED
  COMPONENTS
    ${CATKIN_PACKAGE_DEPENDENCIES}
)

find_package(yaml-cpp REQUIRED)


###########
## Build ##
###########

include_directories(
  include
  ../message_logger/include
  ../ethercat_sdk_master/include
  ../soem_interface/soem_interface/include
  ../soem_interface/soem/include
  SYSTEM
    ${catkin_INCLUDE_DIRS}
)
FILE(GLOB CPPSources src/${PROJECT_NAME}/*.cpp)
add_library(${PROJECT_NAME}
  ${CPPSources}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${YAML_CPP_LIBRARIES}
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
  RUNTIME DESTINATION lib/${PROJECT_NAME}
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
