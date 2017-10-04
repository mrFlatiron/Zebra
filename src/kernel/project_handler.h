#ifndef PROJECT_HANDLER_H
#define PROJECT_HANDLER_H

#include "ticket_container.h"

class project_handler
{
private:
  ticket_container m_tickets;
public:
  project_handler ();
  ~project_handler ();

  ticket_container &tickets ();
  const ticket_container &tickets () const;
};

#endif // PROJECT_HANDLER_H
