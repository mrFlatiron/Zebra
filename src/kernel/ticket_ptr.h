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

  ticket_object *get ();

  bool is_valid () const;
  bool is_dirty () const;
private:
  void set_dirty ();
  void set_deleted ();
  void set_uptodate ();
};


#endif // TICKET_PTR_H
