#include "project_handler.h"

project_handler::project_handler()
{
  m_conn.connect_to (m_tickets.ticket_deleted,
                     [this] (ticket_id id)
  {this->m_columns.notify_ticket_deleted (id);});
}

ticket_container &project_handler::tickets ()
{
  return m_tickets;
}

const ticket_container &project_handler::tickets () const
{
  return m_tickets;
}

columns_handler &project_handler::columns ()
{
  return m_columns;
}

const columns_handler &project_handler::columns () const
{
  return m_columns;
}
