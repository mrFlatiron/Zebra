#ifndef STICKER_COLUMN_SCROLL_H
#define STICKER_COLUMN_SCROLL_H

#include <QScrollArea>
#include "frame_border_handler.h"
#include "kernel/ticket_typedefs.h"

class sticker_column_internal;
class columns_handler;
class ticket_container;

class sticker_column_scroll : public QScrollArea  //proxy class.
{
private:
  frame_border_handler m_borders;
  sticker_column_internal *m_internal;
public:
  sticker_column_scroll (ticket_container &tickets, columns_handler &columns, column_id id, QWidget *parent = nullptr);
  ~sticker_column_scroll ();

  frame_border_handler &borders ();
  sticker_column_internal *internal ();
  void update_view ();
  void set_col_id (column_id id);
private:
  void init ();
  void create_widgets (ticket_container &tickets, columns_handler &columns, column_id id);
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_COLUMN_SCROLL_H
