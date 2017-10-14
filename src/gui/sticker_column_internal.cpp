#include "sticker_column_internal.h"
#include "sticker_widget.h"
#include "style_utils.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "kernel/ticket_object.h"

#include "column_display_proxy_abstract.h"

#include <QVBoxLayout>
#include <QScrollArea>

sticker_column_internal::sticker_column_internal (ticket_container &tickets, columns_handler &columns, column_id col_id, QWidget *parent)
  : QLabel (parent),
    m_col_id (col_id),
    m_columns (columns),
    m_tickets (tickets)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
  update_view ();
}

sticker_column_internal::~sticker_column_internal ()
{

}

frame_border_handler &sticker_column_internal::borders ()
{
  return m_borders;
}

QSize sticker_column_internal::sizeHint () const
{
  return QSize (400, 150);
}

void sticker_column_internal::set_col_id (column_id id)
{
  m_col_id = id;
}

void sticker_column_internal::update_view ()
{
  if (!m_proxy_model)
    return;

  m_stickers.clear ();

  auto ticket_ids = m_proxy_model->get_shown_indices ();
  for (auto id : ticket_ids)
    {
      m_stickers.push_back (new sticker_widget (this));
      m_stickers.back ()->set_ticket (m_tickets.ticket (id));
      m_stickers.back ()->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
      m_conn.connect_to (m_stickers.back ()->body_expanded, [this] () {this->reset_layout ();});
      m_conn.connect_to (m_stickers.back ()->body_collapsed, [this] () {this->reset_layout ();});
    }
  set_layout ();
  updateGeometry ();
}

void sticker_column_internal::set_model (column_display_proxy_abstract *model)
{
  m_proxy_model = model;
  if (!model)
    {
      DEBUG_PAUSE ("Is this ok?")
          return;
    }
  m_conn.connect_to (m_proxy_model->layout_changed, [this] () {this->update_view ();});
  update_view ();
}

void sticker_column_internal::init ()
{
  m_borders.set_parent (this);
}

void sticker_column_internal::create_widgets ()
{

}

void sticker_column_internal::set_layout ()
{
  QVBoxLayout *vlo_0 = new QVBoxLayout;
  {
    vlo_0->setSpacing (0);
    for (int i = 0; i < isize (m_stickers); i++)
      {
        vlo_0->addWidget (m_stickers[i]);
      }
    vlo_0->addStretch ();
  }
  vlo_0->setSizeConstraint (QLayout::SetMinAndMaxSize);
  if (layout ())
    {
      delete layout ();
    }
  setLayout (vlo_0);
}

void sticker_column_internal::make_connections ()
{

}

void sticker_column_internal::reset_layout ()
{
  updateGeometry ();
}
