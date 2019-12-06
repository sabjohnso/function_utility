#pragma once
/**
 * @file function_utility/values.hpp
 *
 * @brief A file containing the definition of a class template and helper
 * functions to support multiple values in function application and function
 * return context.
 */

// TODO: Evaluate and document printing functions

//
// ... Function Utility header files
//
#include <function_utility/import.hpp>

namespace FunctionUtility::Core {

  /**
   * @brief A class template for representing multiple values in a
   * function application or return context.
   *
   * @details The intent of this type is to facilitate the composition
   * of functions accepting or returning mutliple arguments. Specializations
   * are essentially tuples, makeing this type is necessary for to provide
   * a distinction between function application to a single argument that
   * is a tuple and function application over multiple arguemnts.
   */
  template<typename... Ts>
  class Values : tuple<Ts...>
  {
  public:
    using base = tuple<Ts...>;
    using base::base;

  private:
    /**
     * @brief Select values from an rvalue reference based on position
     *
     * @details This function returns a sequence of values that are
     * selected from the first argument  based on the values in the
     * template parameter list of the second argument.
     *
     */
    template<size_t... indices>
    friend constexpr auto
    select(Values&& xs, index_sequence<indices...>)
    {

      return select_aux(
        TypeUtility::select(types<Ts...>, index_sequence<indices...>()),
        index_sequence<indices...>(),
        move(xs));
    }

    /**
     * @brief Select values based on position
     *
     * @details This function returns a sequence of values that are
     * selected from the first argument  based on the values in the
     * template parameter list of the second argument.
     */
    template<size_t... indices>
    friend constexpr auto
    select(const Values& xs, index_sequence<indices...>)
    {
      return select_aux(
        TypeUtility::select(types<Ts...>, index_sequence<indices...>()),
        index_sequence<indices...>(),
        xs);
    }

    /**
     * @brief Select values based on position provided the types
     *
     * @details This static member function is an auxilliary function
     * to the overloads of the select friend functions and provides
     * the actual extraction of values and construction of the new
     * Values object.
     */
    template<typename... Us, size_t... indices, typename T>
    static constexpr auto
    select_aux(Type_sequence<Us...>, index_sequence<indices...>, T&& xs)
    {
      return Values<Us...>(get<indices>(forward<T>(xs))...);

      static_assert(count_types<Us...>() == count_types<decltype(indices)...>(),
                    "Expected equal number of types and indices");
    }

    /**
     * @brief Extract a single value from an rvalue reference to multiple values
     */
    template<size_t index>
    friend constexpr auto
    get(Values&& xs)
    {
      using std::get;
      return get<index>(static_cast<base&&>(move(xs)));
    }

    /**
     * @brief Extract a single value from multiple values
     */
    template<size_t index>
    friend constexpr auto
    get(const Values& xs)
    {
      using std::get;
      return get<index>(static_cast<const base&>(xs));
    }

    /**
     * @brief Apply a function to values
     *
     * @details This static member function is an auxilliary function
     * to the overloads of the friend function apply for rvalue
     * references
     */
    template<size_t... indices, typename F>
    static constexpr auto
    apply_aux(index_sequence<indices...>, F&& f, Values&& xs)
    {
      return forward<F>(f)(get<indices>(move(xs))...);
    }

    /**
     * @brief Apply a function to values
     *
     * @details This static member function is an auxilliary function
     * to the overloads of the friend function apply for const references
     */
    template<size_t... indices, typename F>
    static constexpr auto
    apply_aux(index_sequence<indices...>, F&& f, const Values& xs)
    {
      return forward<F>(f)(get<indices>(xs)...);
    }

    /**
     * @brief Apply a function to values
     */
    template<typename F>
    friend constexpr auto
    apply(F&& f, const Values& xs)
    {
      return apply_aux(generate_indices<Ts...>(), forward<F>(f), xs);
    }

    /**
     * @brief Apply a function to values
     */
    template<typename F>
    friend constexpr auto
    apply(F&& f, Values&& xs)
    {
      return apply_aux(generate_indices<Ts...>(), forward<F>(f), move(xs));
    }

