#ifndef CONSTANT_HPP_INCLUDED_1910593651770922426
#define CONSTANT_HPP_INCLUDED_1910593651770922426 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>
#include <function_utility/static_curried.hpp>

namespace FunctionUtility {
  namespace Core {

    template<typename T>
    class Constant
    {
    public:
      using value_type = T;
      using const_reference = value_type const&;
      using rvalue_reference = value_type&&;

      constexpr Constant(const_reference input_value)
        : value(input_value)
      {}

      constexpr Constant(rvalue_reference input_value)
        : value(std::move(input_value))
      {}

      constexpr Constant(Constant const& input)
        : value(input.value)
      {}

      constexpr Constant(Constant&& input)
        : value(std::move(input.value))
      {}

      template<typename U>
      constexpr const_reference
      operator()(U&&) const&
      {
        return value;
      }

      template<typename U>
      constexpr rvalue_reference
      operator()(U&&) &&
      {
        return std::move(value);
      }

      template<typename U, typename V, typename... Ws>
      constexpr auto
      operator()(U&&, V&& y, Ws&&... zs) const&
      {
        return value(std::forward<V>(y), std::forward<Ws>(zs)...);
      }

      template<typename U, typename V, typename... Ws>
      constexpr auto
      operator()(U&&, V&& y, Ws&&... zs) &&
      {
        return std::move(value)(std::forward<V>(y), std::forward<Ws>(zs)...);
      }

    private:
      value_type value;
    }; // end of class constant

    template<typename T, typename dT = decay_t<T>>
    Constant(T&& x) -> Constant<dT>;

    constexpr struct Make_constant : Static_curried<Make_constant, Nat<1>>
    {
      template<typename T>
      static constexpr auto
      call(T&& x)
      {
        return Constant(std::forward<T>(x));
      }
    } constant{};

  } // end of namespace Core
} // end of namespace FunctionUtility

#endif // ! defined CONSTANT_HPP_INCLUDED_1910593651770922426
