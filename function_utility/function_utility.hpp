#ifndef FUNCTION_UTILITY_HPP_INCLUDED_744288557843392172
#define FUNCTION_UTILITY_HPP_INCLUDED_744288557843392172 1

//
// ... Function Utility header files
//
#include <function_utility/composite.hpp>
#include <function_utility/constant.hpp>
#include <function_utility/curry.hpp>
#include <function_utility/identity.hpp>
#include <function_utility/import.hpp>
#include <function_utility/nsplit.hpp>
#include <function_utility/power.hpp>
#include <function_utility/select.hpp>
#include <function_utility/static_application.hpp>
#include <function_utility/static_curried.hpp>
#include <function_utility/values.hpp>

namespace FunctionUtility {

  /** Multiple values */
  using Core::values;

  /** Identity function */
  using Core::identity;

  /** Constant function (K combinator)*/
  using Core::constant;

  /** Sequential composition of functions */
  using Core::compose;

  /** Parallel composition of functions */
  using Core::pcompose;

  /** Generalized composition */
  using Core::scompose;

  /** Fanout */
  using Core::fanout;

  /** Apply to first argument */
  using Core::first;

  /** Apply to second argument */
  using Core::rest;

  /** Partial application */
  using Core::part;

  /** Rright partial application */
  using Core::rpart;

  using Core::curry;
  using Core::partition;
  using Core::powerfunc;
  using Core::selection;

  /** CRTP base class for deriving the function call operator */
  using Core::is_static_callable;
  using Core::Static_callable;

  /** CRTP base class for curried static function call operator */
  using Core::Static_curried;

} // end of namespace FunctionUtility

#endif // !defined FUNCTION_UTILITY_HPP_INCLUDED_744288557843392172