    /**
     * @bief Append sequences of values
     */
    template<size_t... xindicies, size_t... yindicies, typename... Us>
    static constexpr auto
    append_aux(index_sequence<xindicies...>,
               index_sequence<yindicies...>,
               Values&& xs,
               Values<Us...>&& ys)
    {
      return Values<Ts..., Us...>(get<xindicies>(move(xs))...,
                                  get<yindicies>(move(ys))...);
    }

    /**
     * @brief Append sequences of values
     */
    template<typename... Us>
    friend constexpr auto
    append(Values&& xs, Values<Us...>&& ys)
    {
      return append_aux(generate_indices<Ts...>(),
                        generate_indices<Us...>(),
                        move(xs),
                        move(ys));
    }

    /**
     * @brief Take a number of values from an input sequence of values
     */
    template<size_t N>
    friend constexpr auto
    take(Values&& xs, Nat<N>)
    {
      return select_aux(
        take(types<Ts...>, nat<N>), generate_indices<N>(), move(xs));
    }

    /**
     * @brief Take a number of values from an input sequence of values
     */
    template<size_t N>
    friend constexpr auto
    take(const Values& xs, Nat<N>)
    {
      return select(take(types<Ts...>, nat<N>), generate_indices<N>(), xs);
    }

    /**
     * @brief Drop a number of values from an input sequence of values
     */
    template<size_t N>
    friend constexpr auto
    drop(Values&& xs, Nat<N>)
    {
      static_assert(N <= count_types<Ts...>(), "Expected sufficient types");
      static_assert(length(drop(types<Ts...>, nat<N>)) ==
                    length(drop(generate_indices<Ts...>(), nat<N>)));
      return select_aux(drop(types<Ts...>, nat<N>),
                        drop(generate_indices<Ts...>(), nat<N>),
                        move(xs));
    }

    /**
     * @brief Take a number of values from an input sequence of values
     */
    template<size_t N>
    friend constexpr auto
    drop(const Values& xs, Nat<N>)
    {
      static_assert(N <= count_types<Ts...>(), "Expected sufficient types");
      static_assert(length(drop(types<Ts...>, nat<N>)) ==
                    length(drop(generate_indices<Ts...>(), nat<N>)));
      return select(drop(types<Ts...>, nat<N>),
                    drop(generate_indices<Ts...>(), nat<N>),
                    xs);
    }

    template<size_t index, typename Stream>
    static Stream&
    print_values(index_sequence<>, Stream& os, const Values&)
    {
      return os;
    }

    template<size_t index, typename Stream>
    static Stream&
    print_values(index_sequence<index>, Stream& os, const Values& xs)
    {
      os << get<index>(xs);
      return os;
    }

