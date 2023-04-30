#pragma once

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>

// TODO: Rename this file to reflect the name of the class it contains

namespace FunctionUtility::Core {

  /**
   * @brief A CRTP base class providing the function
   * call operator to subtypes that provide a static
   * member function named call
   */
  template<typename F>
  class Static_callable : public CRTP<Static_callable, F>
  {
  public:
    /**
     * @brief Apply the subtype's `call` function to
     * the input arguments.
     */
    template<typename... Ts>
    constexpr auto
    operator()(Ts&&... xs) const&
    {
      return F::call(std::forward<Ts>(xs)...);
    }
  }; // end of class Static_callable

  /**
   * @brief A struct providing a type predicate for types that
   * inherit from Static_callable.
   */
  template<typename T>
  struct is_static_callable
    : is_base_of<Static_callable<decay_t<T>>, decay_t<T>>
  {};

  /**
   * @brief A value template representing the result of the is_static_callable
   * predicate.
   */
  template<typename T>
  constexpr bool is_static_callable_v = is_static_callable<T>::value;

} // end of namespace FunctionUtility::Core
