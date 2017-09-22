#include "frame_border_handler.h"

frame_border_handler::frame_border_handler (QFrame *parent)
{
  m_parent = parent;
  m_border_width = 2;
  m_border_mid_width = 2;
  m_shape = QFrame::Box;
  m_shadow = QFrame::Plain;
  m_borders_visible.set (true);
}

frame_border_handler::~frame_border_handler ()
{

}

void frame_border_handler::set_width (const int width, const int mid_width)
{
  m_border_width = width;
  m_border_mid_width = mid_width;
  apply ();
}

void frame_border_handler::set_shape (QFrame::Shape shape)
{
  m_shape = shape;
  apply ();
}

void frame_border_handler::set_shadow (QFrame::Shadow shadow)
{
  m_shadow = shadow;
  apply ();
}

void frame_border_handler::set_parent (QFrame *parent)
{
  if (m_parent == parent)
    return;

  m_parent = parent;
  apply ();
}

void frame_border_handler::hide_borders (const std::vector<frame_border_handler::border> &borders)
{
  for (border b : borders)
    m_borders_visible.set (b, false);
  apply ();
}

void frame_border_handler::apply ()
{
  if (!m_parent)
    return;

  bool need_change = false;

  if (   m_parent->frameShape ()   != m_shape
      || m_parent->lineWidth ()    != m_border_width
      || m_parent->midLineWidth () != m_border_mid_width
      || m_parent->contentsMargins () != construct_margins ()
      || m_parent->frameShadow () != m_shadow
     )
    need_change = true;

  if (!need_change)
    return;

  m_parent->setFrameShape (m_shape);
  m_parent->setLineWidth (m_border_width);
  m_parent->setMidLineWidth (m_border_mid_width);
  m_parent->setContentsMargins (construct_margins ());
  m_parent->setFrameShadow (m_shadow);
}

QMargins frame_border_handler::construct_margins ()
{
  QMargins marg;
  int w = m_border_width;
  if (m_borders_visible[border::left])
    marg.setLeft (w);
  else
    marg.setLeft (0);
  if (m_borders_visible[border::top])
    marg.setTop (w);
  else
    marg.setTop (0);
  if (m_borders_visible[border::right])
    marg.setRight (w);
  else
    marg.setRight (0);
  if (m_borders_visible[border::bottom])
    marg.setBottom (w);
  else
    marg.setBottom (0);
  return marg;
}
