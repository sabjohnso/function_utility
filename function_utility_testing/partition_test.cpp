//
// ... Function Utility header files
//
#include <function_utility/function_utility.hpp>

//
// ... External library header files
//
#include <type_utility/type_utility.hpp>


//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>



/** 
 * @brief Test partitioning the arguments over
 * functions
 */
struct Partition_test
{
  Partition_test() : accum( 0 ) {

    using namespace FunctionUtility;
    using TypeUtility::nat;
    
    constexpr auto id  = []( auto x ){ return x; };
    constexpr auto add = []( auto x, auto y ){ return x+y; };
    constexpr auto mul = []( auto x, auto y ){ return x*y; };

    constexpr auto axpy =
      compose( add, partition( mul, nat<2>, id, nat<1>));

    FUNCTION_UTILITY_STATIC_TEST(
      axpy( 2, 3, 4 ) == 10 );


    constexpr auto axpy_ =
      compose( add, partition( mul, nat<2>, id));
    
    FUNCTION_UTILITY_STATIC_TEST(
      axpy_( 2, 3, 4 ) == 10 );
    
  }
  operator int() const { return accum; }
private:
  
  int accum;
}; // end of struct Partition_test



int
main( int, char** )
{
  int accum = 0;
  accum += Partition_test();
  return accum;
}
