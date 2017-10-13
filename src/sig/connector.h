#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "sigsignal.h"
#include "common/template_utils.h"

namespace sig
{

  class signal_base;

  class connector
  {
  private:
    std::unordered_set<signal_base *> m_signals;
  public:
    connector ();
    ~connector ();

    void remove_signal (signal_base *ptr);

    template<typename Func, typename... Args>
    void connect_to (signal<Args...> &s, Func f)
    {
      auto s_ptr = &s;
      if (m_signals.find (s_ptr) == m_signals.end ())
        m_signals.insert (static_cast<signal_base *> (&s));

      s.add_slot (this, std::function<void (Args&&...)> (templ::call_helper<Func> (f)));
    }
    template<typename T, typename Func, typename... Args>
    void connect_to (signal<Args> &s, binded_func<T, Func> &&f)
    {

    }
  };
}
#endif // CONNECTOR_H
