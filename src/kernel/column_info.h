#ifndef COLUMN_INFO_H
#define COLUMN_INFO_H

#include "ticket_typedefs.h"

class column_info
{
private:
  std::unordered_set<ticket_id> m_ticket_ids;
  QString m_name;
public:
  column_info ();
  ~column_info ();

  std::vector<ticket_id> tickets () const;
  void add_ticket (ticket_id id);
  void remove_ticket (ticket_id id);

  QString name () const;
  void set_name (const QString &str);
};

#endif // COLUMN_INFO_H
