#ifndef SIGSIGNAL_H
#define SIGSIGNAL_H

#include "signal_base.h"

namespace sig
{

  template<typename... Args>
  using slots_vector = std::vector<std::pair<connector *, std::function<void (Args...)>>>;


  template<typename... Args>
  class signal;

  template<typename... Args>
  class deferred_info
  {
  private:
    friend class signal<Args...>;

    slots_vector<Args...> m_slots_added;
    std::unordered_map<connector *, bool> m_conns_deleted;
  public:
    void add_slot (connector *c, std::function<void (Args &&...)> slot)
    {
      m_slots_added.push_back (std::make_pair (c, slot));
      m_conns_deleted[c] = false;
    }
    void remove_connect (connector *c)
    {
      m_conns_deleted[c] = true;
      m_slots_added.erase (std::remove_if (m_slots_added.begin (), m_slots_added.end (), [this] (const auto &p) -> bool {return m_conns_deleted[p.first];}), m_slots_added.end ());
    }
    void clear ()
    {
      m_slots_added.clear ();
      m_conns_deleted.clear ();
    }

    std::set<connector *> deleted_connectors () const
    {
      std::set<connector *> retval;
      for (auto &p : m_conns_deleted)
        if (p.second)
          retval.insert (p.first);
      return retval;
    }

    bool is_conn_deleted (connector *conn) const
    {
      auto it = m_conns_deleted.find (conn);
      if (it == m_conns_deleted.end ())
        return false;

      return it->second;
    }

    const slots_vector<Args...> &added_slots () const
    {
      return m_slots_added;
    }
  };


  template<typename... Args>
  class signal : public signal_base
  {
  private:
    mutable slots_vector<Args...> m_slots;
    mutable bool m_is_emitting = false;
    mutable deferred_info<Args...> m_deferred;


  public:
    signal () {}
    ~signal () { if (m_is_emitting) DEBUG_PAUSE ("Oh-oh");}

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

    void add_slot (connector *c, std::function<void (Args &&...)> slot) const
    {
      if (!m_is_emitting)
        {
          signal_base::add_connect (c);
          m_slots.push_back (std::make_pair (c, slot));
        }
      else
        {
          m_deferred.add_slot (c, slot);
        }
    }

    void remove_connect (connector *conn) const override
    {
      if (!m_is_emitting)
        {
          signal_base::remove_connect (conn);
          m_slots.erase (std::remove_if (m_slots.begin (), m_slots.end (), [&] (const auto &p) -> bool {return p.first == conn;}), m_slots.end ());
        }
      else
        {
          m_deferred.remove_connect (conn);
        }
    }

    void apply_deferred () const
    {
      auto deleted = m_deferred.deleted_connectors ();

      for (auto c : deleted)
        remove_connect (c);

      auto &added = m_deferred.added_slots ();

      for (auto &p : added)
        add_slot (p.first, p.second);

      m_deferred.clear ();
    }

    template<typename... SignalArgs>
    void operator () (SignalArgs &&... args) const
    {
      if (m_is_emitting)
        {
          DEBUG_PAUSE ("Recursive emitting is forbidden");
          return;
        }
      m_is_emitting = true;
      for (auto &f : m_slots)
        {
          if (m_deferred.is_conn_deleted (f.first))
            continue;

          f.second (std::forward<SignalArgs> (args)...);
        }
      m_is_emitting = false;
      apply_deferred ();
    }
  };
}
#endif // SIGSIGNAL_H
