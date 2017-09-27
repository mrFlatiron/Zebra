#include "sticker_column_scroll.h"
#include "sticker_column_internal.h"

sticker_column_scroll::sticker_column_scroll (QWidget *parent)
  : QScrollArea (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_column_scroll::~sticker_column_scroll ()
{

}

frame_border_handler &sticker_column_scroll::borders ()
{
  return m_borders;
}

void sticker_column_scroll::init ()
{
  m_borders.set_parent (this);
  setWidgetResizable (true);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
}

void sticker_column_scroll::create_widgets ()
{
  m_internal = new sticker_column_internal;
  m_internal->borders ().set_shape (QFrame::NoFrame);
}

void sticker_column_scroll::set_layout ()
{
  setWidget (m_internal);
}

void sticker_column_scroll::make_connections ()
{

}
