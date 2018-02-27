#ifndef TICKET_CONTAINER_H
#define TICKET_CONTAINER_H

#include "ticket_object.h"

class ticket_ptr;
class const_ticket_ptr;
namespace work {class xml_worker;}


class ticket_container
{
private:
  ticket_id m_max_id;
  std::unordered_map<ticket_id, ticket_object> m_tickets;
public:
  ticket_container ();

  ticket_ptr ticket (ticket_id id);

  const_ticket_ptr ticket (ticket_id id) const;

  ticket_id add_ticket (ticket_object &&obj);

  std::vector<ticket_id> all_ids () const;

  void erase (ticket_id id);

  bool worker_process (work::xml_worker &worker);

  sig::signal<ticket_id> ticket_deleted;
  sig::signal<ticket_id> ticket_added;
};

#endif // TICKET_CONTAINER_H
