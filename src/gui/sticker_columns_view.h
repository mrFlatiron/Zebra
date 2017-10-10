#ifndef STICKER_COLUMNS_VIEW_H
#define STICKER_COLUMNS_VIEW_H

#include "frame_border_handler.h"
#include <QLabel>

class sticker_columns_view : public QLabel
{
private:
  frame_border_handler m_borders;
public:
  sticker_columns_view (QWidget *parent = nullptr);
  ~sticker_columns_view ();

  frame_border_handler &borders ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_COLUMNS_VIEW_H
