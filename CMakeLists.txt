#O
# ... Build script for function_utility
#

cmake_minimum_required( VERSION 3.7 )

project( FUNCTION_UTILITY VERSION 0.2.0 LANGUAGES CXX )

#
# ... Build options
#
option( BUILD_FUNCTION_UTILITY_TESTING  "Build the function_utility  tests" ON )
option( BUILD_FUNCTION_UTILITY_DOCUMENTATION "Build the function_utility documentation" OFF )

list( INSERT CMAKE_MODULE_PATH 0 ${FUNCTION_UTILITY_SOURCE_DIR}/cmake )
include(GNUInstallDirs)

#
# ... Dependencies
#
include(function_utility_deps)


#
# ... Header library target
#
add_library( function_utility INTERFACE )
target_link_libraries( function_utility INTERFACE type_utility::type_utility )

target_include_directories( function_utility  
  INTERFACE
  $<BUILD_INTERFACE:${FUNCTION_UTILITY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${FUNCTION_UTILITY_BINARY_DIR}>
  $<INSTALL_INTERFACE:${FUNCTION_UTILITY_INSTALL_INCLUDE_DIR}> )

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


  set( FUNCTION_UTILITY_INSTALL_DOCDIR share/doc/function_utility
    CACHE PATH "Path for installation of documentation files" )


  set( FUNCTION_UTILITY_INTALL_MANDIR share/man
    CACHE PATH "Path for installation of man files" )


  find_package( Doxygen REQUIRED )

  add_custom_command(
    OUTPUT ${FUNCTION_UTILITY_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${FUNCTION_UTILITY_SOURCE_DIR}/function_utility
    WORKING_DIRECTORY ${FUNCTION_UTILITY_BINARY_DIR} )

  add_custom_target(
    function_utility_documentation ALL
    DEPENDS ${FUNCTION_UTILITY_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${FUNCTION_UTILITY_BINARY_DIR}/doc/html DESTINATION ${FUNCTION_UTILITY_INSTALL_DOCDIR} )
  install( DIRECTORY ${FUNCTION_UTILITY_BINARY_DIR}/doc/man DESTINATION ${FUNCTION_UTILITY_INTALL_MANDIR} )
endif( BUILD_FUNCTION_UTILITY_DOCUMENTATION )


#
# ... Installation
#
set(FUNCTION_UTILITY_CONFDIR ${CMAKE_INSTALL_LIBDIR}/cmake/function_utility)
install( TARGETS function_utility EXPORT function_utility
  DESTINATION ${FUNCTION_UTILITY_CONFDIR} )

install( EXPORT function_utility
  NAMESPACE function_utility::
  DESTINATION ${FUNCTION_UTILITY_CONFDIR}
  FILE function_utility_exports.cmake )

configure_file( function_utility-config.cmake.in function_utility-config.cmake)
install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/function_utility-config.cmake
  DESTINATION ${FUNCTION_UTILITY_CONFDIR})

# end of build definition for function_utility
