#ifndef FUNCTION_UTILITY_HPP_INCLUDED_744288557843392172
#define FUNCTION_UTILITY_HPP_INCLUDED_744288557843392172 1

//
// ... Function Utility header files
//
#include <function_utility/values.hpp>
#include <function_utility/identity.hpp>
#include <function_utility/composite.hpp>


namespace FunctionUtility
{

  /** Multiple values */
  using Core::values;


  /** Identity function */
  using Core::identity;
  
  /** Duplicate the first argument */
  using Core::dup;
  

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
  using Core::second;

  /** Partial application */
  using Core::part;

  /** Rright partial application */
  using Core::rpart;

  
  
} // end of namespace FunctionUtility

#endif // !defined FUNCTION_UTILITY_HPP_INCLUDED_744288557843392172
