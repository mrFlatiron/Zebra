#ifndef STICKER_COLUMN_H
#define STICKER_COLUMN_H

#include <QLabel>
#include "frame_border_handler.h"

class sticker_column_scroll;
class sticker_add_button;

class sticker_column : public QLabel
{
private:
  frame_border_handler m_borders;
  sticker_column_scroll *m_scroll;
  sticker_add_button *m_add_button;
public:
  sticker_column (QWidget *parent = nullptr);
  ~sticker_column ();

  frame_border_handler &borders ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_COLUMN_H
