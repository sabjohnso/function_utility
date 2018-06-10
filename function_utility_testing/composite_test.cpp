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
constexpr auto add = []( auto x, auto y ){ return x+y; };
constexpr auto multiply = []( auto x, auto y ){ return x*y; };


/** Test function composition */
struct Composition_test
{
  Composition_test() : accum( 0 ) {
    using namespace FunctionUtility::Core;
    FUNCTION_UTILITY_STATIC_TEST( compose( sqr, twc )( 3 ) == 36 );
    FUNCTION_UTILITY_STATIC_TEST( pcompose( sqr, twc )( 3, 4 ) == values( 9, 8 ));
    FUNCTION_UTILITY_STATIC_TEST( fanout( sqr, twc )( 3 ) == values( 9, 6 ));


    FUNCTION_UTILITY_STATIC_TEST(
      compose( add, pcompose( identity, identity ))( 3, 4 ) == 7 );

    FUNCTION_UTILITY_STATIC_TEST(
      compose( add, first( sqr ), second( twc ))( 3, 4 ) == 17 );


    FUNCTION_UTILITY_STATIC_TEST(
      compose( multiply, dup )( 3 ) == 9 );
      
    
				  
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Composition_test


int
main( int, char** )
{
  int accum = 0;
  accum += Composition_test();
  return accum;
}
