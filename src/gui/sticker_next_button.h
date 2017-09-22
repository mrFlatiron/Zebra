#ifndef STICKER_NEXT_BUTTON_H
#define STICKER_NEXT_BUTTON_H

#include "sticker_icon.h"
#include "frame_border_handler.h"

class sticker_next_button : public sticker_icon
{
  QColor m_saved_color;
  QPixmap m_saved_pixmap;
  bool m_cursor_in;
public:
  sticker_next_button (QWidget *parent = nullptr);
  ~sticker_next_button ();

  void enterEvent (QEvent *event) override;
  void leaveEvent (QEvent *event) override;
  void mousePressEvent (QMouseEvent *ev) override;
  void mouseReleaseEvent (QMouseEvent *ev) override;
  QSize sizeHint () const override;
private:
  void hover_enter_animation ();
  void hover_leave_animation ();
  void init ();
};

#endif // STICKER_NEXT_BUTTON_H
