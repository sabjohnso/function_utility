configure_file( config.hpp.in config.hpp )
  

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  composite.hpp
  curry.hpp
  function_utility.hpp
  identity.hpp
  import.hpp
  nsplit.hpp
  power.hpp
  select.hpp
  static_application.hpp
  static_curried.hpp
  values.hpp
  DESTINATION ${FUNCTION_UTILITY_INSTALL_INCLUDE_DIR}/function_utility)

configure_file( function_utility-config.cmake.in function_utility-config.cmake)
install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/function_utility-config.cmake
  DESTINATION ${FUNCTION_UTILITY_INSTALL_LIBRARY_DIR} )



