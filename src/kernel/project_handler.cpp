#include "project_handler.h"
#include "common/work/work.h"

project_handler::project_handler ()
{
  {
    work::xml_worker worker (work::action_t::load, "save_test.xml");
    work::process (worker, *this, "project");
  }

  m_conn.connect_to (m_tickets.ticket_deleted,
                     [this] (ticket_id id)
  {this->m_columns.notify_ticket_deleted (id);});
}

project_handler::~project_handler ()
{
  work::xml_worker worker (work::action_t::save, "save_test.xml");

  work::process (worker, *this, "project");
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

bool project_handler::worker_process (work::xml_worker &worker)
{
  work::process (worker, m_tickets, "tickets");
  work::process (worker, m_columns, "columns");
  return worker.is_ok ();
}
