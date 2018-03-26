#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "ticket_container.h"
#include "columns_handler.h"

class user_settings
{
private:
  ticket_container m_tickets;
  columns_handler m_columns;

  sig::connector m_conn;

public:
  user_settings ();
  ~user_settings () = default;

  ticket_container &tickets ();
  const ticket_container &tickets () const;

  columns_handler &columns ();
  const columns_handler &columns () const;

  bool worker_process (work::xml_worker &worker);
};

#endif // USER_SETTINGS_H
