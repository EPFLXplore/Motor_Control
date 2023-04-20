# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_soem_rsl_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED soem_rsl_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(soem_rsl_FOUND FALSE)
  elseif(NOT soem_rsl_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(soem_rsl_FOUND FALSE)
  endif()
  return()
endif()
set(_soem_rsl_CONFIG_INCLUDED TRUE)

# output package information
if(NOT soem_rsl_FIND_QUIETLY)
  message(STATUS "Found soem_rsl: 0.0.0 (${soem_rsl_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'soem_rsl' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${soem_rsl_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(soem_rsl_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${soem_rsl_DIR}/${_extra}")
endforeach()
