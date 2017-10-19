#include "sticker_button.h"
#include <QEvent>
#include <common/enum_misc.h>

sticker_next_button::sticker_next_button (QWidget *parent)
  : sticker_icon (parent)
{
  init ();
}

sticker_next_button::~sticker_next_button ()
{

}

void sticker_next_button::enterEvent (QEvent *event)
{
  if (event->type () != QEvent::Enter)
    return QWidget::enterEvent (event);

  m_cursor_in = true;
  hover_enter_animation ();
}

void sticker_next_button::leaveEvent (QEvent *event)
{
  if (event->type () != QEvent::Leave)
    return QWidget::leaveEvent (event);

  m_cursor_in = false;
  hover_leave_animation ();
}

void sticker_next_button::mousePressEvent (QMouseEvent *ev)
{
  (void)ev;
//  m_borders.show_borders (vector_of (frame_border_handler::border ()));
  m_saved_pixmap = m_pixmap;
  set_icon (m_pixmap.scaled (QSize (30, 30)));
//  m_border_handler.set_width (1, 0);
  m_border_handler.set_shadow (QFrame::Sunken);

}

void sticker_next_button::mouseReleaseEvent(QMouseEvent *ev)
{
  (void)ev;
  m_border_handler.set_shadow (QFrame::Plain);
  set_icon (m_saved_pixmap);
}

QSize sticker_next_button::sizeHint () const
{
  return sticker_icon::sizeHint ();
}

void sticker_next_button::hover_enter_animation ()
{
  m_saved_color = m_background_color;
  set_background_color (QColor (m_background_color.red ()   / 2,
                                m_background_color.green () / 2,
                                m_background_color.blue ()  / 2));
}

void sticker_next_button::hover_leave_animation ()
{
  set_background_color (m_saved_color);
}

void sticker_next_button::init ()
{
  m_saved_color = m_background_color;
  m_border_handler.set_parent (this);
}
