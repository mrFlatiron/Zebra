#ifndef INDEXED_EMPLACER_H
#define INDEXED_EMPLACER_H

template<typename index_t, typename T>
class indexed_emplacer
{
private:
  std::unordered_map<index_t, std::unique_ptr<T>> m_vals;
//  std::unordered_set<index_t> m_old_ids;
  std::vector<index_t> m_cur_ids;
public:
  indexed_emplacer () {};
  ~indexed_emplacer () {};

  void set_new_ids (const std::vector<index_t> &new_ids)
  {
//    for (auto id : m_cur_ids)
//      m_old_ids.insert (id);

    m_cur_ids = new_ids;

//    auto remove_condition = [this] (auto &it) -> bool
//    {
//        return std::find (m_cur_ids.begin (), m_cur_ids.end (), it->first) == m_cur_ids.end ();
//    };

//    auto it = m_vals.begin ();
//    while (it != m_vals.end ())
//    {
//      if (remove_condition (it))
//        it = m_vals.erase (it);
//      else
//        it++;
//    }

  }

  std::vector<index_t> values_that_need_construction () const
  {
    std::vector<index_t> retval;
    for (auto id : m_cur_ids)
      {
        auto it = m_vals.find (id);
        if (it == m_vals.end ())
          retval.push_back (id);
        else
          {
            if (!it->second)
              retval.push_back (id);
          }
      }
    return retval;
  }

  template<typename... Args>
  void emplace (index_t id, Args &&... args)
  {
    m_vals[id].reset (new T (std::forward<Args> (args)...));
  }



  std::vector<T *> values () const
  {
    std::vector<T *> retval;
    for (auto id : m_cur_ids)
      {
        retval.push_back (m_vals.at (id).get ());
      }
    return retval;
  }

  std::vector<T *> unused_values () const
  {
    std::vector<T *> retval;

    auto condition = [this] (auto &p) -> bool
    {
        return std::find (m_cur_ids.begin (), m_cur_ids.end (), p.first) == m_cur_ids.end ();
      };

    for (auto &p : m_vals)
      {
        if (condition (p))
          retval.push_back (p.second.get ());
      }
    return retval;
  }

  T * operator[] (index_t id) const
  {
    return m_vals.at (id).get ();
  }

  size_t size () const
  {
    return m_cur_ids.size ();
  }

  const std::vector<index_t> &current_indices_ref ()
  {
    return m_cur_ids;
  }
};

#endif // INDEXED_EMPLACER_H
