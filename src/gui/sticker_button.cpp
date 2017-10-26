#include "sticker_button.h"

#include <QEvent>

sticker_button::sticker_button (QWidget *parent)
  : sticker_icon (parent)
{
  init ();
}

sticker_button::~sticker_button ()
{

}

void sticker_button::enterEvent (QEvent *event)
{
  if (event->type () != QEvent::Enter)
    return QWidget::enterEvent (event);

  m_cursor_in = true;
  hover_enter_animation ();
}

void sticker_button::leaveEvent (QEvent *event)
{
  if (event->type () != QEvent::Leave)
    return QWidget::leaveEvent (event);

  m_cursor_in = false;
  hover_leave_animation ();
}

void sticker_button::mousePressEvent (QMouseEvent *ev)
{
  (void)ev;
//  m_borders.show_borders (vector_of (frame_border_handler::border ()));
  m_saved_pixmap = m_pixmap;
  QSize init_size = m_pixmap.size ();
  QSize scaled_size = QSize (static_cast<double> (init_size.width ()) * 0.8,
                             static_cast<double> (init_size.height ()) * 0.8);
  set_icon (m_pixmap.scaled (scaled_size));
//  m_border_handler.set_width (1, 0);
  m_border_handler.set_shadow (QFrame::Sunken);

}

void sticker_button::mouseReleaseEvent(QMouseEvent *ev)
{
  (void)ev;
  m_border_handler.set_shadow (QFrame::Plain);
  set_icon (m_saved_pixmap);
  clicked ();
}

QSize sticker_button::sizeHint () const
{
  return  sticker_icon::sizeHint ();
}

void sticker_button::hover_enter_animation ()
{
  m_saved_color = m_background_color;
  set_background_color (QColor (m_background_color.red ()   / 2,
                                m_background_color.green () / 2,
                                m_background_color.blue ()  / 2));
}

void sticker_button::hover_leave_animation ()
{
  set_background_color (m_saved_color);
}

void sticker_button::init ()
{
  m_saved_color = m_background_color;
  m_border_handler.set_parent (this);
}
