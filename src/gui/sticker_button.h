#ifndef STICKER_ADD_BUTTON_H
#define STICKER_ADD_BUTTON_H

#include "sticker_icon.h"
#include "sig/sigslots.h"

class sticker_button : public sticker_icon
{
private:
  QColor m_saved_color;
  QPixmap m_saved_pixmap;
  bool m_cursor_in;
public:
  sticker_button (QWidget *parent = nullptr);
  ~sticker_button ();

  void enterEvent (QEvent *event) override;
  void leaveEvent (QEvent *event) override;
  void mousePressEvent (QMouseEvent *ev) override;
  void mouseReleaseEvent (QMouseEvent *ev) override;
  QSize sizeHint () const override;

  sig::signal<> clicked;
private:
  void hover_enter_animation ();
  void hover_leave_animation ();
  void init ();
};

#endif // STICKER_BUTTON_H
