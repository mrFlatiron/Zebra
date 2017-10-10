#ifndef TICKET_CONTAINER_H
#define TICKET_CONTAINER_H

#include "ticket_object.h"

class ticket_container
{
private:
  ticket_id m_max_id = 0;
  std::unordered_map<ticket_id, ticket_object> m_tickets;
public:
  ticket_container ();
  ~ticket_container ();

  const ticket_object &ticket (const ticket_id id) const;

  ticket_id add_ticket (const ticket_object &obj);
};

#endif // TICKET_CONTAINER_H
