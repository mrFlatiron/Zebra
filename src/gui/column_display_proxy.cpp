#include "column_display_proxy.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"

column_display_proxy::column_display_proxy (const columns_handler &columns, column_id id)
  : m_id (id),
    m_columns (columns)
{

}

column_display_proxy::~column_display_proxy ()
{

}

std::vector<column_id> column_display_proxy::get_shown_indices ()
{
  return m_columns.column (m_id).tickets ();
}

void column_display_proxy::set_col_id (column_id id)
{
  m_id = id;
}

column_id column_display_proxy::col_id () const
{
  return m_id;
}
