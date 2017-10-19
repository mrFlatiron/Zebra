#include "ticket_object.h"

ticket_object::ticket_object ()
{

}

ticket_object::~ticket_object ()
{
  if (m_id != 0)
    ticket_deleted ();
}

void ticket_object::set_id (ticket_id id)
{
  m_id = id;
}

void ticket_object::set_title (const QString &str)
{
  m_title = str;
  data_changed ();
}

void ticket_object::set_description (const QString &str)
{
  m_description = str;
  data_changed ();
}

void ticket_object::set_type (ticket_type t)
{
  m_type = t;
  data_changed ();
}

void ticket_object::set_priority (ticket_priority p)
{
  m_priority = p;
  data_changed ();
}

ticket_id ticket_object::id () const
{
  return m_id;
}

QString ticket_object::title () const
{
  return m_title;
}

QString ticket_object::description () const
{
  return m_description;
}

ticket_type ticket_object::type () const
{
  return m_type;
}

ticket_priority ticket_object::priority () const
{
  return m_priority;
}
