#ifndef TICKET_PTR_GENERIC_H
#define TICKET_PTR_GENERIC_H

//DONT USE THIS HEADER DIRECTLY. INCLUDE ticket_ptr.h instead

#include "sig/sigslots.h"
#include "ticket_object.h"
#include "ticket_container.h"

template<typename T, typename Container>
class ticket_ptr_generic
{
private:
  T m_data;
  mutable bool m_is_uptodate = true;

  Container m_container;

  sig::connector m_conn;
public:
  ticket_ptr_generic (Container container = nullptr, T data = nullptr)
  {
    m_data = data;
    m_container = container;

    if (m_data)
      make_connections ();
  }

  ~ticket_ptr_generic () {}

  ticket_ptr_generic (const ticket_ptr_generic<T, Container> &ptr)
  {
    m_data = ptr.m_data;
    m_container = ptr.m_container;
    m_is_uptodate = ptr.m_is_uptodate;
    m_conn = ptr.m_conn;

    if (m_data)
      make_connections ();
  }

  ticket_ptr_generic (ticket_ptr_generic<T, Container> &&ptr)
  {
    m_data = ptr.m_data;
    m_container = ptr.m_container;
    ptr.m_data = nullptr;
    ptr.m_container = nullptr;
    m_conn = std::move (ptr.m_conn);
    m_is_uptodate = ptr.m_is_uptodate;

    if (m_data)
      make_connections ();
  }

  ticket_ptr_generic &operator = (const ticket_ptr_generic<T, Container> &ptr)
  {
    m_data = ptr.m_data;
    m_container = ptr.m_container;
    m_is_uptodate = ptr.m_is_uptodate;
    m_conn = ptr.m_conn;

    if (m_data)
      make_connections ();

    return *this;
  }

  ticket_ptr_generic &operator = (ticket_ptr_generic<T, Container> &&ptr)
  {
    m_data = ptr.m_data;
    m_container = ptr.m_container;
    ptr.m_data = nullptr;
    ptr.m_container = nullptr;
    m_conn = std::move (ptr.m_conn);
    m_is_uptodate = ptr.m_is_uptodate;

    if (m_data)
      make_connections ();

    return *this;
  }

  template<typename S, typename C>
  void copy_state (const ticket_ptr_generic<S, C> &t)
  {
    m_is_uptodate = !t.is_dirty ();
  }


  T get () const {return m_data;}
  Container container () const {return m_container;}

  bool is_valid () const {return m_data != nullptr && m_container != nullptr;}
  bool is_dirty () const {return !m_is_uptodate;}

  void erase () {if (!m_container) {DEBUG_PAUSE ("Shouldn't happen"); return;} m_container->erase (m_data->id ());}
private:
  void set_dirty () const    {m_is_uptodate = false;}
  void set_deleted ()        {m_data = nullptr;}
  void set_uptodate () const {m_is_uptodate = true;}

  void make_connections ()
  {
    m_conn.connect_to (m_data->data_changed, [this] () {this->set_dirty ();});
    m_conn.connect_to (m_data->ticket_deleted, [this] () {this->set_deleted ();});
  }
};


#endif // TICKET_PTR_GENERIC_H
