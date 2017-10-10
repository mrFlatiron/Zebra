#ifndef TICKET_OBJECT_H
#define TICKET_OBJECT_H

#include "sig/sigslots.h"
#include "ticket_typedefs.h"

class ticket_object
{
private:
  ticket_id m_id;
  QString m_title;
  QString m_description;
  ticket_type m_type;
  ticket_priority m_priority;
public:
  ticket_object ();
  ~ticket_object ();

  void set_title (const QString &str);
  void set_description (const QString &str);
  void set_type (ticket_type t);
  void set_priority (ticket_priority p);

  QString title () const;
  QString description () const;
  ticket_type type () const;
  ticket_priority priority () const;

  sig::signal<> data_changed;
};

#endif // TICKET_OBJECT_H
