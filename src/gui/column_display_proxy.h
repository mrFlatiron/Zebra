#ifndef COLUMN_DISPLAY_PROXY_H
#define COLUMN_DISPLAY_PROXY_H

#include "gui/sticker_display_proxy_abstract.h"

class ticket_container;
class columns_handler;

class column_display_proxy : public sticker_display_proxy_abstract<column_id>
{
private:
  column_id m_id;
  const columns_handler &m_columns;
  const ticket_container &m_tickets;
public:
  column_display_proxy (const columns_handler &columns, const ticket_container &tickets);
  ~column_display_proxy ();
};

#endif // COLUMN_DISPLAY_PROXY_H
