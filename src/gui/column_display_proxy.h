#ifndef COLUMN_DISPLAY_PROXY_H
#define COLUMN_DISPLAY_PROXY_H

#include "column_display_proxy_abstract.h"

class ticket_container;
class columns_handler;
class column_info;

class column_display_proxy : public column_display_proxy_abstract
{
private:
  column_info &m_column;

  sig::connector m_conn;
public:
  column_display_proxy (column_info &column);

  std::vector<ticket_id> get_shown_indices ();

  column_id col_id () const;
};

#endif // COLUMN_DISPLAY_PROXY_H
