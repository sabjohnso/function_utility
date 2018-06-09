//
// ... Function Utility header files
//
#include <function_utility/composite.hpp>


//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>

constexpr auto twc = []( auto x ){ return x+x; };
constexpr auto sqr = []( auto x ){ return x*x; };


/** Test function composition */
struct Composition_test
{
  Composition_test() : accum( 0 ) {
    using namespace FunctionUtility::Core;
    FUNCTION_UTILITY_STATIC_TEST( compose( sqr, twc )( 3 ) == 36 );
    FUNCTION_UTILITY_STATIC_TEST( pcompose( sqr, twc )( 3, 4 ) == values( 9, 8 ));
    FUNCTION_UTILITY_STATIC_TEST( fanout( sqr, twc )( 3 ) == values( 9, 6 ));
    
				  
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Composition_test


int
main( int, char** )
{
  int accum = 0;
    
  return accum;
}