    template<size_t index0, size_t index1, size_t... indices, typename Stream>
    static Stream&
    print_values(index_sequence<index0, index1, indices...>,
                 Stream& os,
                 const Values& xs)
    {
      os << get<index0>(xs) << ',';
      return print_values(index_sequence<index1, indices...>(), os, xs);
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, const Values& xs)
    {
      print_values(generate_indices<Ts...>(), os, xs);
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
    template<typename F>
    friend constexpr auto
    apply_each(F&& f, Values&& xs)
    {
      return apply_each_aux(types<result_of_t<decay_t<F>(Ts)>...>,
                            generate_indices<Ts...>(),
                            forward<F>(f),
                            move(xs));
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
    template<typename F>
    friend constexpr auto
    apply_each(F&& f, const Values& xs)
    {
      return apply_each_aux(types<result_of_t<decay_t<F>(Ts)>...>,
                            generate_indices<Ts...>(),
                            forward<F>(f),
                            xs);
    }

    /**
     * @brief Apply a function to each value
     *
     * @details This static member function provides
     * auxilliary functionality to the apply_aach
     * friend function.  This function is private and
     * not intended as part of the API for the Values class.
     */
    template<size_t... indices, typename F, typename... Us, typename T>
    static constexpr auto
    apply_each_aux(index_sequence<indices...>,
                   Type_sequence<Us...>,
                   F&& f,
                   T&& xs)
    {
      return Values<Us...>(f(get<indices>(forward<T>(xs)))...);
    }

  }; // end of class Values

  /**
   * @brief Construct an empty values object
   */
  constexpr auto
  values()
  {
    return Values<>();
  }

  /**
   * @brief Construct a value object from an input values object
   */
  template<typename... Ts>
  constexpr auto
  values(Values<Ts...>&& xs)
  {
    return move(xs);
  }

  /**
   * @brief Construct a values object from an input values object
   */
  template<typename... Ts>
  constexpr auto
  values(const Values<Ts...>& xs)
  {
    return xs;
  }

  /**
   * @brief Construct a values object from a single input value
   */
  template<typename T>
  constexpr auto
  values(T&& x)
  {
    return Values<decay_t<T>>(forward<T>(x));
  }

  /**
   * @brief Construct a values object from two input values objects
   */
  template<typename... Ts, typename... Us>
  constexpr auto
  values(Values<Ts...>&& xs, Values<Us...>&& ys)
  {
    return append(move(xs), move(ys));
  }

  /**
   * @brief Construct a values object from multiple input values
   */
  template<typename T, typename U, typename... Vs>
  constexpr auto
  values(T&& a, U&& b, Vs&&... cs)
  {
    return values(values(values(forward<T>(a)), values(forward<U>(b))),
                  values(forward<Vs>(cs))...);
  }

  /**
   * @brief Return the first value in a values object
   */
  template<typename... Ts>
  constexpr auto
  head(const Values<Ts...>& xs)
  {
    return values(get<0>(xs));
  }

  /**
   * @brief Return the first value in a values object
   */
  template<typename... Ts>
  constexpr auto
  head(Values<Ts...>&& xs)
  {
    return values(get<0>(move(xs)));
  }

  template<size_t index, size_t... indices, typename... Ts>
  constexpr auto
  tail_aux(index_sequence<index, indices...>, Values<Ts...>&& xs)
  {
    return values(get<indices>(move(xs))...);
  }

  /**
   * @brief Return a values object containing all but the
   * first value in the input values object
   */
  template<typename... Ts>
  constexpr auto
  tail(Values<Ts...>&& xs)
  {
    return tail_aux(generate_indices<Ts...>(), move(xs));
  }

  /**
   * @brief Return a values object containing all but the
   * first value in the input values object
   *
   * @details This function is an auxilliary function for
   * tail, where tail generates the index sequence that is
   * used to extract the values in the call to this function.
   */
  template<size_t index, size_t... indices, typename... Ts>
  constexpr auto
  tail_aux(index_sequence<index, indices...>, const Values<Ts...>& xs)
  {
    return values(get<indices>(xs)...);
  }

  /**
   * @brief Return a values object containing all but the
   * first value in the input values object
   */
  template<typename... Ts>
  constexpr auto
  tail(const Values<Ts...>& xs)
  {
    return tail_aux(generate_indices<Ts...>(), xs);
  }

  /**
   * @brief Return true, indicating the equality of two
   * empty values objects
   */
  constexpr auto
  operator==(const Values<>&, const Values<>&)
  {
    return true;
  }

  /**
   * @brief Return true if the values objects are equal
   * and false if they are not
   */
  template<typename T, typename U, typename... Vs>
  constexpr auto
  operator==(const Values<T, U, Vs...>& xs, const Values<T, U, Vs...>& ys)
  {
    return head(xs) == head(ys) ? tail(xs) == tail(ys) : false;
  }

  /**
   * @brief Return true if the values objects are equal
   * and false if they are not
   *
   * @details This operator is specialize for the case of one value in
   * each of the input objects and the result is the result of
   * evaluating the equality of the contained object.
   */
  template<typename T>
  constexpr auto
  operator==(const Values<T>& x, const Values<T>& y)
  {
    return get<0>(x) == get<0>(y);
  }

} // end of namespace FunctionUtility::Core
