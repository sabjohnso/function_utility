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

namespace {
  using TypeUtility::type;
  using namespace FunctionUtility::Core;
} // end of namespace

namespace FunctionUtility {
  namespace Testing {

    TEST(Values, EmptyConstruction)
    {
      FUNCTION_UTILITY_STATIC_TEST(
	type<decltype(values())> == type<Values<>>);
    }

    TEST(Values, OneValueConstruction)
    {
      FUNCTION_UTILITY_STATIC_TEST(
	type<decltype(values(1))> ==
	type<Values<int>>);
      EXPECT_EQ(get<0>(values(1)), 1);
    }

    TEST(Values, TwoValueConstruction)
    {
      FUNCTION_UTILITY_STATIC_TEST(
	type<decltype(values(1, 2))> == 
	type<Values<int, int>>);

      EXPECT_EQ(get<0>(values(1, 2)), 1);
      EXPECT_EQ(get<1>(values(1, 2)), 2);
    }
    
    TEST(Values, Inhomogeneous_construction)
    {
      FUNCTION_UTILITY_STATIC_TEST(
	type<decltype(values('x', 1, 2.0))> == 
	type<Values<char, int, double>>);
      FUNCTION_UTILITY_STATIC_TEST(get<0>(values('x', 1, 2.0)) == 'x');
      FUNCTION_UTILITY_STATIC_TEST(get<1>(values('x', 1, 2.0)) == 1);
      FUNCTION_UTILITY_STATIC_TEST(get<2>(values('x', 1, 2.0)) == 2);
    }
    
    TEST(Values, JoinConstruction)
    {
      FUNCTION_UTILITY_STATIC_TEST(
	type<decltype(values(values('x', 1), values('y', 2)))> ==
	type<Values<char, int, char, int>>);
      
      FUNCTION_UTILITY_STATIC_TEST(
	get<0>(values(values('x', 1), values('y', 2))) == 'x');
      FUNCTION_UTILITY_STATIC_TEST(
	get<1>(values(values('x', 1), values('y', 2))) == 1);
      FUNCTION_UTILITY_STATIC_TEST(
	get<2>(values(values('x', 1), values('y', 2))) == 'y');
      FUNCTION_UTILITY_STATIC_TEST(
	get<3>(values(values('x', 1), values('y', 2))) == 2);
    }
    
    TEST(Values, ListAccess)
    {
      FUNCTION_UTILITY_STATIC_TEST(get<0>(head(values(1, 2, 3, 4))) == 1);
      FUNCTION_UTILITY_STATIC_TEST(get<0>(tail(values(1, 2, 3, 4))) == 2);
      FUNCTION_UTILITY_STATIC_TEST(get<0>(tail(tail(values(1, 2, 3, 4)))) == 3);
    }
    
    TEST(Values, Selection){
      FUNCTION_UTILITY_STATIC_TEST(
	select(values(1, 2, 3, 4), index_sequence<0, 2>()) == values(1, 3));
      FUNCTION_UTILITY_STATIC_TEST(
	select(values(1, 2, 3, 4), index_sequence<1, 2>()) == values(2, 3));
      FUNCTION_UTILITY_STATIC_TEST(
	select(values(1, 2, 3, 4), index_sequence<>()) == values());
    }
    
    TEST(Values,Types)
    {
      EXPECT_TRUE(type<decltype(values())> == type<Values<>>);
      EXPECT_TRUE(type<decltype(values(1))> == type<Values<int>>);
      EXPECT_TRUE((type<decltype(values(1, 2))>) == (type<Values<int, int>>));
      EXPECT_TRUE((type<decltype(values('x', 1, 2.0))>) == (type<Values<char, int, double>>));
      
      EXPECT_EQ( get<0>(values('x', 1, 2.0)), 'x');
      EXPECT_EQ( get<1>(values('x', 1, 2.0)), 1);
      EXPECT_EQ( get<2>(values('x', 1, 2.0)), 2);
    }
    
    TEST(Values, Misc)
    {
      EXPECT_TRUE((type<decltype(values(values('x', 1), values('y', 2)))> == type<Values<char, int, char, int>>)); 
      EXPECT_EQ( get<0>(values(values('x', 1), values('y', 2))), 'x');
      EXPECT_EQ( get<1>(values(values('x', 1), values('y', 2))), 1);
      EXPECT_EQ( get<2>(values(values('x', 1), values('y', 2))), 'y');
      EXPECT_EQ( get<3>(values(values('x', 1), values('y', 2))), 2);
      EXPECT_EQ( get<0>(head(values(1, 2, 3, 4))), 1);
      EXPECT_EQ( get<0>(tail(values(1, 2, 3, 4))), 2);
      EXPECT_EQ( get<0>(tail(tail(values(1, 2, 3, 4)))),3);

    }
    
  } // end of namespace Testing
} // end of namespace FunctionUtility

