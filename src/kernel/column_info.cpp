#include "column_info.h"

column_info::column_info ()
{

}

column_id column_info::id () const
{
  return m_id;
}

void column_info::set_id (column_id id)
{
  m_id = id;
}

std::vector<ticket_id> column_info::tickets () const
{
  std::vector<ticket_id> retval;
  for (auto &p : m_ticket_ids)
    retval.push_back (p.first);
  return retval;
}

void column_info::add_ticket (ticket_id id)
{
  m_max_entry_id++;

  auto it = m_ticket_ids.find (id);
  if (it != m_ticket_ids.end ())
    {
      DEBUG_PAUSE ("Already in this column");
      return;
    }
  m_ticket_ids.insert (std::make_pair (id, m_max_entry_id));
  ticket_added_to_column (id);
}

void column_info::remove_ticket (ticket_id id)
{
  auto it = m_ticket_ids.find (id);
  if (it == m_ticket_ids.end ())
    {
      DEBUG_PAUSE ("Not in this column");
      return;
    }
  m_ticket_ids.erase (it);
  ticket_removed_from_column (id);
}

QString column_info::name () const
{
  return m_name;
}

void column_info::set_name (const QString &str)
{
  m_name = str;
}

bool column_info::try_remove_ticket (ticket_id tid)
{
  auto it = m_ticket_ids.find (tid);
  if (it != m_ticket_ids.end ())
    {
      m_ticket_ids.erase (it);
      ticket_removed_from_column (tid);
      return true;
    }
  return false;
}

ticket_col_id column_info::ticket_internal_id (ticket_id id) const
{
  return m_ticket_ids.at (id);
}
