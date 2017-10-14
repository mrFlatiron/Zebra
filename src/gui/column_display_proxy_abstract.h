#ifndef COLUMN_DISPLAY_PROXY_ABSTRACT_H
#define COLUMN_DISPLAY_PROXY_ABSTRACT_H

#include "kernel/ticket_typedefs.h"
#include "sig/sigslots.h"

class column_display_proxy_abstract
{
public:
  column_display_proxy_abstract () {}
  virtual ~column_display_proxy_abstract () {}

  virtual std::vector<ticket_id> get_shown_indices () = 0;
  sig::signal<> layout_changed;
  sig::signal<> data_changed;
};

#endif // COLUMN_DISPLAY_PROXY_ABSTRACT_H
