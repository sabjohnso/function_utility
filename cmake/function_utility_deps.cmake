find_package( Git REQUIRED )

execute_process(
  COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
  WORKING_DIRECTORY ${TYPE_UTILITY_SOURCE_DIR})

list( INSERT CMAKE_MODULE_PATH 0 ${TYPE_UTILITY_SOURCE_DIR}/cmake_modules )

