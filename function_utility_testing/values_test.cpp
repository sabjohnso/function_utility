//
// ... Function Utility header files
//
#include <function_utility/values.hpp>


//
// ... Type Utility header files
//
#include <type_utility/type_utility.hpp>



//
// ... Testing header files
//
#include <function_utility_testing/test_macros.hpp>


/** Test the values type */
struct Values_test
{
  Values_test() : accum( 0 ) {
    using TypeUtility::type;
    using namespace FunctionUtility::Core;
    
    FUNCTION_UTILITY_STATIC_TEST( type<decltype(values())> == type<Values<>> );
    FUNCTION_UTILITY_STATIC_TEST( type<decltype(values(1))> == type<Values<int>> );
    FUNCTION_UTILITY_STATIC_TEST( type<decltype(values(1,2))> == type<Values<int,int>> );

    FUNCTION_UTILITY_STATIC_TEST( 
      type<decltype(values('x',1,2.0))> ==
      type<Values<char,int,double>> );

    FUNCTION_UTILITY_STATIC_TEST(
      get<0>( values( 'x', 1, 2.0 )) == 'x' );

    FUNCTION_UTILITY_STATIC_TEST(
      get<1>( values( 'x', 1, 2.0 )) == 1 );

    FUNCTION_UTILITY_STATIC_TEST(
      get<2>( values( 'x', 1, 2.0 )) == 2 );


    FUNCTION_UTILITY_STATIC_TEST(
      type<decltype(values( values( 'x', 1 ), values( 'y', 2 )))> ==
      type<Values<char,int,char,int>> );

    FUNCTION_UTILITY_STATIC_TEST( get<0>( values( values( 'x', 1 ), values( 'y', 2 ))) == 'x' );
    FUNCTION_UTILITY_STATIC_TEST( get<1>( values( values( 'x', 1 ), values( 'y', 2 ))) == 1 );
    FUNCTION_UTILITY_STATIC_TEST( get<2>( values( values( 'x', 1 ), values( 'y', 2 ))) == 'y' );
    FUNCTION_UTILITY_STATIC_TEST( get<3>( values( values( 'x', 1 ), values( 'y', 2 ))) == 2 );

    FUNCTION_UTILITY_STATIC_TEST( get<0>( head( values( 1, 2, 3, 4 ))) == 1 );
    FUNCTION_UTILITY_STATIC_TEST( get<0>( tail( values( 1, 2, 3, 4 ))) == 2 );
    FUNCTION_UTILITY_STATIC_TEST( get<0>( tail( tail( values( 1, 2, 3, 4 )))) == 3 );
    


    
    FUNCTION_UTILITY_TEST( accum, type<decltype(values())> == type<Values<>> );
    FUNCTION_UTILITY_TEST( accum, type<decltype(values(1))> == type<Values<int>> );
    FUNCTION_UTILITY_TEST( accum, type<decltype(values(1,2))> == type<Values<int,int>> );

    FUNCTION_UTILITY_TEST( accum, 
      type<decltype(values('x',1,2.0))> ==
      type<Values<char,int,double>> );

    FUNCTION_UTILITY_TEST( accum,
      get<0>( values( 'x', 1, 2.0 )) == 'x' );

    FUNCTION_UTILITY_TEST( accum,
      get<1>( values( 'x', 1, 2.0 )) == 1 );

    FUNCTION_UTILITY_TEST( accum,
      get<2>( values( 'x', 1, 2.0 )) == 2 );

    
    FUNCTION_UTILITY_TEST( accum,
      type<decltype(values( values( 'x', 1 ), values( 'y', 2 )))> ==
      type<Values<char,int,char,int>> );

    FUNCTION_UTILITY_TEST( accum, get<0>( values( values( 'x', 1 ), values( 'y', 2 ))) == 'x' );
    FUNCTION_UTILITY_TEST( accum, get<1>( values( values( 'x', 1 ), values( 'y', 2 ))) == 1 );
    FUNCTION_UTILITY_TEST( accum, get<2>( values( values( 'x', 1 ), values( 'y', 2 ))) == 'y' );
    FUNCTION_UTILITY_TEST( accum, get<3>( values( values( 'x', 1 ), values( 'y', 2 ))) == 2 );

    FUNCTION_UTILITY_TEST( accum, get<0>( head( values( 1, 2, 3, 4 ))) == 1 );
    FUNCTION_UTILITY_TEST( accum, get<0>( tail( values( 1, 2, 3, 4 ))) == 2 );
    FUNCTION_UTILITY_TEST( accum, get<0>( tail( tail( values( 1, 2, 3, 4 )))) == 3 );




    std::cout << values( 1, 2, 3 ) << std::endl;
    std::cout << drop( values(1, 2, 3 ), nat<1> ) << std::endl; 
    
  }
  
  operator int() const { return accum; }
  
private:

  
  int accum;
}; // end of struct Values_test



int
main( int, char** )
{
  int accum = 0;
  accum += Values_test();
  return accum;
}
