#ifndef VALUES_HPP_INCLUDED_19995948350155737
#define VALUES_HPP_INCLUDED_19995948350155737 1

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>


namespace FunctionUtility
{
  namespace Core
  {


    template< typename ... Ts >
    class Values : tuple<Ts...>
    {
    public:

      using base = tuple<Ts...>;
      using base::base;

    private:

      template< size_t ... indices >
      friend constexpr auto
      select( Values&& xs, index_sequence<indices...>){

	return select( 
	  TypeUtility::select( types<Ts...>, index_sequence<indices...>()),
	  index_sequence<indices...>(),
	  move( xs ));
      }

      template< size_t ... indices >
      friend constexpr auto
      select( const Values& xs, index_sequence<indices...> ){
	return select(
	  TypeUtility::select( types<Ts...>, index_sequence<indices...>()),
	  index_sequence<indices...>(),
	  xs );
      }

	  

      template<  typename ... Us, size_t ... indices, typename T >
      static constexpr auto
      select( Type_sequence<Us...>,
	      index_sequence<indices...>,
	      T&& xs ){
	static_assert( 
	  count_types<Us...>() == count_types<decltype(indices) ...>(),
	  "Expected equal number of types and indices" );
	return Values<Us...>( get<indices>( forward<T>( xs )) ... );
      }


      template< size_t index >
      friend constexpr auto
      get( Values&& xs ){
	using std::get;
	return get<index>( static_cast<base&&>( move( xs )));
      }

      
      template< size_t index >
      friend constexpr auto
      get( const Values& xs ){
	using std::get;
	return get<index>( static_cast<const base&>( xs ));
      }


      
      template< size_t ... indices, typename F >
      static constexpr auto
      aux( index_sequence<indices ...>, F&& f, Values&& xs ){
	return forward<F>( f )( get<indices>( move( xs )) ... );
      }

                  
      template< size_t ... indices, typename F >
      static constexpr auto
      aux( index_sequence<indices ...>, F&& f, const Values& xs ){
	return forward<F>( f )( get<indices>( xs ) ... );
      }
      
      
      template< typename F >
      friend constexpr auto
      apply( F&& f, const Values& xs ){
	return aux( generate_indices<Ts...>(), forward<F>( f ), xs ); 
      }

      template< typename F >
      friend constexpr auto
      apply( F&& f, Values&& xs ){
	return aux( generate_indices<Ts...>(), forward<F>( f ),
		    move( xs ));
      }
      

      template< size_t ... xindicies, size_t ... yindicies, typename ... Us >
      static constexpr auto
      append_aux( index_sequence<xindicies...>,
		  index_sequence<yindicies...>,
		  Values&& xs,
		  Values<Us...>&& ys ){
	return Values<Ts...,Us...>(
	  get<xindicies>( move( xs )) ...,
	  get<yindicies>( move( ys )) ... );
      }
	

      template< typename ... Us >
      friend constexpr auto
      append( Values&& xs, Values<Us...>&& ys ){
	return append_aux(
	  generate_indices<Ts...>(),
	  generate_indices<Us...>(),
	  move( xs ),
	  move( ys ));
      }


      template< size_t N >
      friend constexpr auto
      take( Values&& xs, Nat<N>){
	return select(
	  take( types<Ts...>, nat<N> ),
	  generate_indices<N>(),
	  move( xs ));
      }

      template< size_t N >
      friend constexpr auto
      take( const Values& xs, Nat<N> ){
	return select(
	  take( types<Ts...>, nat<N> ),
	  generate_indices<N>(),	  
	  xs );
      }



      template< size_t N >
      friend constexpr auto
      drop( Values&& xs, Nat<N> ){
	static_assert( N <= count_types<Ts...>(), "Expected sufficient types" );
	static_assert(
	  length( drop( types<Ts...>, nat<N> )) ==
	  length( drop( generate_indices<Ts...>(), nat<N> )));			       
	return select(
	  drop( types<Ts...>, nat<N> ),
	  drop( generate_indices<Ts...>(), nat<N> ),
	  move( xs ));
      }

      
      template< size_t N >
      friend constexpr auto
      drop( const Values& xs, Nat<N>){
	static_assert( N <= count_types<Ts...>(), "Expected sufficient types" );
	static_assert( 
	  length( drop( types<Ts...>, nat<N> )) ==
	  length( drop( generate_indices<Ts...>(), nat<N> )));
	return select(
	  drop( types<Ts...>, nat<N> ),
	  drop( generate_indices<Ts...>(), nat<N> ),
	  xs );
      }

      template< size_t index, typename Stream >
      static Stream&
      print_values( index_sequence<>, Stream& os, const Values& ){
	return os;
      }

      template< size_t index, typename Stream >
      static Stream&
      print_values( index_sequence<index>, Stream& os, const Values& xs ){
	os << get<index>( xs );
	return os;
      }

