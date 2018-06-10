#ifndef COMPOSITE_HPP_INCLUDED_2266294756011886040
#define COMPOSITE_HPP_INCLUDED_2266294756011886040 1

//
// ... FunctionUtility header files
//
#include <function_utility/import.hpp>
#include <function_utility/values.hpp>
#include <function_utility/identity.hpp>


namespace FunctionUtility
{
  namespace Core
  {

    /** Generic composite function */
    template< typename E,  typename F, typename G >
    class Composite : pair<F,G>
    {
    public:
      
      using execution_model = E;
      
      using first_type = F;
      using second_type = G;
      using base = pair<F,G>;

      using base::base;


       

      template< typename ... Ts >
      constexpr auto
      operator ()( Ts&& ... xs ) const& {
	return execution_model::exec(
	  base::first,
	  base::second,
	  values( forward<Ts>( xs ) ... ));
      }

      template< typename ... Ts >
      constexpr auto
      operator ()( Ts&& ... xs ) && {
	return execution_model::exec(
	  move( base::first ),
	  move( base::second ),
	  values( forward<Ts>( xs ) ... ));
      }

      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, const Composite& fun ){
	os << type<Composite> << '('
	   << fun.first << ','
	   << fun.second << ')';
	return os;
      }
      
    }; // end of class Composite


    template< typename Stream >
    Stream&
    operator <<( Stream& os, Type1<Composite> ){
      os << "FunctionUtility::Core::Composite";
      return os;
    }


    class After
    {
    public:
      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, Values<Ts... >&& xs ){
	return apply( forward<F>( f ),
		      values( apply( forward<G>( g ),
				     move( xs ))));
      }

      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, const Values<Ts... >& xs ){
	return apply( forward<F>( f ),
		      values( apply( forward<G>( g ),
				     xs )));
      }
      
    }; // end of class After




    class Split
    {
    public:
      
      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, Values<Ts...>&& xs ){
	return values( apply( forward<F>( f ), head( move( xs ))),
		       apply( forward<G>( g ), tail( move( xs ))));
      }
    }; // end of class Split


    class Generalized
    {
    public:
      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, Values<Ts...>&& xs ){
	return apply(
	  apply( forward<F>( f ), xs ),
	  values( apply( forward<G>( g ), xs )));
      }
    }; // end of class Generalized


    class Partial
    {
    public:
      template< typename F, typename T, typename ... Ts >
      static constexpr auto
      exect( F&& f, T&& x, Values<Ts...>&& xs ){
	return apply( forward<F>( f ), values( values( forward<T>( x )), move( xs )));
      }
      
    };

    class RightPartial
    {
    public:
      template< typename F, typename T, typename ... Ts >
      static constexpr auto
      exec( F&& f, T&& x, Values<Ts...>&& xs ){
	return apply( forward<F>( f ), values( move( xs ), values( forward<T>( x ))));
      }
    };


    
    constexpr
    class Compose
    {
    public:
      template< typename F, typename G >
      constexpr auto
      operator ()( F&& f, G&& g ) const & {
	return Composite<After, decay_t<F>, decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      }

      template< typename F, typename G, typename H, typename ... Is >
      constexpr auto
      operator ()( F&& f, G&& g, H&& h, Is&& ... is ) const & {
	return (*this)( forward<F>( f ),
			(*this)( forward<G>( g ),
				 forward<H>( h ),
				 forward<Is>( is ) ... ));
      }

      template< typename Stream >
      friend Stream&
      operator<<( Stream& os, Compose ){
	os << "FunctionUtility::Core::compose";
	return os;
      }
    } compose{}; // end of class Compose
      

    
    
    constexpr
    class PCompose
    {
    public:
      template< typename F, typename G >
      constexpr auto
      operator ()( F&& f, G&& g ) const & {
	return Composite<Split,decay_t<F>, decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      } // end of operator ()


      template< typename F, typename G, typename H, typename ... Is >
      constexpr auto
      operator ()( F&& f, G&& g, H&& h, Is&& ... is ) const & {
	return (*this)( forward<F>( f ),
			(*this)( forward<G>( g ),
				 forward<H>( h ),
				 forward<Is>( is ) ... ));
      } // end of operator ()


      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, PCompose ) {
	os << "FunctionUtility::Core::pcompose";
	return os;
      }
    } pcompose{}; // end of class PCompose


    constexpr
    class Fanout{
    public:
      template< typename F, typename G >
      constexpr auto
      operator ()(  F&& f, G&& g ) const & {
	return compose( pcompose( forward<F>( f ), forward<G>( g )), dup );
      }

      template< typename F, typename G, typename H, typename ... Is >
      constexpr auto
      operator ()( F&& f, G&& g, H&& h, Is&& ... is ) const & {
	return (*this)( forward<F>( f ), 
			(*this)( forward<G>( g ),
				 forward<H>( h ),
				 forward<Is>( is ) ... ));
      }
    } fanout{};


    constexpr
    class First{
    public:
      template< typename F >
      constexpr auto
      operator ()( F&& f ) const & {
	return pcompose( forward<F>( f ), identity );
      }
    } first{}; // end of class First

    constexpr
    class Second{
    public:
      template< typename F >
      constexpr auto
      operator ()( F&& f ) const & {
	return pcompose( identity, forward<F>( f ));
      }
    } second{};




    constexpr
    class SCompose {
    public:
      template< typename F, typename G >
      constexpr auto
      operator ()( F&& f, G&& g ) const &{
	return Composite<Generalized,decay_t<F>,decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      }


      template< typename F, typename G, typename H, typename ... Is >
      constexpr auto
      operator ()( F&& f, G&& g, H&& h, Is&& ... is ) const & {
	return (*this)( forward<F>( f ), 
			(*this)( forward<G>( g ),
				 forward<H>( h ),
				 forward<Is>( is ) ... ));
      }
    } scompose{};



    constexpr
    class Part{
    public:
      template< typename F, typename T >
      constexpr auto
      operator ()( F&& f, T&& x ) const & {
	return Composite<Partial,decay_t<F>,decay_t<T>>(
	  forward<F>( f ),
	  forward<T>( x ));
      }

      template< typename F, typename T, typename U, typename ... Vs >
      constexpr auto
      operator ()( F&& f, T&& x, U&& y, Vs&& ... zs ) const & {
	return (*this)( (*this)( forward<F>( f ), forward<T>( x )),
			forward<U>( y ),
			forward<Vs>( zs ) ... );
      }
      
    } part{}; // end of class Part

    constexpr
    class RPart{
    public:
      template< typename F, typename T >
      constexpr auto
      operator ()( F&& f, T&& x ) const & {
	return Composite<RightPartial,decay_t<F>,decay_t<T>>(
	  forward<F>( f ),
	  forward<T>( x ));
      }

      template< typename F, typename T, typename U, typename ... Vs >
      constexpr auto
      operator ()( F&& f, T&& x, U&& y, Vs&& ... zs ) const {
	return (*this)( (*this)( forward<F>( f ), forward<U>( y ), forward<Vs>( zs ) ... ),
			forward<T>( x ));
      }
      
    } rpart{}; // end of class RPart;


    

    
    
  } // end of namespace Core
} // end of namespace FunctionUtility


#endif // !defined COMPOSITE_HPP_INCLUDED_2266294756011886040
