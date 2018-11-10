#ifndef POWER_HPP_INCLUDED_429174662928402887
#define POWER_HPP_INCLUDED_429174662928402887 1

//
// ... Function Utility header files
//
#include <function_utility/composite.hpp>
#include <function_utility/static_curried.hpp>

namespace FunctionUtility
{
  namespace Core
  {

    

    class Power {
    public:
      template< typename F, size_t N, typename T >
      static constexpr auto
      exec( F&& f, Nat<N>, T&& xs ){
	return aux( f, nat<N>, forward<T>( xs ));
      }
    private:

      template< typename F, typename T >
      static constexpr auto
      aux( F&& , Nat<0>, T&& xs ){
	return forward<T>( xs );
      }
      template< typename F, typename T >
      static constexpr auto
      aux( F&&, Nat<0>, Values<T>&& x ){
	return get<0>( move( x ));
      }
      
      template< typename F, typename T >
      static constexpr auto
      aux( F&&, Nat<0>, const Values<T>& x ){
	return get<0>( x );
      }

      
      template< typename F, typename T >
      static constexpr auto
      aux( F&& f, Nat<1>, T&& xs ){
	return apply( f, values( forward<T>( xs )));
      }

      
      template< typename F, size_t N, typename T >
      static constexpr auto
      aux( F&& f, Nat<N>, T&& xs ){
	return aux( f, nat<N-1>, apply( f, forward<T>( xs )));
      }
    };


    constexpr
    class Powerfunc : public Static_curried<Powerfunc,Nat<2>>
    {
    public:
      template< typename F, size_t N >
      static constexpr auto
      call( F&& f, Nat<N> ){
	return Composite<Power,decay_t<F>,Nat<N>>(
	  forward<F>( f ), nat<N> );
      }
    } powerfunc{}; // end of class Power_func;
    
    
  } // end of namespace Core
} // end of namespace FunctionUtility


#endif // !defined POWER_HPP_INCLUDED_429174662928402887
