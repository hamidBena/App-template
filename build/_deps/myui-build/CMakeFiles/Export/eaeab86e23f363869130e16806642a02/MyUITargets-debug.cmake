#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyUI::MyUI" for configuration "Debug"
set_property(TARGET MyUI::MyUI APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MyUI::MyUI PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/MyUI.lib"
  )

list(APPEND _cmake_import_check_targets MyUI::MyUI )
list(APPEND _cmake_import_check_files_for_MyUI::MyUI "${_IMPORT_PREFIX}/lib/MyUI.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
