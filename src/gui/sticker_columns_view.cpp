#include "sticker_columns_view.h"

sticker_columns_view::sticker_columns_view (QWidget *parent)
  : QLabel (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_columns_view::~sticker_columns_view()
{

}

frame_border_handler &sticker_columns_view::borders ()
{
  return m_borders;
}

void sticker_columns_view::init ()
{
  m_borders.set_parent (this);
}

void sticker_columns_view::create_widgets ()
{

}

void sticker_columns_view::set_layout ()
{

}

void sticker_columns_view::make_connections ()
{

}
