//
// ... Function Utility header files
//
#include <function_utility/static_curried.hpp>


//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>

using namespace FunctionUtility::Core;


/** UNDOCUMENTED TEST */
struct Static_curried_test
{
  static constexpr
  class Axpy : public Static_curried<Axpy,Nat<3>> {
  public:
    template< typename A, typename X, typename Y >
    static constexpr auto
    call( A&& a, X&& x, Y&& y ){
      return a*x+y;
    }
  } axpy{};  
  
  Static_curried_test() : accum( 0 ) {
    
    FUNCTION_UTILITY_STATIC_TEST( axpy( 2, 3, 4 ) == 10 );
    FUNCTION_UTILITY_STATIC_TEST( axpy( 2, 3 )( 4 ) == 10 );
    FUNCTION_UTILITY_STATIC_TEST( axpy( 2 )( 3, 4 ) == 10 );
    FUNCTION_UTILITY_STATIC_TEST( axpy( 2 )( 3 )( 4 ) == 10 );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Static_curried_test

int
main( int, char** )
{
  int accum = 0;
  accum += Static_curried_test();
  return accum;
}
