# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_soem_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED soem_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(soem_FOUND FALSE)
  elseif(NOT soem_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(soem_FOUND FALSE)
  endif()
  return()
endif()
set(_soem_CONFIG_INCLUDED TRUE)

# output package information
if(NOT soem_FIND_QUIETLY)
  message(STATUS "Found soem: 0.0.0 (${soem_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'soem' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${soem_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(soem_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_targets-extras.cmake;ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_libraries-extras.cmake")
foreach(_extra ${_extras})
  include("${soem_DIR}/${_extra}")
endforeach()
