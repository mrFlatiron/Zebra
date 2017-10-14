#include "sticker_column.h"

#include "sticker_column_internal.h"
#include "sticker_add_button.h"
#include "style_utils.h"

#include "common/enum_misc.h"

#include <QVBoxLayout>

sticker_column::sticker_column (ticket_container &tickets, columns_handler &columns, column_id id, QWidget *parent)
  : QLabel (parent)
{
  init ();
  create_widgets (tickets, columns, id);
  set_layout ();
  make_connections ();
}

sticker_column::~sticker_column ()
{

}

frame_border_handler &sticker_column::borders ()
{
  return m_borders;
}

QSize sticker_column::minimumSizeHint () const
{
  return QSize (300, 100);
}

void sticker_column::set_col_id (column_id id)
{
  m_internal->set_col_id (id);
}

void sticker_column::set_model (column_display_proxy_abstract *model)
{
  m_internal->set_model (model);
}

void sticker_column::update_view ()
{
  m_internal->update_view ();
  updateGeometry ();
}

void sticker_column::init ()
{
  m_borders.set_parent (this);
}

void sticker_column::create_widgets (ticket_container &tickets, columns_handler &columns, column_id id)
{
  m_internal = new sticker_column_internal (tickets, columns, id, this);
  m_add_button = new sticker_add_button (this);
  m_add_button->set_background_color (style_settings::get_color (common_colors::mint));
  m_add_button->set_icon (style_settings::common_icons::plus);


  using borders = frame_border_handler::border;

  m_internal->borders ().set_shape (QFrame::NoFrame);

  m_internal->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
  m_add_button->borders ().hide_borders (vector_of (borders ()));
}

void sticker_column::set_layout ()
{
  QVBoxLayout *vlo_0 = new QVBoxLayout;
  {
    vlo_0->setSpacing (0);
    QScrollArea *scroll = new QScrollArea (this);

    scroll->setWidget (m_internal);
    scroll->setWidgetResizable (true);
    scroll->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOn);

    vlo_0->addWidget (scroll);
    vlo_0->addWidget (m_add_button);
  }
  vlo_0->setContentsMargins (0, 0, 0, 0);
  if (layout ())
    {
      delete layout ();
    }
  setLayout (vlo_0);
}

void sticker_column::make_connections ()
{

}
