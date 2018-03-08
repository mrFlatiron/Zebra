#ifndef STICKER_COLORLINE_H
#define STICKER_COLORLINE_H

#include <QFrame>
#include <QColor>

#include "frame_border_handler.h"
#include "sig/sigsignal.h"

enum class ticket_priority;

namespace style_utils
{
  QColor priority_to_color (ticket_priority type);
}

class sticker_colorline : public QFrame
{
private:
  QColor m_color;

  frame_border_handler m_borders;
public:
  sticker_colorline (QWidget *parent = nullptr);
  ~sticker_colorline ();

  void init ();
  void set_color (const QColor &color);
  void set_color (ticket_priority type);

  QSize sizeHint () const override;
  QSize minimumSizeHint () const override;

  frame_border_handler &borders ();

  void mouseReleaseEvent (QMouseEvent *ev) override;

  sig::signal<> right_clicked;
};

#endif // STICKER_COLORLINE_H
