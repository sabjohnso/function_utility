//
// ... Standard header files
//
#include <type_traits>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... FunctionUtility header files
//
#include <function_utility/constant.hpp>

namespace // anonymous
{
  using FunctionUtility::Core::Constant;
  using std::is_same;

} // end of anonymous namespace

namespace FunctionUtility {
  namespace Testing {
    TEST(Constant, Construction)
    {
      auto f = Constant(3);
      static_assert(std::is_same_v<decltype(f), Constant<int>>);
    }

    TEST(Constant, Construction2)
    {
      constexpr auto f = Constant(3);
      static_assert(std::is_same_v<decltype(f), const Constant<int>>);
    }

    TEST(Constant, Application)
    {
      auto f = Constant(3);
      static_assert(std::is_same_v<decltype(f), Constant<int>>);
      EXPECT_EQ(f('z'), 3);
    }

    TEST(Constant, CurriedApplication)
    {
      EXPECT_EQ(Constant([](auto x) { return x * x; })(3, 4), 16);
    }

  } // end of namespace Testing
} // end of namespace FunctionUtility
