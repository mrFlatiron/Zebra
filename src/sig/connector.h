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
    mutable std::unordered_set<const signal_base *> m_signals;
  public:
    connector ();
    ~connector ();

    connector (const connector  &);
    connector (connector &&c);

    connector &operator = (const connector &);
    connector &operator =(connector &&c);

    void remove_signal (const signal_base *ptr) const;

    template<typename Func, typename... Args>
    void connect_to (const signal<Args...> &s, Func f)
    {
      auto s_ptr = &s;
      if (m_signals.find (s_ptr) == m_signals.end ())
        m_signals.insert (static_cast<const signal_base *> (&s));

      s.add_slot (this, std::function<void (Args&&...)> (templ::call_helper<Func> (std::move (f))));
    }
    void disconnect_all ();
  };
}
#endif // CONNECTOR_H
