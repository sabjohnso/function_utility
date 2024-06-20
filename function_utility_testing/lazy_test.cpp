//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... Function Utility header files
//
#include <function_utility/function_utility.hpp>

namespace FunctionUtility::testing{
  TEST(Lazy, Construction){
    const auto x = lazy([]{ return 3+4; });
    ASSERT_EQ(x.value(), 7);
  }

} // end of namespace function_utility::testing
