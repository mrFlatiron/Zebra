#include <QApplication>

#include "gui/main_window.h"
#include "kernel/project_handler.h"

template<typename... Args>
class check
{

};

template<typename Func, typename Tuple, size_t... Indices>
auto try_call_impl (Func &f, Tuple &&tup, std::index_sequence<Indices...>) -> decltype (f (std::get<Indices> (tup)...))
{
  f ((std::get<Indices> (tup))...);
}

template<typename Func, typename Tuple, size_t... Indices>
void try_call_impl (Func &f, Tuple &&tup, std::index_sequence<Indices...>, ...)
{
  try_call_impl (f, std::forward (tup), std::make_index_sequence<std::tuple_size<Tuple>::value - 1> {});
}

template<typename Func, typename... Args>
void try_call (Func &f, Args &&... args)/* -> decltype (try_call_impl (f, std::declval<std::tuple<Args...> ()))*/
{
  try_call_impl (f, std::make_tuple (std::forward<Args> (args)...), std::make_index_sequence<sizeof... (Args)> {});
}

template<typename Func, typename... Args>
struct call_helper
{
  Func &func;
  call_helper (Func &f)
    : func (f) {}
  ~call_helper () {}
  void operator () (Args &&... args)
  {
    try_call (func, args...);
  }
};





template<typename Func, typename... Args>
std::function<void(Args...)> get_function (check<Args...> &c, Func &f) {return std::function<void(Args...)> (call_helper<Func, Args...> (f));}



void go (const int i, const int j) {return;}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  project_handler proj;

  main_window w;
  w.show();

  check<int, int> s;

  auto super = get_function (s, go);

  super (2, 3);

  return a.exec();
}
