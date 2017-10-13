#include "sticker_column_scroll.h"
#include "sticker_column_internal.h"

sticker_column_scroll::sticker_column_scroll (ticket_container &tickets, columns_handler &columns, column_id col_id, QWidget *parent)
  : QScrollArea (parent)
{
  init ();
  create_widgets (tickets, columns, col_id);
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

sticker_column_internal *sticker_column_scroll::internal ()
{
  return m_internal;
}

void sticker_column_scroll::update_view ()
{
  m_internal->update_view ();
}

void sticker_column_scroll::set_col_id (column_id id)
{
  m_internal->set_col_id (id);
}

void sticker_column_scroll::init ()
{
  m_borders.set_parent (this);
  setWidgetResizable (true);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
}

void sticker_column_scroll::create_widgets (ticket_container &tickets, columns_handler &columns, column_id id)
{
  m_internal = new sticker_column_internal (tickets, columns, id);
  m_internal->borders ().set_shape (QFrame::NoFrame);
}

void sticker_column_scroll::set_layout ()
{
  setWidget (m_internal);
}

void sticker_column_scroll::make_connections ()
{

}
