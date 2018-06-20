#ifndef SELECT_HPP_INCLUDED_1644263888070028833
#define SELECT_HPP_INCLUDED_1644263888070028833 1

//
// ... Function Utility header files
//
#include <function_utility/composite.hpp>
#include <function_utility/static_curried.hpp>

namespace FunctionUtility
{
  namespace Core
  {


    /** 
     * @brief An application model that select applies a function
     * to selection of values.
     */
    class Select
    {
    public:
      template< typename F, size_t ... indices, typename T >
      static constexpr auto
      exec( F&& f, index_sequence<indices...>, T&& xs ){
	return apply( f, select( forward<T>( xs ),
				 index_sequence<indices...>{}));
      }
    }; // end of class Select

    
    constexpr
    class Selection : public Static_curried<Selection,Nat<2>>{
    public:
      template< typename F, size_t ... indices >
      static constexpr auto
      call( F&& f, index_sequence<indices ...> ){
	return Composite<Select,decay_t<F>,index_sequence<indices ...>>(
	  forward<F>( f ),
	  index_sequence<indices...>());
      }
    }selection{}; // end of class Selection

  } // end of namespace Core
} // end of namespace FunctionUtility

#endif // !defined SELECT_HPP_INCLUDED_1644263888070028833
