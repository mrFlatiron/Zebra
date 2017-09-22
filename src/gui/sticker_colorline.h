#ifndef STICKER_COLORLINE_H
#define STICKER_COLORLINE_H

#include <QFrame>
#include <QColor>

#include "frame_border_handler.h"

enum class priority;

namespace style_settings
{
  static QColor priority_to_color (priority type);
}

class sticker_colorline : public QFrame
{
private:
  int m_preferred_width;
  QColor m_color;

  frame_border_handler m_borders;
public:
  sticker_colorline (QWidget *parent = nullptr);
  ~sticker_colorline ();

  void init ();
  void set_color (const QColor &color);
  void set_color (priority type);

  QSize sizeHint () const override;

  frame_border_handler &borders ();
};

#endif // STICKER_COLORLINE_H
