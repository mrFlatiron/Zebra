#ifndef SIGSIGNAL_H
#define SIGSIGNAL_H

#include "signal_base.h"

namespace sig
{

  template<typename... Args>
  struct deferred_info
  {
    std::vector<const connector *> conns_to_add;
    std::vector<std::vector<std::function<void (Args...)>>> slots_to_add;
    std::vector<size_t> deleted_slots;

    void invalidate ()
    {
      conns_to_add.clear ();
      slots_to_add.clear ();
      deleted_slots.clear ();
    }
  };

  template<typename... Args>
  class signal : public signal_base
  {
  private:
    mutable std::vector<std::vector<std::function<void (Args...)>>> m_slots;
    mutable bool m_is_emitting = false;
    mutable std::vector<int> m_count_to_execute;
    mutable deferred_info m_deferred;
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

      if (!m_is_emitting)
        {
          int pos = signal_base::add_pos (c);
          if (pos == isize (m_slots))
            {
              m_slots.push_back ({slot});
              m_count_to_execute.push_back (1);
            }
          else
            {
              m_slots[pos].push_back (slot);
              m_count_to_execute[pos]++;
            }
        }
      else
        {

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
