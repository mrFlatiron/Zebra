#include "sticker_colorline.h"
#include "kernel/ticket_object.h"
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
  set_color (ticket_priority::mid);
}

void sticker_colorline::set_color (const QColor &color)
{
  m_color = color;
  QPalette pal = palette ();
  pal.setColor (QPalette::Background, m_color);
  setAutoFillBackground (true);
  setPalette (pal);
}

void sticker_colorline::set_color (ticket_priority type)
{
  set_color (style_settings::priority_to_color (type));
}

QSize sticker_colorline::sizeHint () const
{
  return QSize (15, style_settings::collapsed_height);
}

QSize sticker_colorline::minimumSizeHint () const
{
  return sizeHint ();
}

frame_border_handler &sticker_colorline::borders ()
{
  return m_borders;
}

QColor style_settings::priority_to_color (ticket_priority type)
{
  switch (type)
    {
    case ticket_priority::low:
      return style_settings::get_color (common_colors::green);
    case ticket_priority::mid:
      return style_settings::get_color (common_colors::yellow);
    case ticket_priority::high:
      return style_settings::get_color (common_colors::red);
    case ticket_priority::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
    }
  return QColor ();
}
