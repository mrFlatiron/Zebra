#ifndef TICKET_PTR_H
#define TICKET_PTR_H

#include "kernel/ticket_typedefs.h"
#include "sig/sigslots.h"

class ticket_object;

class ticket_ptr
{
private:
  ticket_object *m_data = nullptr;
  mutable bool m_changed = false;
  sig::connector m_conn;
public:
  ~ticket_ptr ();

  ticket_ptr (ticket_object *data = nullptr);

  ticket_ptr (const ticket_ptr &ptr);
  ticket_ptr (ticket_ptr &&ptr);

  ticket_ptr &operator = (const ticket_ptr &ptr);
  ticket_ptr &operator = (ticket_ptr &&ptr);


  ticket_object *get ();
  const ticket_object *get () const;

  bool is_valid () const;
  bool is_dirty () const;

  sig::signal<> ticket_changed; //do you really want to know this? prefer lazy calculations.
  sig::signal<> ticket_deleted; //the same comment
private:
  void set_dirty () const;
  void set_deleted ();
  void set_uptodate () const;
  void make_connections ();
};


#endif // TICKET_PTR_H
