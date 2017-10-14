#ifndef COLUMN_DISPLAY_PROXY_H
#define COLUMN_DISPLAY_PROXY_H

#include "column_display_proxy_abstract.h"

class ticket_container;
class columns_handler;

class column_display_proxy : public column_display_proxy_abstract
{
private:
  column_id m_id;
  const columns_handler &m_columns;
public:
  column_display_proxy (const columns_handler &columns, column_id id);
  ~column_display_proxy ();

  std::vector<column_id> get_shown_indices ();

  void set_col_id (column_id id);
  column_id col_id () const;
};

#endif // COLUMN_DISPLAY_PROXY_H
