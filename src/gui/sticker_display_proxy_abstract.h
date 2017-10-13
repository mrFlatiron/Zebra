#ifndef STICKER_DISPLAY_PROXY_H
#define STICKER_DISPLAY_PROXY_H

#include "kernel/ticket_typedefs.h"
#include "sig/sigslots.h"

template<typename IndexType>
class sticker_display_proxy_abstract
{
public:
  sticker_display_proxy_abstract () {}
  virtual ~sticker_display_proxy_abstract () {}

  virtual std::vector<IndexType> get_shown_indices () = 0;
  sig::signal<> layout_changed;
  sig::signal<> data_changed;
};

#endif // STICKER_DISPLAY_PROXY_H
