#ifndef SIGNAL_DEFERRED_H
#define SIGNAL_DEFERRED_H

namespace sig
{
  class signal_base;
  class connector;

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
      m_slots_added.erase
          (std::remove_if
           (m_slots_added.begin (), m_slots_added.end (),
            [this, c] (const auto &p) -> bool
      {
          return p.first == c;
        }), m_slots_added.end ());
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
  class signal_deferred
  {
  private:
    std::unordered_map<const signal_base *, deferred_info<Args...>> m_deferred;
  public:
    signal_deferred () {}
    ~signal_deferred () {}

    deferred_info<Args...> *get_deferred (const signal_base *sig)
    {
      auto it = m_deferred.find (sig);
      if (it == m_deferred.end ())
        return nullptr;
      return &(it->second);
    }

    void add_new (const signal_base * sig)
    {
      m_deferred.emplace (sig, deferred_info<Args...> ());
    }
  };
}
#endif // SIGNAL_DEFERRED_H
