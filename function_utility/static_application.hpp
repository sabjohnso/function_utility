#ifndef STATIC_APPLICATION_HPP_INCLUDED_452842591972554914
#define STATIC_APPLICATION_HPP_INCLUDED_452842591972554914 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>
#include <function_utility/curry.hpp>
#include <function_utility/values.hpp>

#include <iostream>

namespace FunctionUtility
{
  namespace Core
  {

    /** 
     * @brief A CRTP base class providing the function
     * call operator to subtypes that provide a static
     * member function named call
     */
    template< typename F >
    class Static_callable : public CRTP<Static_callable,F>
    {
    public:
      
      /** 
       * @brief Apply the subtype's `call` function to
       * the input arguments.
       */
      template< typename ... Ts >
      constexpr auto
      operator ()( Ts&& ... xs ) const & {
	return F::call( forward<Ts>( xs ) ... );
      }
      
    }; // end of class Static_callable


    
    template< typename ... >
    class Static_curried;

    template< typename F, size_t N >
    class Static_curried<F,Nat<N>> : public CRTP<Static_curried,F>
    {
    public:
      using function_type = F;
      
      struct equal_tag{};
      struct less_tag{};
      struct more_tag{};
      
      template< typename ... Ts >
      constexpr auto
      operator()( Ts&& ... xs ) const & {
	return aux( conditional_t<( count_types<Ts...>() == N ), equal_tag,
		    conditional_t< (N > count_types<Ts...>()), less_tag, more_tag >>(),
		    forward<Ts>( xs ) ... );
      }
    private:
      template< typename ... Ts >
      constexpr auto
      aux( equal_tag, Ts&& ... xs ) const & {
	return function_type::call( forward<Ts>( xs ) ... );
      }

      template< typename ... Ts >
      constexpr auto
      aux( less_tag, Ts&& ... xs ) const & {
	return curry<N>( *this )( forward<Ts>( xs ) ... );
      }

      template< typename ... Ts >
      constexpr auto
      aux( more_tag, Ts&& ... xs ) const & {
	return aux2( values( forward<Ts>( xs ) ...  ));
      }

      template< typename T >
      constexpr auto
      aux2( T&& xs ) const & {
	std::cout << xs  << std::endl;
	return apply( apply( *this, take( forward<T>( xs ), nat<N> )),
		      drop( forward<T>( xs ), nat<N>));
      }
      
      
    }; // end of class static curried

    
    
  } // end of namespace Core
} // end of namespace FunctionUtility

#endif // !defined STATIC_APPLICATION_HPP_INCLUDED_452842591972554914
