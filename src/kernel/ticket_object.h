#ifndef TICKET_OBJECT_H
#define TICKET_OBJECT_H

#include "sig/sigslots.h"
#include "ticket_typedefs.h"
//namespace work {class xml_worker;}

namespace work
{
  class xml_worker;
}

class ticket_object
{
private:
  ticket_id m_id;
  QString m_title = "New Ticket";
  QString m_description = "";
  ticket_type m_type = ticket_type::regular;
  ticket_priority m_priority = ticket_priority::mid;
public:
  ticket_object ();
  ~ticket_object ();

  void set_id (ticket_id id);
  void set_title (const QString &str);
  void set_description (const QString &str);
  void set_type (ticket_type t);
  void set_priority (ticket_priority p);

  ticket_id id () const;
  QString title () const;
  QString description () const;
  ticket_type type () const;
  ticket_priority priority () const;

  bool worker_process (work::xml_worker &worker);

  sig::signal<> data_changed;
  sig::signal<> ticket_deleted;
};

#endif // TICKET_OBJECT_H
