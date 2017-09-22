#ifndef STICKER_COLUMN_H
#define STICKER_COLUMN_H

#include <QLabel>
#include "frame_border_handler.h"

class sticker_widget;


class sticker_column : public QLabel
{
private:
  frame_border_handler m_borders;
  std::vector<sticker_widget *> m_stickers;
public:
  sticker_column (QWidget *parent = nullptr);
  ~sticker_column ();

private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_COLUMN_H
