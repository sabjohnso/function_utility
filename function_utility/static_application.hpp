#ifndef STATIC_APPLICATION_HPP_INCLUDED_452842591972554914
#define STATIC_APPLICATION_HPP_INCLUDED_452842591972554914 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>


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

    protected:
      Static_callable() = default;
      ~Static_callable() = default;
      
    }; // end of class Static_callable


    

    
  } // end of namespace Core
} // end of namespace FunctionUtility

#endif // !defined STATIC_APPLICATION_HPP_INCLUDED_452842591972554914
