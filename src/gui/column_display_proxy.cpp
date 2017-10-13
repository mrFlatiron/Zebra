#include "column_display_proxy.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"

column_display_proxy::column_display_proxy (const columns_handler &columns, const ticket_container &tickets)
  : m_columns (columns),
    m_tickets (tickets)
{

}

column_display_proxy::~column_display_proxy ()
{

}

std::vector<column_id> column_display_proxy::get_shown_indices ()
{
  return m_columns.column (m_id).tickets ();
}
