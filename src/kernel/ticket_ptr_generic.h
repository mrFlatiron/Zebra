#ifndef TICKET_PTR_GENERIC_H
#define TICKET_PTR_GENERIC_H

//DONT USE THIS HEADER DIRECTLY. INCLUDE ticket_ptr.h instead

#include "sig/sigslots.h"
#include "ticket_object.h"

template<typename T>
class ticket_ptr_generic
{
private:
  T m_data;
  mutable bool m_is_uptodate = true;
  sig::connector m_conn;
public:
  ticket_ptr_generic (T data = nullptr)
  {
    m_data = data;

    if (m_data)
      make_connections ();
  }

  ~ticket_ptr_generic () {}

  ticket_ptr_generic (const ticket_ptr_generic<T> &ptr)
  {
    m_data = ptr.m_data;
    m_is_uptodate = ptr.m_is_uptodate;
    m_conn = ptr.m_conn;

    if (m_data)
      make_connections ();
  }

  ticket_ptr_generic (ticket_ptr_generic<T> &&ptr)
  {
    m_data = ptr.m_data;
    ptr.m_data = nullptr;
    m_conn = std::move (ptr.m_conn);
    m_is_uptodate = ptr.m_is_uptodate;

    if (m_data)
      make_connections ();
  }

  ticket_ptr_generic &operator = (const ticket_ptr_generic<T> &ptr)
  {
    m_data = ptr.m_data;
    m_is_uptodate = ptr.m_is_uptodate;
    m_conn = ptr.m_conn;

    if (m_data)
      make_connections ();

    return *this;
  }

  ticket_ptr_generic &operator = (ticket_ptr_generic<T> &&ptr)
  {
    m_data = ptr.m_data;
    ptr.m_data = nullptr;
    m_conn = std::move (ptr.m_conn);
    m_is_uptodate = ptr.m_is_uptodate;

    if (m_data)
      make_connections ();

    return *this;
  }

  template<typename S>
  void copy_state (const ticket_ptr_generic<S> &t)
  {
    m_is_uptodate = !t.is_dirty ();
  }


  T get () const {return m_data;}

  bool is_valid () const {return m_data != nullptr;}
  bool is_dirty () const {return !m_is_uptodate;}

  sig::signal<> ticket_changed; //do you really want to know this? prefer lazy calculations.
  sig::signal<> ticket_deleted; //the same comment
private:
  void set_dirty () const    {m_is_uptodate = false;}
  void set_deleted ()        {m_data = nullptr;}
  void set_uptodate () const {m_is_uptodate = true;}

  void make_connections ()
  {
    m_conn.connect_to (m_data->data_changed, [this] () {this->set_dirty ();});
    m_conn.connect_to (m_data->ticket_deleted, [this] () {this->set_deleted ();});
    m_conn.connect_to (m_data->data_changed, [this] () {this->ticket_changed ();});
    m_conn.connect_to (m_data->ticket_deleted, [this] () {this->ticket_deleted ();});
  }
};


#endif // TICKET_PTR_GENERIC_H
