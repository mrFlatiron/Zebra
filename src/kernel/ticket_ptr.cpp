#include "ticket_ptr.h"
#include "ticket_object.h"

ticket_ptr::ticket_ptr (ticket_object *data)
{
  m_data = data;
  if (!m_data)
    return;

  make_connections ();
}

ticket_ptr::ticket_ptr(const ticket_ptr &ptr)
{
  m_data = ptr.m_data;
  m_changed = ptr.m_changed;
  m_conn = ptr.m_conn;
  make_connections ();
}

ticket_ptr::ticket_ptr (ticket_ptr &&ptr)
{
  m_data = ptr.m_data;
  ptr.m_data = nullptr;
  m_changed = ptr.m_changed;
  m_conn = std::move (ptr.m_conn);
  make_connections ();
}

ticket_ptr &ticket_ptr::operator =(const ticket_ptr &ptr)
{
  m_data = ptr.m_data;
  m_changed = ptr.m_changed;
  m_conn = ptr.m_conn;
  make_connections ();
  return *this;
}

ticket_ptr &ticket_ptr::operator =(ticket_ptr &&ptr)
{
  m_data = ptr.m_data;
  ptr.m_data = nullptr;
  m_changed = ptr.m_changed;
  m_conn = std::move (ptr.m_conn);
  make_connections ();
  return *this;
}

ticket_object *ticket_ptr::get ()
{
  set_uptodate ();

  return m_data;
}

const ticket_object *ticket_ptr::get () const
{
  set_uptodate ();

  return m_data;
}

bool ticket_ptr::is_valid () const
{
  return m_data != nullptr;
}

bool ticket_ptr::is_dirty () const
{
  return m_changed;
}

void ticket_ptr::set_dirty () const
{
  m_changed = true;
}

void ticket_ptr::set_deleted ()
{
  m_data = nullptr;
  set_dirty ();
}

void ticket_ptr::set_uptodate() const
{
  m_changed = false;
}

void ticket_ptr::make_connections ()
{
  m_conn.connect_to (m_data->data_changed, [this] () {this->set_dirty ();});
  m_conn.connect_to (m_data->ticket_deleted, [this] () {this->set_deleted ();});
  m_conn.connect_to (m_data->data_changed, [this] () {this->ticket_changed ();});
  m_conn.connect_to (m_data->ticket_deleted, [this] () {this->ticket_deleted ();});
}

ticket_ptr::~ticket_ptr ()
{

}

