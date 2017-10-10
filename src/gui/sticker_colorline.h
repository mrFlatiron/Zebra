#ifndef STICKER_COLORLINE_H
#define STICKER_COLORLINE_H

#include <QFrame>
#include <QColor>

#include "frame_border_handler.h"

enum class ticket_priority;

namespace style_settings
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
};

#endif // STICKER_COLORLINE_H
