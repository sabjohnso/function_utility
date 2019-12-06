//
// ... Standard header files
//
#include <utility>

//
// ... Function Utility header files
//
#include <function_utility/composite.hpp>
#include <function_utility/function_utility.hpp>

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
    FUNCTION_UTILITY_STATIC_TEST(
      [](const auto& x ){ return values( apply( sqr, x ), apply( twc, x )); }(
	values( 3 )) == values( 9, 6 ));
    FUNCTION_UTILITY_STATIC_TEST( fanout( sqr, twc )( 3 ) == values( 9, 6 ))

    FUNCTION_UTILITY_STATIC_TEST(
      compose( add, pcompose( identity, identity ))( 3, 4 ) == 7 );

    FUNCTION_UTILITY_STATIC_TEST(
      compose( add, first( sqr ), rest( twc ))( 3, 4 ) == 17 );

    

      				  
  }
  operator int() const { return accum; }

private:
  int accum;
}; // end of struct Composition_test


/** Test argument selection */
struct Selection_test
{
  Selection_test() : accum( 0 ) {
    using namespace FunctionUtility::Core;
    using std::index_sequence;
    FUNCTION_UTILITY_STATIC_TEST(
      selection( add, index_sequence<1,2>())(1, 2, 3, 4, 5 ) == 5 );

    FUNCTION_UTILITY_STATIC_TEST(
      selection( multiply, index_sequence<1,2>(), 1, 2, 3, 4, 5 ) == 6 );
    
    FUNCTION_UTILITY_TEST(
      accum, selection( add, index_sequence<1,2>())( 1, 2, 3, 4, 5 ) == 5 );

    FUNCTION_UTILITY_TEST(
      accum,
      selection( multiply, index_sequence<1,2>(), 1, 2, 3, 4, 5 ) == 6 );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Selection_test

namespace FunctionUtility
{
  namespace Testing
  {
    TEST(Composite, Legacy)
    {
      Composition_test{};
      Selection_test{};
    }
  } // end of namespace Testing
} // end of namespace FunctionUtility
