#include "column_info.h"

column_info::column_info ()
{

}

column_info::~column_info ()
{

}

std::vector<ticket_id> column_info::tickets () const
{
  return {m_ticket_ids.begin (), m_ticket_ids.end ()};
}

void column_info::add_ticket (ticket_id id)
{
  auto it = m_ticket_ids.find (id);
  if (it != m_ticket_ids.end ())
    {
      DEBUG_PAUSE ("Already in this column");
      return;
    }
  m_ticket_ids.insert (id);
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
}

QString column_info::name () const
{
  return m_name;
}

void column_info::set_name (const QString &str)
{
  m_name = str;
}
