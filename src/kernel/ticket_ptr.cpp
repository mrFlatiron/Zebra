#include "ticket_ptr.h"
#include "ticket_object.h"

ticket_ptr::ticket_ptr (ticket_object *data)
{
  m_data = data;
  if (!m_data)
    return;

  m_conn.connect_to (m_data->data_changed, [this] () {this->set_dirty});
  m_conn.connect_to (m_data->ticket_deleted, [this] () {this->set_deleted});
}

ticket_object *ticket_ptr::get ()
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

void ticket_ptr::set_dirty ()
{
  m_changed = true;
}

void ticket_ptr::set_deleted ()
{
  m_data = nullptr;
  set_dirty ();
}

void ticket_ptr::set_uptodate()
{
  m_changed = false;
}

ticket_ptr::~ticket_ptr ()
{

}

