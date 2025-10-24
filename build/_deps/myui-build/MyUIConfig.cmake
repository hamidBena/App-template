
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was MyUIConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# MyUI CMake configuration file

set(MYUI_VERSION "1.0.0")

# Set up import targets
include("${CMAKE_CURRENT_LIST_DIR}/MyUITargets.cmake")

# Provide legacy variables for compatibility
set(MyUI_FOUND TRUE)
set(MYUI_VERSION_STRING "1.0.0")
set(MYUI_LIBRARIES MyUI)
set(MYUI_INCLUDE_DIRS "C:/Program Files (x86)/AppProject/include")

# Check required components
check_required_components(MyUI)

# Display found message for user feedback
if(NOT MyUI_FIND_QUIETLY)
    message(STATUS "Found MyUI: ${MYUI_VERSION} (${CMAKE_CURRENT_LIST_DIR})")
endif()
