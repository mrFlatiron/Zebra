#ifndef COLUMNS_HANDLER_H
#define COLUMNS_HANDLER_H

#include "column_info.h"


class columns_handler
{
private:
  column_id m_max_id = 0;
  std::unordered_map<column_id, column_info> m_column_to_tickets;
public:
  columns_handler ();
  ~columns_handler ();

  column_id create_column (const QString &name);

  column_info &column (column_id id);
  const column_info &column (column_id id) const;
};

#endif // COLUMNS_HANDLER_H
