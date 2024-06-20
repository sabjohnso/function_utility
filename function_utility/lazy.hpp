#pragma  once

//
// ... function utility header files
//
#include <function_utility/import.hpp>

namespace FunctionUtility::Core{

  template<typename T>
  concept Thunk = requires(const T& const_thunk, T& mutable_thunk){
    const_thunk(); mutable_thunk();
  };

  template<Thunk Th>
  struct Lazy_Expr {
    using Thunk_Type = Th;
    using Value_Type = invoke_result_t<Th>;

    Lazy_Expr() = delete;

    template<class T>
    explicit Lazy_Expr(T&& thunk)
      : pkernel{make_shared<Kernel>(thunk)}
    {}

    const Value_Type&
    value() const {
      return pkernel->value();
    }

  private:

    struct Kernel {

      Kernel(Kernel&& input)
        : thunk(std::move(input.thunk))
      {}

      template<class T>
      Kernel(T&& thunk) :
        thunk(std::forward<T>(thunk))
      {}

      const Value_Type& value() const {
        if(! ptr){
          reify_value();
        }
        return *ptr;
      }

    private:

      void reify_value() const {
        lock_guard lock{mex};
        if(! ptr){
          ptr = make_unique<Value_Type>(thunk());
        }
      }

      Thunk_Type thunk;
      mutable unique_ptr<Value_Type> ptr{};
      mutable mutex mex{};
    };
    using Kernel_Pointer = shared_ptr<Kernel>;

    Kernel_Pointer pkernel;

  };

  template<Thunk Th>
  constexpr auto
  lazy(Th&& thunk){
    return Lazy_Expr<std::remove_cvref_t<Th>>{std::forward<Th>(thunk)};
  }



} // end of namespace FunctionUtility::Core
