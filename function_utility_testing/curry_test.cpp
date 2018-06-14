//
// ... Function Utility header files
//
#include <function_utility/function_utility.hpp>


//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>


/** Test function currying */
struct Test_curry
{
  Test_curry() : accum( 0 ) {
    using namespace FunctionUtility;
    constexpr auto add = curry<2>( []( auto x, auto y ){ return x+y; });
    FUNCTION_UTILITY_STATIC_TEST( add( 3, 4 ) == 7 );
    FUNCTION_UTILITY_STATIC_TEST( add( 3 )( 4 ) == 7 );

    
    FUNCTION_UTILITY_TEST( accum, add( 3, 4 ) == 7 );
    FUNCTION_UTILITY_TEST( accum, add( 3 )( 4 ) == 7 );
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Test_curry


int
main( int, char** )
{
  int accum = 0;
  accum += Test_curry();
  return accum;
}
