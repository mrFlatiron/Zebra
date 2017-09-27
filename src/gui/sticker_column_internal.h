#ifndef STICKER_COLUMN_INTERNAL_H
#define STICKER_COLUMN_INTERNAL_H

#include <QLabel>
#include <QScrollArea>
#include "frame_border_handler.h"

class sticker_widget;
class QScrollArea;
class QVBoxLayout;

class sticker_column_internal : public QLabel
{
  Q_OBJECT
private:
  frame_border_handler m_borders;
  std::vector<sticker_widget *> m_stickers;
  QVBoxLayout *m_vlo_0;
public:
  sticker_column_internal (QWidget *parent = nullptr);
  ~sticker_column_internal ();


  frame_border_handler &borders ();
  QSize sizeHint () const override;

private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
private slots:
  void reset_layout ();
};

#endif // STICKER_COLUMN_INTERNAL_H
