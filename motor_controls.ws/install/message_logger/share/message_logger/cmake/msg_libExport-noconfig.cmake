#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "message_logger::msg_lib" for configuration ""
set_property(TARGET message_logger::msg_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(message_logger::msg_lib PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmsg_lib.so"
  IMPORTED_SONAME_NOCONFIG "libmsg_lib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS message_logger::msg_lib )
list(APPEND _IMPORT_CHECK_FILES_FOR_message_logger::msg_lib "${_IMPORT_PREFIX}/lib/libmsg_lib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
