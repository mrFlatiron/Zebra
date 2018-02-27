#ifndef PROJECT_HANDLER_H
#define PROJECT_HANDLER_H

#include "ticket_container.h"
#include "columns_handler.h"
namespace work {class xml_worker;}

class project_handler
{
private:
  ticket_container m_tickets;
  columns_handler m_columns;

  sig::connector m_conn;
public:
  project_handler ();
  ~project_handler ();

  ticket_container &tickets ();
  const ticket_container &tickets () const;

  columns_handler &columns ();
  const columns_handler &columns () const;

  bool worker_process (work::xml_worker &worker);
};

#endif // PROJECT_HANDLER_H
