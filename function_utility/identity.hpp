#ifndef IDENTITY_HPP_INCLUDED_2288411002301372931
#define IDENTITY_HPP_INCLUDED_2288411002301372931 1

namespace FunctionUtility
{
  namespace Core
  {



    
    constexpr
    class Identity{
    public:
      
      template< typename T >
      constexpr auto
      operator ()( T&& x ) const & {
	return forward<T>( x );
      } // end of operator()

      
      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, Identity ){
	os << "FunctionUtility::Core::identity";
	return os;
      } //end of friend operator<<
      
    } identity{}; // end of class Identity



    
    template< typename Stream >
    Stream&
    operator<<( Stream& os, Type<Identity> ){
      os << "FunctionUtility::Core::Identity";
      return os;
    } // end of operator<<

    
    
  } // end of namespace Core
} // end of namespace FunctionUtility

#endif // !defined IDENTITY_HPP_INCLUDED_2288411002301372931
