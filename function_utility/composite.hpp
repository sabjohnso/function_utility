#ifndef COMPOSITE_HPP_INCLUDED_2266294756011886040
#define COMPOSITE_HPP_INCLUDED_2266294756011886040 1

//
// ... FunctionUtility header files
//
#include <function_utility/import.hpp>
#include <function_utility/values.hpp>
#include <function_utility/identity.hpp>
#include <function_utility/static_application.hpp>




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

      template< typename T, typename U >
      constexpr
      Composite( T&& x, U&& y )
	: base( forward<T>( x ), forward<U>( y ))
      {}

      
      Composite(){}
      ~Composite() = default;
       

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

      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, const Values<Ts...>& xs ){
	return values( apply( forward<F>( f ), head( xs )),
		       apply( forward<G>( g ), tail( xs )));
      }
    }; // end of class Split





    /**
     * @brief Execution model for generalized
     */
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


    
    /**
     * @brief Execution model for Partial application. 
     */
    class Partial
    {
    public:
      template< typename F, typename T, typename ... Ts >
      static constexpr auto
      exec( F&& f, T&& x, Values<Ts...>&& xs ){
	return apply( forward<F>( f ), values( values( forward<T>( x )), move( xs )));
      }

      Partial() = default;
      ~Partial() = default;
	
      
    };

    /**
     * @brief Execution model for right partial application. 
     */
    class RightPartial
    {
    public:
      template< typename F, typename T, typename ... Ts >
      static constexpr auto
      exec( F&& f, T&& x, Values<Ts...>&& xs ){
	return apply( forward<F>( f ), values( move( xs ), values( forward<T>( x ))));
      }
    };


    /** 
     * @brief Function composition
     *
     * @details
     *
     */
    constexpr
    class Compose : public  Static_callable<Compose>
    {
    public:
      template< typename F, typename G >
      static constexpr auto
      call( F&& f, G&& g ){
	return Composite<After, decay_t<F>, decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      }

      template< typename F, typename G, typename H, typename ... Is >
      static constexpr auto
      call( F&& f, G&& g, H&& h, Is&& ... is ){
	return call( forward<F>( f ),
		     call( forward<G>( g ),
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
      

    
    /**
     * @brief Return a function that applies the
     * input functions currently over its input 
     * arguments.
     *
     * @details 
     */
    constexpr
    class PCompose : public Static_callable<PCompose>
    {
    public:

      template< typename F, typename G >
      static constexpr auto
      call( F&& f, G&& g ){
	return Composite<Split,decay_t<F>, decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      } // end of function call


      template< typename F, typename G, typename H, typename ... Is >
      static constexpr auto
      call( F&& f, G&& g, H&& h, Is&& ... is ){
	return call( forward<F>( f ),
		     call( forward<G>( g ),
			   forward<H>( h ),
			   forward<Is>( is ) ... ));
      } // end of function call


      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, PCompose ) {
	os << "FunctionUtility::Core::pcompose";
	return os;
      }
    } pcompose{}; // end of class PCompose


    /** 
     * @brief An execution model duplicating the input and 
     * send one copy to the first function and one to the second.
     */    
    class Dup
    {
    public:
      template< typename F, typename G, typename T >
      static constexpr auto
      exec( F&& f, G&& g, const T& xs ){
	return values( apply( forward<F>( f ), xs ),
		       apply( forward<G>( g ), xs ));
      }
    }; // end of class Dup

    
    /**
     * @brief Return a function applies each of the
     * input funtions to all of the input arguments.
     *
     * @details
     */
    constexpr
    class Fanout : public Static_callable<Fanout>{
    public:

      template< typename F, typename G >
      static constexpr auto
      call(  F&& f, G&& g ){
	return Composite<Dup,decay_t<F>,decay_t<G>>( forward<F>( f ), forward<G>( g ));
      } // end of function call

      template< typename F, typename G, typename H, typename ... Is >
      static constexpr auto
      call( F&& f, G&& g, H&& h, Is&& ... is ){
	return call( forward<F>( f ), 
		     call( forward<G>( g ),
			   forward<H>( h ),
			   forward<Is>( is ) ... ));
      } // end of function call


      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, Fanout ) {
	os << "FunctionUtility::Core::fanout";
	return os;
      }// end of operator <<
      
    } fanout{}; // end of class Fanout


    
    
    /**
     * @brief Return a function that applies the input function
     * to its first argument and passes the remaining arguments 
     * unaltered.
     *
     * @details
     */
    constexpr
    class First{
    public:
      template< typename F >
      constexpr auto
      operator ()( F&& f ) const & {
	return pcompose( forward<F>( f ), identity );
      }
    } first{}; // end of class First

    /**
     * @brief Return a function passing the first argument
     * unaltered and the input function applied to the 
     * remaining arguments
     *
     * @details
     */
    constexpr
    class Rest : public Static_callable<Rest> {
    public:
      template< typename F >
      static constexpr auto
      call( F&& f ){
	return pcompose( identity, forward<F>( f ));
      }

      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, Rest ){
	os << "FunctionUtility::Core::Rest";
	return os;
      }
    } rest {}; // end of class Rest


    /**
     * @brief Return a function selecting arguments based on an index_sequence
     *
     * @details 
     */


    
   


    /**
     * @brief Generalized application
     *
     * @details
     */
    constexpr
    class SCompose : public Static_callable<SCompose> {
    public:
      template< typename F, typename G >
      static constexpr auto
      call( F&& f, G&& g ){
	return Composite<Generalized,decay_t<F>,decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      }


      template< typename F, typename G, typename H, typename ... Is >
      static constexpr auto
      call( F&& f, G&& g, H&& h, Is&& ... is ){
	return call( forward<F>( f ), 
		     call( forward<G>( g ),
			   forward<H>( h ),
			   forward<Is>( is ) ... ));
      }

      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, SCompose ){
	os << "FunctionUtility::Core::scompose";
	return os;
      }
    } scompose{}; // end of class SCompose



    /**
     * @brief Partial function application
     */
    constexpr
    class Part : public Static_callable<Part> { 
    public:
      template< typename F, typename T >
      static constexpr auto
      call( F&& f, T&& x ){
	return Composite<Partial,decay_t<F>,decay_t<T>>(
	  forward<F>( f ),
	  forward<T>( x ));
      }

      template< typename F, typename T, typename U, typename ... Vs >
      static constexpr auto
      call( F&& f, T&& x, U&& y, Vs&& ... zs ){
	return call( call( forward<F>( f ), forward<T>( x )),
		     forward<U>( y ),
		     forward<Vs>( zs ) ... );
      }

      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, Part ){
	os << "FunctionUtility::Core::Part";
	return os;
      }
      
    } part{}; // end of class Part



    /**
     * @brief Right partial function application 
     */
    constexpr
    class RPart : public Static_callable<RPart> {
    public:
      
      template< typename F, typename T >
      static constexpr auto
      call( F&& f, T&& x ){
	return Composite<RightPartial,decay_t<F>,decay_t<T>>(
	  forward<F>( f ),
	  forward<T>( x ));
      }

      template< typename F, typename T, typename U, typename ... Vs >
      static constexpr auto
      call( F&& f, T&& x, U&& y, Vs&& ... zs ){
	return call( call( forward<F>( f ), forward<U>( y ), forward<Vs>( zs ) ... ),
		     forward<T>( x ));
      }

      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, RPart ){
	os << "FunctionUtility::Core::rpart";
	return os;
      }
      
    } rpart{}; // end of class RPart;


    
    
  } // end of namespace Core
} // end of namespace FunctionUtility


#endif // !defined COMPOSITE_HPP_INCLUDED_2266294756011886040
