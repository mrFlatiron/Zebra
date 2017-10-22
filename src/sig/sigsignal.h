#ifndef SIGSIGNAL_H
#define SIGSIGNAL_H

#include "signal_base.h"

namespace sig
{

  template<typename... Args>
  class signal : public signal_base
  {
  private:
    mutable std::vector<std::vector<std::function<void (Args...)>>> m_slots;
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
      int pos = signal_base::add_connect (c);
      if (pos == isize (m_slots))
        {
          m_slots.push_back ({slot});
        }
      else
        {
          m_slots[pos].push_back (slot);
        }
    }

    int remove_connect (connector *conn) const
    {
      int pos = signal_base::remove_connect (conn);
      if (pos == isize (m_slots))
        {
          DEBUG_PAUSE ("Shouldn't happen");
        }
      m_slots.erase (m_slots.begin () + pos);
      return pos;
    }

    template<typename... SignalArgs>
    void operator () (SignalArgs &&... args) const
    {
      //TODO: check for disconnection
      int size_conn = isize (m_connectors);
      auto copy_slots = m_slots;
      for (auto i = 0; i < size_conn; i++)
        {
          auto vec = copy_slots[i];
          for (auto &f : vec)
            {
              f (std::forward<SignalArgs> (args)...);
            }
        }
    }
  };
}
#endif // SIGSIGNAL_H
