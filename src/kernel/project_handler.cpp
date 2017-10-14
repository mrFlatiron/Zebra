#include "project_handler.h"

project_handler::project_handler()
{

}

project_handler::~project_handler ()
{

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
