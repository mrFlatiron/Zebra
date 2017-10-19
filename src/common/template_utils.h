#ifndef TEMPLATE_UTILS_H
#define TEMPLATE_UTILS_H

namespace templ
{
  template<typename Func, typename Tuple, size_t... I>
  auto try_call (Func &&f, Tuple && t, std::index_sequence<I...>) -> decltype (f (std::get<I> (t)...));

  template<typename Func, typename Tuple, size_t N, typename = void>
  struct arguments_needed
  {
    static constexpr size_t value = arguments_needed<Func, Tuple, N - 1>::value;
  };

  template<typename Func, typename Tuple, size_t N>
  struct arguments_needed<Func, Tuple, N, decltype (try_call (std::declval<Func> (),
                                                              std::declval<Tuple> (),
                                                              std::make_index_sequence<N> {}))>
  {
    static constexpr size_t value = N;
  };



  template<typename Func, typename Tuple, size_t... I>
  void call_final (Func &f, Tuple &&tup, std::index_sequence<I...>)
  {
    f (std::get<I> (tup)...);
  }

  template<typename Func>
  struct call_helper
  {
    Func func;
    call_helper (const Func &f)
      : func (f) {}

    template<typename...Args>
    void operator () (Args &&... args) const
    {
      constexpr size_t N = arguments_needed<Func, std::tuple<Args...>, sizeof... (Args)>::value;
      call_final (func, std::forward_as_tuple (std::forward<Args> (args)...), std::make_index_sequence<N> {});
    }

  };
}

#endif // TEMPLATE_UTILS_H
