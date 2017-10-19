#ifndef SIGSIGNAL_H
#define SIGSIGNAL_H

#include "signal_base.h"

namespace sig
{

  template<typename... Args>
  class signal : public signal_base
  {
  private:
    mutable std::unordered_map<const connector *, std::vector<std::function<void (Args...)>>> m_slots;
  public:
    signal () {}
    ~signal () {}

    signal (const signal &s)
      : signal_base (s)
    {

    }

    signal (signal &&s)
      : signal_base (std::move (s))
    {

    }

    signal &operator = (const signal &)
    {
      return *this;
    }

    signal &operator = (signal &&s)
    {
      s.disconnect_all ();
      return *this;
    }

    void add_slot (const connector *c, std::function<void (Args &&...)> slot) const
    {
      bool res = signal_base::add_connect (c);
      if (res)
        {
          m_slots.insert ({c, {slot}});
        }
      else
        {
          (*m_slots.find (c)).second.push_back (slot);
        }
    }

    void remove_connect (connector *conn) const
    {
      signal_base::remove_connect (conn);
      m_slots.erase (m_slots.find (conn));
    }

    template<typename... SignalArgs>
    void operator () (SignalArgs &&... args) const
    {
      for (auto c : m_connectors)
        {
          auto &vec = m_slots.at (c);
          for (auto &f : vec)
            {
              f (std::forward<SignalArgs> (args)...);
            }
        }
    }
  };
}
#endif // SIGSIGNAL_H
