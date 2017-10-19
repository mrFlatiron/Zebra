#ifndef MW_COLUMNS_DISPLAY_PROXY_ABSTRACT_H
#define MW_COLUMNS_DISPLAY_PROXY_ABSTRACT_H

#include "sig/sigslots.h"
#include "kernel/ticket_typedefs.h"

class mw_columns_display_proxy_abstract
{
private:

public:
  mw_columns_display_proxy_abstract ();
  virtual ~mw_columns_display_proxy_abstract ();

  virtual std::vector<column_id> get_shown_indices () = 0;

  sig::signal<> data_changed;
  sig::signal<> layout_changed;
};

#endif // MW_COLUMNS_DISPLAY_PROXY_ABSTRACT_H
