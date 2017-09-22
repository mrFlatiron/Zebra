#include "sticker_colorline.h"
#include "kernel/task_object.h"
#include "style_utils.h"

sticker_colorline::sticker_colorline (QWidget *parent)
  : QFrame (parent)
{
  init ();
}

sticker_colorline::~sticker_colorline ()
{

}

void sticker_colorline::init ()
{
  m_borders.set_parent (this);
  m_preferred_width = 15;
  set_color (priority::mid);
  setMaximumWidth (m_preferred_width);
}

void sticker_colorline::set_color (const QColor &color)
{
  m_color = color;
  QPalette pal = palette ();
  pal.setColor (QPalette::Background, m_color);
  setAutoFillBackground (true);
  setPalette (pal);
}

void sticker_colorline::set_color (priority type)
{
  set_color (style_settings::priority_to_color (type));
}

QSize sticker_colorline::sizeHint () const
{
  return QSize (m_preferred_width, 50);
}

frame_border_handler &sticker_colorline::borders ()
{
  return m_borders;
}

QColor style_settings::priority_to_color (priority type)
{
  switch (type)
    {
    case priority::low:
      return style_settings::get_color (common_colors::green);
    case priority::mid:
      return style_settings::get_color (common_colors::yellow);
    case priority::high:
      return style_settings::get_color (common_colors::red);
    case priority::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
    }
  return QColor ();
}
