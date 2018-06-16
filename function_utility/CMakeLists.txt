configure_file( config.hpp.in config.hpp )


install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  composite.hpp
  curry.hpp
  function_utility.hpp
  identity.hpp
  import.hpp
  power.hpp
  static_application.hpp
  values.hpp
  DESTINATION ${FUNCTION_UTILITY_INSTALL_INCLUDE_DIR})
