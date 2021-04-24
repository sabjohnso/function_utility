if(NOT EXISTS ${PROJECT_SOURCE_DIR}/cmake_utilities/FindCMakeUtilities.cmake)
  #
  # ... Git submodules
  #
  find_package(Git REQUIRED)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${FUNCTION_UTILITY_SOURCE_DIR})
endif()
list( INSERT CMAKE_MODULE_PATH 0 ${FUNCTION_UTILITY_SOURCE_DIR}/cmake_utilities )
find_package(CMakeUtilities REQUIRED)


#
# ... Installed dependencies
#
find_package( type_utility REQUIRED )
