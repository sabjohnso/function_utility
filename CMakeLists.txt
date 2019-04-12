#O
# ... Build script for function_utility
#

cmake_minimum_required( VERSION 3.7 )

project( FUNCTION_UTILITY )

#
# ... Version information
#
set( FUNCTION_UTILITY_MAJOR 0)
set( FUNCTION_UTILITY_MINOR 1)
set( FUNCTION_UTILITY_UPDATE 0)

set( FUNCTION_UTILITY_SUFFIX -${FUNCTION_UTILITY_MAJOR}.${FUNCTION_UTILITY_MINOR} )

set( FUNCTION_UTILITY_VERSION function_utility-${FUNCTION_UTILITY_SUFFIX} )
set( FUNCTION_UTILITY_VERSION_UPDATE ${FUNCTION_UTILITY_VERSION}.${FUNCTION_UTILITY_UPDATE} )

#
# ... Build options
#
option( BUILD_FUNCTION_UTILITY_TESTING  "Build the function_utility  tests" ON )
option( BUILD_FUNCTION_UTILITY_DOCUMENTATION "Build the function_utility documentation" ON )
option( FUNCTION_UTILITY_INSTALL_VERSIONED "Make a version specific installation" ON )


#
# ... Dependencies
#
find_package( type_utility REQUIRED )


#
# ... Installation path info
#
set( FUNCTION_UTILITY_INSTALL_INCLUDE_DIR include
  CACHE PATH "Path for installation of header files" )

set( FUNCTION_UTILITY_INSTALL_LIBRARY_DIR lib/function_utility
  CACHE PATH "Path for installation of library files" )

set( FUNCTION_UTILITY_INSTALL_EXEC_DIR bin
  CACHE PATH "Path for installation of executable files" )

if( FUNCTION_UTILITY_INSTALL_VERSIONED )
  string( APPEND FUNCTION_UTILITY_INSTALL_INCLUDE_DIR /function_utility${FUNCTION_UTILITY_SUFFIX})
  string( APPEND FUNCTION_UTILITY_INSTALL_LIBRARY_DIR ${FUNCTION_UTILITY_SUFFIX})
endif()


#
# ... Header library target
#
add_library( function_utility INTERFACE )
target_link_libraries( function_utility INTERFACE type_utility::type_utility )


target_include_directories( function_utility
  INTERFACE $<INSTALL_INTERFACE:${FUNCTION_UTILITY_INSTALL_INCLUDE_DIR}> )

target_include_directories( function_utility
  INTERFACE $<BUILD_INTERFACE:${FUNCTION_UTILITY_SOURCE_DIR}>)

target_include_directories( function_utility
  INTERFACE $<BUILD_INTERFACE:${FUNCTION_UTILITY_BINARY_DIR}> )


install( TARGETS function_utility EXPORT function_utility
  DESTINATION ${FUNCTION_UTILITY_INSTALL_LIBRARY_DIR})

install( EXPORT function_utility
  NAMESPACE function_utility::
  DESTINATION ${FUNCTION_UTILITY_INSTALL_LIBRARY_DIR}
  FILE function_utility.cmake )


#
# ... Walk the source tree
#
add_subdirectory( function_utility )



#
# ... Testing
#
if( BUILD_FUNCTION_UTILITY_TESTING )
  enable_testing()
  add_subdirectory( function_utility_testing )
endif( BUILD_FUNCTION_UTILITY_TESTING )



#
# ... Documentation
#
if( BUILD_FUNCTION_UTILITY_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )


  set( FUNCTION_UTILITY_INSTALL_DOC_DIR share/doc/${FUNCTION_UTILITY_VERSION}
    CACHE PATH "Path for installation of documentation files" )


  set( FUNCTION_UTILITY_INTALL_MAN_DIR include/function_utility
    CACHE PATH "Path for installation of man files" )


  find_package( Doxygen REQUIRED )

  add_custom_command(
    OUTPUT ${FUNCTION_UTILITY_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${FUNCTION_UTILITY_SOURCE_DIR}/function_utility
    WORKING_DIRECTORY ${${FUNCTION_UTILITY_BINARY_DIR}} )

  add_custom_target(
    function_utility_documentation ALL
    DEPENDS ${FUNCTION_UTILITY_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${FUNCTION_UTILITY_BINARY_DIR}/doc/html DESTINATION ${FUNCTION_UTILITY_INSTALL_DOC_DIR} )
  install( DIRECTORY ${FUNCTION_UTILITY_BINARY_DIR}/doc/man DESTINATION ${FUNCTION_UTILITY_INTALL_MAN_DIR} )
endif( BUILD_FUNCTION_UTILITY_DOCUMENTATION )

# end of build definition for function_utility
