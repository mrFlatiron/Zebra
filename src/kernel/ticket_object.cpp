#include "ticket_object.h"

ticket_object::ticket_object ()
{

}

ticket_object::~ticket_object ()
{

}

void ticket_object::set_title (const QString &str)
{
  m_title = str;
}

void ticket_object::set_description (const QString &str)
{
  m_description = str;
}

void ticket_object::set_type (const ticket_type t)
{
  m_type = t;
}

void ticket_object::set_priority (const ticket_priority p)
{
  m_priority = p;
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
