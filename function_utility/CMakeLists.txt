configure_file( config.hpp.in config.hpp )
  

set( FUNCTION_UTILITY_HEADER_FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  composite.hpp
  constant.hpp
  curry.hpp
  function_utility.hpp
  identity.hpp
  import.hpp
  nsplit.hpp
  power.hpp
  select.hpp
  static_application.hpp
  static_curried.hpp
  trampoline.hpp
  values.hpp)
  
install( FILES
  ${FUNCTION_UTILITY_HEADER_FILES}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/function_utility )


