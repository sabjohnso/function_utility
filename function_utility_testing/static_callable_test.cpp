//
// ... Standard header files
//
#include <utility>


//
// ... Function Utility header files
//
#include <function_utility/function_utility.hpp>


//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>

using std::forward;
using namespace FunctionUtility;

/** Test the static callable base class */
struct Static_callable_test
{
  struct Add : public Static_callable<Add>{
    template< typename T, typename U >    
    static constexpr auto
    call( T&& x, U&& y ){ return forward<T>( x ) + forward<U>( y ); }
  };

  static constexpr auto add = Add{};
  
  Static_callable_test() : accum( 0 ) {
    FUNCTION_UTILITY_STATIC_TEST( add( 3, 4 ) == 7 );
    FUNCTION_UTILITY_TEST( accum, add( 3, 4 ) == 7 );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Static_callable_test


int
main( int, char** )
{
  int accum = 0;
  accum += Static_callable_test();
  return accum;
}
