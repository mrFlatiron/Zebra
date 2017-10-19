#include "column_display_proxy.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"

column_display_proxy::column_display_proxy (column_info &column)
  : m_column (column)
{
  m_conn.connect_to (m_column.ticket_removed_from_column, [this] (ticket_id)
  {this->layout_changed ();});
  m_conn.connect_to (m_column.ticket_added_to_column, [this] (ticket_id)
  {this->layout_changed ();});
}

std::vector<ticket_id> column_display_proxy::get_shown_indices ()
{
  auto tickets = m_column.tickets ();
  std::sort (tickets.begin (), tickets.end (), [this] (auto l, auto r) -> bool {
      return m_column.ticket_internal_id (l) < m_column.ticket_internal_id (r);
    });
  return tickets;
}

column_id column_display_proxy::col_id () const
{
  return m_column.id ();
}
