#ifndef STICKER_BUTTON_H
#define STICKER_BUTTON_H

#include <QLabel>
#include <QIcon>

#include "frame_border_handler.h"

class QToolButton;
class QPushButton;

class sticker_button : public QLabel
{
private:
  frame_border_handler m_borders;
  QToolButton *m_button;
public:
  sticker_button (QWidget *parent = nullptr);
  ~sticker_button ();

  void set_icon (const QIcon &icon);
  void set_background_color (const QColor &color);

  QSize sizeHint () const override;

  frame_border_handler &borders ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();


};

#endif // STICKER_BUTTON_H
