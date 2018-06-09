#
# ... Build script for function_utility
#

cmake_minimum_required( VERSION 3.7 )

project( FUNCTION_UTILITY )
set( FUNCTION_UTILITY_MAJOR 0)
set( FUNCTION_UTILITY_MINOR 1)
set( FUNCTION_UTILITY_UPDATE 0)
set( FUNCTION_UTILITY_VERSION function_utility-${FUNCTION_UTILITY_MAJOR}.${FUNCTION_UTILITY_MINOR} )
set( FUNCTION_UTILITY_VERSION_UPDATE ${FUNCTION_UTILITY_VERSION}.${FUNCTION_UTILITY_UPDATE} )

option( BUILD_FUNCTION_UTILITY_TESTING  "Build the function_utility  tests" ON )
option( BUILD_FUNCTION_UTILITY_DOCUMENTATION "Build the function_utility documentation" ON )

include_directories( 
  ${FUNCTION_UTILITY_SOURCE_DIR}
  ${FUNCTION_UTILITY_BINARY_DIR} )

if( NOT FUNCTION_UTILITY_INSTALL_INCLUDE_DIR)
  set( FUNCTION_UTILITY_INSTALL_INCLUDE_DIR include/function_utility
    CACHE PATH "Path for installation of header files" )
endif( NOT FUNCTION_UTILITY_INSTALL_INCLUDE_DIR)

add_subdirectory( function_utility )



#
# ... Testing #
if( BUILD_FUNCTION_UTILITY_TESTING )
  enable_testing()
  add_subdirectory( function_utility_testing )
endif( BUILD_FUNCTION_UTILITY_TESTING )



#
# ... Documentation
#
if( BUILD_FUNCTION_UTILITY_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )

  if( NOT FUNCTION_UTILITY_INSTALL_DOC_DIR)
    set( FUNCTION_UTILITY_INSTALL_DOC_DIR share/doc/${FUNCTION_UTILITY_VERSION}
      CACHE PATH "Path for installation of documentation files" )
  endif( NOT FUNCTION_UTILITY_INSTALL_DOC_DIR)

  if( NOT FUNCTION_UTILITY_INTALL_MAN_DIR)
    set( FUNCTION_UTILITY_INTALL_MAN_DIR include/function_utility
      CACHE PATH "Path for installation of man files" )
  endif( NOT FUNCTION_UTILITY_INTALL_MAN_DIR)

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
