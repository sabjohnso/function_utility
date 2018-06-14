macro( function_utility_add_simple_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  add_test( ${name} ${name}_test ) 
endmacro( function_utility_add_simple_test  name )


function_utility_add_simple_test( values )
function_utility_add_simple_test( composite )
function_utility_add_simple_test( curry )
function_utility_add_simple_test( static_callable )
