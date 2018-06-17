#ifndef CURRY_HPP_INCLUDED_360585343177575083
#define CURRY_HPP_INCLUDED_360585343177575083 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>
#include <function_utility/values.hpp>
#include <function_utility/composite.hpp>


namespace FunctionUtility
{
  namespace Core
  {

    template< size_t N, typename F >
    class Curried : Value<F>{
    public:
      static constexpr size_t arity = N;
      using function_type = F;
      using base = Value<function_type>;

      using base::base;

      template< typename T >
      constexpr auto
      operator ()( T&& arg ) const & {
	using G = decay_t<decltype( part( this->get(), forward<T>( arg )))>;
	return Curried<arity-1,G>( part( this->get(), forward<T>( arg )));
      }

      template< typename T >
      constexpr auto
      operator ()( T&& arg ) && {
	using G = decay_t<decltype( part( this->get(), forward<T>( arg )))>;
	return Curried<arity-1,G>( part( this->get(), forward<T>( arg )));
      }
	
      template< typename T, typename U, typename ... Vs >
      constexpr auto
      operator ()( T&& x, U&& y, Vs&& ... zs ) const & {
	return (*this)( forward<T>( x ))( forward<U>( y ), forward<Vs>( zs ) ... );
      }

      template< typename T, typename U, typename ... Vs >
      constexpr auto
      operator ()( T&& x, U&& y, Vs&& ... zs ) && {
	return (move( *this ))( forward<T>( x ))( forward<U>( y ), forward<Vs>( zs ) ... );
      }

    };




    template< typename F >
    class Curried<1,F> : Value<F>{
    public:
      static constexpr size_t arity = 1;
      using function_type = F;
      using base = Value<function_type>;

      using base::base;

      template< typename T >
      constexpr auto
      operator ()( T&& x ) const & { return this->get()( forward<T>( x )); }

      template< typename T >
      constexpr auto
      operator ()( T&& arg ) && {
	return this->get()( forward<T>( arg ));
      }
	
      template< typename T, typename U, typename ... Vs >
      constexpr auto
      operator ()( T&& x, U&& y, Vs&& ... zs ) const & {
	return (*this)( forward<T>( x ))( forward<U>( y ), forward<Vs>( zs ) ... );
      }

      template< typename T, typename U, typename ... Vs >
      constexpr auto
      operator ()( T&& x, U&& y, Vs&& ... zs ) && {
	return ( *this )( forward<T>( x ))( forward<U>( y ), forward<Vs>( zs ) ... );
      }

    };


    template< size_t N, typename F >
    constexpr auto
    curry( F&& f ){ return Curried<N,F>( forward<F>( f )); }

    template< typename F, size_t N >
    constexpr auto
    curry( F&& f, Nat<N> ){ return Curried<N,F>( forward<F>( f )); }



    



    
    
  } // end of namespace Core
} // end of namespace FunctionUtility
#endif // !defined CURRY_HPP_INCLUDED_360585343177575083
