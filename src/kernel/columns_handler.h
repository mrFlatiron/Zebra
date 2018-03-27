#ifndef COLUMNS_HANDLER_H
#define COLUMNS_HANDLER_H

#include "column_info.h"

namespace work {class xml_worker;}

class columns_handler
{
private:
  column_id m_max_id;
  std::unordered_map<column_id, column_info> m_column_to_tickets;
public:
  columns_handler ();

  column_id create_column (const QString &name);

  void delete_column (column_id id);

  column_info &column (column_id id);
  const column_info &column (column_id id) const;

  std::vector<column_id> all_ids () const;
  int size ();

  void notify_ticket_deleted (ticket_id tid);

  void transfer_ticket (ticket_id tid, column_id from, column_id to);


  sig::signal<ticket_id, column_id/*from*/, column_id/*to*/> ticket_transfered;
  sig::signal<column_id> column_deleted;

  bool worker_process (work::xml_worker &worker);
};

#endif // COLUMNS_HANDLER_H
