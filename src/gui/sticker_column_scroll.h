#ifndef STICKER_COLUMN_SCROLL_H
#define STICKER_COLUMN_SCROLL_H

#include <QScrollArea>
#include "frame_border_handler.h"

class sticker_column_internal;

class sticker_column_scroll : public QScrollArea
{
private:
  frame_border_handler m_borders;
  sticker_column_internal *m_internal;
public:
  sticker_column_scroll (QWidget *parent = nullptr);
  ~sticker_column_scroll ();

  frame_border_handler &borders ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_COLUMN_SCROLL_H
