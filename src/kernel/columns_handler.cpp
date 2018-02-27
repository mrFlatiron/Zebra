#include "columns_handler.h"
#include "common/work/work.h"

columns_handler::columns_handler ()
{

}

column_id columns_handler::create_column (const QString &name)
{
  m_max_id++;

  column_info column;
  column.set_name (name);
  column.set_id (m_max_id);

  m_column_to_tickets.insert (std::make_pair (m_max_id, column));
  return m_max_id;
}

column_info &columns_handler::column (column_id id)
{
  return m_column_to_tickets[id];
}

const column_info &columns_handler::column (column_id id) const
{
  return m_column_to_tickets.at (id);
}

std::vector<column_id> columns_handler::all_ids () const
{
  std::vector<column_id> retval;

  for (auto &p : m_column_to_tickets)
    retval.push_back (p.first);

  return retval;
}

int columns_handler::size ()
{
  return isize (m_column_to_tickets);
}

void columns_handler::notify_ticket_deleted (ticket_id tid)
{
  for (auto &p : m_column_to_tickets)
    {
      p.second.try_remove_ticket (tid);
    }
}

void columns_handler::transfer_ticket (ticket_id tid, column_id from, column_id to)
{
  m_column_to_tickets[from].remove_ticket (tid);
  m_column_to_tickets[to].add_ticket (tid);
  ticket_transfered (tid, from, to);
}

bool columns_handler::worker_process (work::xml_worker &worker)
{
  work::process (worker, m_max_id, "max_id");
  work::process (worker, m_column_to_tickets, "column_to_tickets");
  return worker.is_ok ();
}
