#ifndef STATIC_CURRIED_HPP_INCLUDED_306387524266182216
#define STATIC_CURRIED_HPP_INCLUDED_306387524266182216 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>
#include <function_utility/curry.hpp>


namespace FunctionUtility
{
  namespace Core
  {

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



    protected:
      Static_curried() = default;
      ~Static_curried() = default;
      
    private:
      
      template< typename ... Ts >
      constexpr auto
      aux( equal_tag, Ts&& ... xs ) const & {
	return function_type::call( forward<Ts>( xs ) ... );
      }

      template< typename ... Ts >
      constexpr auto
      aux( less_tag, Ts&& ... xs ) const & {
	return curry<N>( static_cast<const F&>(*this ))( forward<Ts>( xs ) ... );
      }

      template< typename ... Ts >
      constexpr auto
      aux( more_tag, Ts&& ... xs ) const & {
	return aux2( values( forward<Ts>( xs ) ...  ));
      }

      template< typename T >
      constexpr auto
      aux2( T&& xs ) const & {
	return apply( apply( static_cast<const F&>( *this ), take( forward<T>( xs ), nat<N> )),
		      drop( forward<T>( xs ), nat<N>));
      }
      
      
    }; // end of class static curried

    
    
  } // end of namespace Core
} // end of namespace FunctionUtility

#endif // !defined STATIC_CURRIED_HPP_INCLUDED_306387524266182216
