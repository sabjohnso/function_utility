//
// ... Standard header files
//
#include <cstdint>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>

//
// ... FunctionUtility header files
//
#include <function_utility/function_utility.hpp>

using integer = std::ptrdiff_t;
using TypeUtility::Nat;

namespace FunctionUtility::Testing
{

  TEST(Trampoline, Addition){
    struct Add : Static_curried<Add, Nat<2>> {
      static integer
      call(integer m, integer n){
        return m >= 0
          ? aux_pos(m, n)
          : aux_neg(m, n);
      }
    private:
      static Trampoline<integer>
      aux_pos(integer m, integer n){
        return m == 0
          ? Trampoline<integer>(n)
          : Trampoline<integer>(
            [=]{ return aux_pos(m-1, n+1); });
      }

      static Trampoline<integer>
      aux_neg(integer m, integer n){
        return m == 0
          ? Trampoline<integer>(n)
          : Trampoline<integer>(
            [=]{ return aux_neg(m + 1, n-1); });
      }
    } constexpr add{};

    EXPECT_EQ(add(3, 4), 7);
    EXPECT_EQ(add(10000000, 4), 10000004);
  }

  TEST(Trampoline, Factorial){
    struct Fact : Static_callable<Fact> {
      static integer
      call(integer n){
        return aux(n, 1, 1);
      }
    private:
      static Trampoline<integer>
      aux(integer n, integer m, integer accum){
        return m >= n
          ? Trampoline<integer>(m * accum)
          : Trampoline<integer>(
            [=]() -> Trampoline<integer> {
              return aux(n, m+1, m*accum);
            });
      }
    } fact{};

    EXPECT_EQ(fact(3), 6);
    EXPECT_EQ(fact(10), 3628800);
  }

  TEST(Trampoline, EvenOrOdd){
    struct Even_tag{};
    struct Odd_tag{};
    struct Even_or_odd : Static_curried<Even_or_odd, Nat<2>>{
      static bool
      call(Even_tag, integer n){ return even(n >= 0 ? n : -n); }

      static bool
      call(Odd_tag, integer n){ return odd(n >= 0 ? n : -n); }

    private:

      static Trampoline<bool>
      even(integer n){
        return n == 0
          ? Trampoline<bool>(true)
          : Trampoline<bool>([=]{ return odd(n-1); });
      }

      static Trampoline<bool>
      odd(integer n){
        return n == 0
          ? Trampoline<bool>(false)
          : Trampoline<bool>([=]{ return even(n-1); });
      }
    } constexpr even_or_odd{};

    constexpr auto even = even_or_odd(Even_tag{});
    constexpr auto odd = even_or_odd(Odd_tag{});

    EXPECT_TRUE(even(0));
    EXPECT_FALSE(odd(0));
    EXPECT_FALSE(even(1));
    EXPECT_TRUE(odd(1));
    EXPECT_TRUE(even(10000));
    EXPECT_FALSE(odd(10000));
    EXPECT_FALSE(even(10001));
    EXPECT_TRUE(odd(10001));
  }

} // end of namespace FunctionUtility::Testing
