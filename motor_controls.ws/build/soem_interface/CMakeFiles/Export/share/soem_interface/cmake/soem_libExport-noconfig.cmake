#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "soem_interface::soem_lib" for configuration ""
set_property(TARGET soem_interface::soem_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(soem_interface::soem_lib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libsoem_lib.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS soem_interface::soem_lib )
list(APPEND _IMPORT_CHECK_FILES_FOR_soem_interface::soem_lib "${_IMPORT_PREFIX}/lib/libsoem_lib.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
