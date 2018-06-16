//
// ... Function Utility header files
//
#include <function_utility/function_utility.hpp>


//
// ... External header files header files
//
#include <type_utility/type_utility.hpp>


//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>

constexpr 
struct Sqr
{
  template< typename T >
  constexpr auto
  operator()( T&& x ){ return x*x; }

  template< typename Stream >
  friend Stream&
  operator <<( Stream& os, Sqr ){
    os << "sqr";
    return os;
  }
} sqr{};

/** Test the power func composite */
struct Powerfunc_test
{
  Powerfunc_test() : accum( 0 ) {
    using namespace FunctionUtility;
    using namespace TypeUtility;


    FUNCTION_UTILITY_STATIC_TEST( powerfunc( sqr, nat<2> )( 3 ) == 81 );
    FUNCTION_UTILITY_TEST( accum, powerfunc( sqr, nat<2> )( 3 ) == 81 );

    std::cout << std::endl << powerfunc( sqr, nat<2>, 3 ) << std::endl;
    FUNCTION_UTILITY_TEST( accum, powerfunc( sqr, nat<2>, 3 ) == 81 );
      
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Powerfunc_test

int
main( int, char** )
{
  int accum = 0;
  accum += Powerfunc_test();
  return accum;
}
