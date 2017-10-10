#include "columns_handler.h"

columns_handler::columns_handler ()
{

}

columns_handler::~columns_handler ()
{

}

column_id columns_handler::create_column (const QString &name)
{
  m_max_id++;

  column_info column;
  column.set_name (name);

  m_column_to_tickets.insert (std::make_pair (m_max_id, std::move (column)));
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