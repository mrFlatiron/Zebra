#ifndef SIGSIGNAL_H
#define SIGSIGNAL_H

#include "signal_base.h"
#include "signal_deferred.h"

namespace sig
{
  template<typename... Args>
  class signal : public signal_base
  {
  private:
    mutable slots_vector<Args...> m_slots;
    static signal_deferred<Args...> m_deferred;

  public:
    signal ()
    {
      m_deferred.add_new (this);
    }
    ~signal ()
    {
      apply_deferred ();
    }

    signal (const signal &s)
      : signal_base (s)
    {
      m_deferred.add_new (this);
    }

    signal (signal &&s)
      : signal_base (std::move (s))
    {
      s.apply_deferred ();
      s.disconnect_all ();
      m_slots = std::move (s.m_slots);
      m_deferred.add_new (this);
    }

    signal &operator = (const signal &s)
    {
      return *this;
    }

    signal &operator = (signal &&s)
    {
      s.apply_deferred ();
      s.disconnect_all ();
      return *this;
    }

    void add_slot (connector *c, std::function<void (Args &&...)> slot) const
    {
      m_deferred.get_deferred (this)->add_slot (c, slot);
    }

    void remove_connect (connector *conn) const override
    {
      m_deferred.get_deferred (this)->remove_connect (conn);
    }

    void apply_deferred () const
    {
      auto deferred = m_deferred.get_deferred (this);

      auto deleted = deferred->deleted_connectors ();

      for (auto c : deleted)
        remove_connect_actual (c);

      auto &added = deferred->added_slots ();

      for (auto &p : added)
        add_slot_actual (p.first, p.second);

      deferred->clear ();
    }

    template<typename... SignalArgs>
    void operator () (SignalArgs &&... args) const
    {
      apply_deferred ();
      auto slots_copy = m_slots;
      for (auto &f : slots_copy)
        {
          if (m_deferred.get_deferred (this)->is_conn_deleted (f.first))
            continue;

          f.second (std::forward<SignalArgs> (args)...);
        }
    }

  private:
    void remove_connect_actual (connector *c) const
    {
      signal_base::remove_connect (c);
      m_slots.erase
          (std::remove_if
           (m_slots.begin (), m_slots.end (),
            [&] (const auto &p) -> bool {return p.first == c;}),
           m_slots.end ());
    }
    void add_slot_actual (connector *c, std::function<void (Args &&...)> slot) const
    {
      signal_base::add_connect (c);
      m_slots.push_back (std::make_pair (c, slot));
    }
  };

  template<typename... Args>
  signal_deferred<Args...> signal<Args...>::m_deferred;
}
#endif // SIGSIGNAL_H
