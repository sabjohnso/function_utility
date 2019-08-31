include( FetchGTest )

macro( function_utility_add_test name exe_name)
  add_executable( ${exe_name} ${ARGN} )
  set_target_properties( ${exe_name} PROPERTIES CXX_STANDARD 17 )
  target_link_libraries( ${exe_name} PRIVATE
    function_utility::function_utility
    GTest::gtest_main )
  add_test(${name} ${exe_name})
endmacro()

macro( function_utility_add_simple_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  set_target_properties( ${name}_test PROPERTIES CXX_STANDARD 17 )
  target_link_libraries( ${name}_test PRIVATE function_utility )  
  add_test( ${name} ${name}_test )
endmacro()

function_utility_add_simple_test( values )
function_utility_add_simple_test( composite )
function_utility_add_simple_test( curry )
function_utility_add_simple_test( static_callable )
function_utility_add_simple_test( static_curried )
function_utility_add_simple_test( powerfunc )
function_utility_add_simple_test( partition )
