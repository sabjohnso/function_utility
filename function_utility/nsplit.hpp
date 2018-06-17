#ifndef NSPLIT_HPP_INCLUDED_1238837879826989914
#define NSPLIT_HPP_INCLUDED_1238837879826989914 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>
#include <function_utility/values.hpp>
#include <function_utility/composite.hpp>
#include <function_utility/static_application.hpp>



namespace FunctionUtility
{
  namespace Core
  {

    /** 
     * @brief An execution mode for partitioning arguments
     * between functions
     */
    template< size_t N >
    class NSplit
    {
    public:
      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, Values<Ts...>&& xs ){
	return values( apply( forward<F>( f ), take( move( xs ), nat<N> )),
		       apply( forward<G>( g ), drop( move( xs ), nat<N> )));
      }

      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, const Values<Ts...>& xs ){
	return values( apply( forward<F>( f ), take( xs, nat<N> )),
		       apply( forward<G>( g ), drop( xs, nat<N> ))); 
      }
    }; // end of class NSplit
    

    /** 
     * @brief An execution model for partitioning arguments
     * between functions
     */
    template< size_t N, size_t M >
    class NMSplit
    {
    public:
      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, Values<Ts...>&& xs ){
	return values( apply( forward<F>( f ), take( move( xs ), nat<N> )),
		       apply( forward<G>( g ), take( drop( move( xs ), nat<N> ), nat<M> )));
      }

      template< typename F, typename G, typename ... Ts >
      static constexpr auto
      exec( F&& f, G&& g, const Values<Ts...>& xs ){
	return values( apply( forward<F>( f ), take( xs, nat<N> )),
		       apply( forward<G>( g ), take( drop( xs, nat<N> ), nat<M> )));
      }
    }; // end of class NSplit


    constexpr
    class Partition : public Static_callable<Partition>{
    public:
      template< typename F, size_t N, typename G, size_t M >
      static constexpr auto
      call( F&& f, Nat<N>, G&& g, Nat<M> ){
	return Composite<NMSplit<N,M>,decay_t<F>,decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      }

      template< typename F, size_t N, typename G >
      static constexpr auto
      call( F&& f, Nat<N>, G&& g ){
	return Composite<NSplit<N>,decay_t<F>,decay_t<G>>(
	  forward<F>( f ),
	  forward<G>( g ));
      }

      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, Partition ){
	os << "FunctionUtility::Core::partition";
	return os;
      }
    } partition{};
    


    

    

  } // end of namespace Core
} // end of namespace FunctionUtility
#endif // !defined NSPLIT_HPP_INCLUDED_1238837879826989914
