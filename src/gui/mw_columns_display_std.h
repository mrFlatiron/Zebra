#ifndef MW_COLUMNS_DISPLAY_STD_H
#define MW_COLUMNS_DISPLAY_STD_H

#include "mw_columns_display_proxy_abstract.h"

class columns_handler;

class mw_columns_display_std : public mw_columns_display_proxy_abstract
{
private:
  columns_handler &m_columns;

  sig::connector m_conn;
public:
  mw_columns_display_std (columns_handler &columns);
  ~mw_columns_display_std ();

  std::vector<column_id> get_shown_indices () override;

};

#endif // MW_COLUMNS_DISPLAY_STD_H
