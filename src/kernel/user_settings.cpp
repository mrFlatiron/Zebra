#include "user_settings.h"

#include "common/work/work.h"

user_settings::user_settings ()
{
  m_conn.connect_to (m_tickets.ticket_deleted,
                     [this] (ticket_id id)
  {this->m_columns.notify_ticket_deleted (id);});
}


ticket_container &user_settings::tickets ()
{
  return m_tickets;
}

const ticket_container &user_settings::tickets () const
{
  return m_tickets;
}

columns_handler &user_settings::columns ()
{
  return m_columns;
}

const columns_handler &user_settings::columns () const
{
  return m_columns;
}

bool user_settings::worker_process (work::xml_worker &worker)
{
  work::process (worker, m_tickets, "tickets");
  work::process (worker, m_columns, "columns_handler");
  return worker.is_ok ();
}
