#ifndef TRAMPOLINE_HPP_INCLUDED_1344546961191746609
#define TRAMPOLINE_HPP_INCLUDED_1344546961191746609 1

//
// ... Function Utiliyt header files
//
#include <function_utility/import.hpp>

namespace FunctionUtility::Core
{
  template<typename T>
  using Thunk_of = function<T()>;

  template<typename T, template<typename > class Thunk = Thunk_of>
  class Trampoline
  {
  public:

    using value_type = T;
    using const_reference = value_type const&;
    using rvalue_reference = value_type &&;

  private:

    using thunk_type = Thunk<Trampoline>;
    using thunk_const_reference = thunk_type const&;
    using thunk_rvalue_reference = thunk_type &&;

    using data_type = variant<value_type, thunk_type>;

    mutable data_type data;
    mutable mutex mex;

  public:

    Trampoline(const_reference value) : data(value) {}
    Trampoline(rvalue_reference value) : data(move(value)) {}
    Trampoline(thunk_const_reference thunk) : data(thunk) {}
    Trampoline(thunk_rvalue_reference thunk) : data(move(thunk)) {}

    const_reference
    operator *() const& {
      reify();
      return get<value_type>(data);
    }

    rvalue_reference
    operator *() && {
      reify();
      return get<value_type>(move(data));
    }

    explicit
    operator const_reference () const& {
      reify();
      return get<value_type>(data);
    }

  private:

    void
    reify() const {
      if(holds_alternative<thunk_type>(data)){
        lock_guard lock(mex);
        while(holds_alternative<thunk_type>(data)){
          auto temp = get<thunk_type>(data)();
          data = move(temp.data);
        }
      }
    }
  }; // end of class Trampoline

} // end of namespace FunctionUtility::Core


#endif // ! defined TRAMPOLINE_HPP_INCLUDED_1344546961191746609
