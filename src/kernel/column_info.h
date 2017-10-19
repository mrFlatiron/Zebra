#ifndef COLUMN_INFO_H
#define COLUMN_INFO_H

#include "ticket_typedefs.h"

#include "sig/sigslots.h"

class column_info
{
private:
  column_id m_id;
  ticket_col_id m_max_entry_id;
  std::unordered_map<ticket_id, ticket_col_id> m_ticket_ids;
  QString m_name;

  sig::connector m_conn;
public:
  column_info ();

  column_id id () const;
  void set_id (column_id id);

  std::vector<ticket_id> tickets () const;
  void add_ticket (ticket_id id);
  void remove_ticket (ticket_id id);

  QString name () const;
  void set_name (const QString &str);

  bool try_remove_ticket (ticket_id tid);

  ticket_col_id ticket_internal_id (ticket_id id) const;

  sig::signal<ticket_id> ticket_removed_from_column;
  sig::signal<ticket_id> ticket_added_to_column;
};

#endif // COLUMN_INFO_H
