#ifndef TICKET_PTR_H
#define TICKET_PTR_H

#include "ticket_ptr_generic.h"

class ticket_ptr;

class const_ticket_ptr : private ticket_ptr_generic<const ticket_object *>
{
private:
  using base = ticket_ptr_generic<const ticket_object *>;
  using self = const_ticket_ptr;
public:
  using base::is_dirty;
  using base::is_valid;
  using base::get;
  using base::copy_state;

  const_ticket_ptr (const ticket_object *data = nullptr)
    : base (data) {}

  const_ticket_ptr (const const_ticket_ptr &rhs)
    : base (rhs) {}

  const_ticket_ptr (const_ticket_ptr &&rhs)
    : base (rhs) {}

  self &operator = (const self &rhs) {base::operator = (rhs); return *this;}
  self &operator = (self &&rhs) {base::operator = (rhs); return *this;}
};

class ticket_ptr : private ticket_ptr_generic<ticket_object *>
{
private:
  using base = ticket_ptr_generic<ticket_object *>;
  using self = ticket_ptr;
public:
  using base::is_dirty;
  using base::is_valid;
  using base::get;
  using base::copy_state;

  ticket_ptr (ticket_object *data = nullptr)
    : base (data) {}

  ticket_ptr (const ticket_ptr &rhs)
    : base (rhs) {}

  ticket_ptr (ticket_ptr &&rhs)
    : base (rhs) {}

  self &operator = (const self &rhs) {base::operator = (rhs); return *this;}
  self &operator = (self &&rhs) {base::operator = (rhs); return *this;}

  operator const_ticket_ptr ()
  {
    const_ticket_ptr retval (base::get ());
    retval.copy_state (*this);
    return retval;
  }
};


#endif // TICKET_PTR_H
