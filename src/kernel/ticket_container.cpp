#include "ticket_container.h"

ticket_container::ticket_container ()
{

}

ticket_container::~ticket_container ()
{

}

ticket_ptr ticket_container::ticket (const ticket_id id) const
{
  auto it = m_tickets.find (id);
  if (it ==)
}

ticket_id ticket_container::add_ticket (const ticket_object &obj)
{
  m_max_id++;
  m_tickets.insert (std::pair<int, ticket_object> (m_max_id, obj));
  return m_max_id;
}
