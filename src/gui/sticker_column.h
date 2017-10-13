#ifndef STICKER_COLUMN_H
#define STICKER_COLUMN_H

#include <QLabel>
#include "frame_border_handler.h"
#include "kernel/ticket_typedefs.h"

class sticker_column_scroll;
class sticker_add_button;
class ticket_container;
class columns_handler;

class sticker_column : public QLabel
{
private:
  frame_border_handler m_borders;
  sticker_column_scroll *m_scroll;
  sticker_add_button *m_add_button;
public:
  sticker_column (ticket_container &tickets, columns_handler &columns, column_id id, QWidget *parent = nullptr);
  ~sticker_column ();

  frame_border_handler &borders ();
  QSize minimumSizeHint () const;

  void set_col_id (column_id id);
  void update_view ();

  column_id col_id () const;
private:
  void init ();
  void create_widgets (ticket_container &tickets, columns_handler &columns, column_id id);
  void set_layout ();
  void make_connections ();


};

#endif // STICKER_COLUMN_H
