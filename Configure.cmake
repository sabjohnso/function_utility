cmake_minimum_required(VERSION 3.12)

if(USE_CLANG)
  find_program(CXX clang++)
  set(CXX_FLAGS "-Wall -Wextra -Wshadow -pedantic -Werror")
else()
  find_program(CXX g++)
  set(CXX_FLAGS "-Wall -Wextra -Wshadow -pedantic -Werror")
endif()

if(TYPE STREQUAL "Debug")

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/build_debug
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

  execute_process(
    COMMAND ${CMAKE_COMMAND}
    -DCMAKE_BUILD_TYPE=Debug
    -DCMAKE_CXX_FLAGS=${CXX_FLAGS}
    -DCMAKE_CXX_COMPILER=${CXX}
    ${CMAKE_CURRENT_LIST_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build_debug )

else()

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/build
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

  execute_process(
    COMMAND ${CMAKE_COMMAND}
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_CXX_FLAGS=${CXX_FLAGS}
    -DCMAKE_CXX_COMPILER=${CXX}
    ${CMAKE_CURRENT_LIST_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build )

endif()