      template< size_t index0, size_t index1,  size_t ... indices, typename Stream >
      static Stream&
      print_values( index_sequence<index0,index1,indices...>, Stream& os, const Values& xs ){
	os << get<index0>( xs ) << ',';
	return print_values( index_sequence<index1,indices...>(), os, xs );
      }


      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, const Values& xs ){
	print_values( generate_indices<Ts...>(), os,  xs );
	return os;
      }


      //
      // ... apply a function to each value
      //
      
      /** 
       * @brief Apply a function to each value
       *
       * @details This overload of apply_each is a friend to
       * the Values class accepting a function and and an rvalue 
       * reference to a Values instance. The result is, an instance of Values,
       * specialized with the appropiate type parametes, that 
       * corresponds to applying the input function over each of the 
       * input values, individually.
       */
      template< typename F >
      friend constexpr auto
      apply_each( F&& f, Values&& xs ){
	return apply_each_aux(
	  types<result_of_t<decay_t<F>(Ts)>...>,
	  generate_indices<Ts...>(),
	  forward<F>( f ), move( xs ));
	
      }

      /** 
       * @brief Apply a function to each value
       *
       * @details This overload of apply_each is a friend to
       * the Values class accepting a function and and a const
       * reference to a Values instance. The result is, an instance of Values,
       * specialized with the appropiate type parametes, that 
       * corresponds to applying the input function over each of the 
       * input values, individually.
       */
      template< typename F >
      friend constexpr auto
      apply_each( F&& f, const Values& xs ){
	return apply_each_aux(
	  types<result_of_t<decay_t<F>(Ts)>...>,
	  generate_indices<Ts...>(),
	  forward<F>( f ),
	  xs );	
      }

      /** 
       * @brief Apply a function to each value
       *
       * @details This static member function provides
       * auxilliary functionality to the apply_aach
       * friend function.  This function is private and
       * not intended as part of the API for the Values class.
       */
      template< size_t ... indices, typename F, typename ... Us, typename T >
      static constexpr auto
      apply_each_aux( index_sequence<indices...>, Type_sequence<Us...>, F&& f, T&& xs ){
	return Values<Us...>( f( get<indices>( forward<T>( xs ))) ... );
      }

      

      }; // end of class Values
    
    

      constexpr auto
      values(){ return Values<>(); }

      template< typename ... Ts >
      constexpr auto
      values( Values<Ts...>&& xs ){ return move( xs ); }

      template< typename ... Ts >
      constexpr auto
      values( const Values<Ts...>& xs ){ return xs; }

      template< typename T >
      constexpr auto
      values( T&& x ){ return Values<decay_t<T>>( forward<T>( x )); }


      template< typename ... Ts, typename ... Us >
      constexpr auto
      values( Values<Ts...>&& xs, Values<Us...>&& ys ){ return append( move( xs ), move( ys )); }

      template< typename T, typename U, typename ... Vs >
      constexpr auto
      values( T&& a, U&& b, Vs&& ... cs ){
	return values(
	  values( values( forward<T>( a )), values( forward<U>( b ))),
	  values( forward<Vs>( cs )) ...  );
      }

      template< typename ... Ts >
      constexpr auto
      head( const Values<Ts...>& xs ){
	return values( get<0>( xs ));
      }
	

      template< typename ... Ts >
      constexpr auto
      head( Values<Ts...>&& xs ){
	return values( get<0>( move( xs )));
      }




      template< size_t index, size_t ... indices, typename ... Ts >
      constexpr auto
      tail_aux( index_sequence<index,indices...>, Values< Ts ... >&& xs ){
	return values( get<indices>( move( xs )) ... );
      }

      template< typename ... Ts >
      constexpr auto
      tail( Values<Ts...>&& xs ){
	return tail_aux( generate_indices<Ts...>(), move( xs ));
      }




    
      template< size_t index, size_t ... indices, typename ... Ts >
      constexpr auto
      tail_aux( index_sequence<index,indices...>, const Values< Ts ... >& xs ){
	return values( get<indices>( xs ) ... );
      }

      template< typename ... Ts >
      constexpr auto
      tail( const Values<Ts...>& xs ){
	return tail_aux( generate_indices<Ts...>(), xs );
      }





    


    

    


      constexpr auto
      operator ==( const Values<>&, const Values<>& ){
	return true;
      }
    


      template< typename T, typename U, typename ... Vs >
      constexpr auto
      operator ==( const Values<T,U,Vs...>& xs, const Values<T,U,Vs...>& ys ){
	return head( xs ) == head( ys )
	  ? tail( xs ) == tail( ys )
	  : false;
      }
    


      template< typename T>
      constexpr auto
      operator ==( const Values<T>& x, const Values<T>& y ){
	return get<0>( x ) == get<0>( y );
      }

    
    
    } // end of namespace Core
  } // end of namespace FunctionUtility

#endif // !defined VALUES_HPP_INCLUDED_19995948350155737
