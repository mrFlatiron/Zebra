#include "ticket_container.h"
#include "ticket_ptr.h"

ticket_container::ticket_container ()
{

}

const_ticket_ptr ticket_container::ticket (ticket_id id) const
{
  auto it = m_tickets.find (id);
  if (it == m_tickets.end ())
    {
      return const_ticket_ptr (this);
    }
  return const_ticket_ptr (this, &(it->second));
}

ticket_ptr ticket_container::ticket (const ticket_id id)
{
  auto it = m_tickets.find (id);
  if (it == m_tickets.end ())
    {
      return ticket_ptr (this);
    }
  else
    return ticket_ptr (this, &(it->second));
}

ticket_id ticket_container::add_ticket (ticket_object &&obj)
{
  m_max_id++;
  obj.set_id (m_max_id);
  m_tickets.insert (std::pair<ticket_id, ticket_object> (m_max_id, obj));
  return m_max_id;
}

std::vector<ticket_id> ticket_container::all_ids () const
{
  std::vector<ticket_id> retval;
  for (auto &p : m_tickets)
    retval.push_back (p.first);
  return retval;
}

void ticket_container::erase (ticket_id id)
{
  auto it = m_tickets.find (id);
  if (it == m_tickets.end ())
    {
      DEBUG_PAUSE ("No such ticket");
      return;
    }
  m_tickets.erase (it);

  ticket_deleted (std::move (id));
}
