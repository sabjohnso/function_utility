#pragma once
//
// ... Function Utility header files
//
#include <function_utility/static_application.hpp>

namespace FunctionUtility::Core {

  /**
   * @brief A struct providing the identity function
   */
  constexpr class Identity : public Static_callable<Identity>
  {
  public:
    /**
     * @brief Return the input
     */
    template<typename T>
    static constexpr auto
    call(T&& x)
    {
      return std::forward<T>(x);
    }

    /**
     * @brief Inject a text representation of the static instance
     * of this class as any instance of this class into an output
     * stream
     */
    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Identity)
    {
      os << "FunctionUtility::Core::identity";
      return os;
    } // end of friend operator<<

  } identity{}; // end of class Identity

  /**
   * @brief Inject a text representation of the Identity Type
   * into an output stream.
   */
  template<typename Stream>
  Stream&
  operator<<(Stream& os, Type<Identity>)
  {
    os << "FunctionUtility::Core::Identity";
    return os;
  } // end of operator<<

} // end of namespace FunctionUtility::Core
