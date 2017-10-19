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

column_id sticker_column_internal::col_id () const
{
  return m_col_id;
}

void sticker_column_internal::update_view ()
{
  if (!m_proxy_model)
    return;

  auto ticket_ids = m_proxy_model->get_shown_indices ();

  m_stickers.set_new_ids (ticket_ids);
  for (auto id : m_stickers.values_that_need_construction ())
    {
      m_stickers.emplace (id);
      m_stickers[id]->set_ticket (m_tickets.ticket (id));
      m_stickers[id]->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
      m_conn.connect_to (m_stickers[id]->body_expanded, [this] () {this->reset_layout ();});
      m_conn.connect_to (m_stickers[id]->body_collapsed, [this] () {this->reset_layout ();});
      m_conn.connect_to (m_stickers[id]->next_button_clicked, [this, id] ()
      {this->transfer_to_next_requested (id);});
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

columns_handler &sticker_column_internal::columns ()
{
  return m_columns;
}

const columns_handler &sticker_column_internal::columns () const
{
  return m_columns;
}

ticket_container &sticker_column_internal::tickets ()
{
  return m_tickets;
}

const ticket_container &sticker_column_internal::tickets () const
{
  return m_tickets;
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
    for (auto w : m_stickers.values ())
      {
        vlo_0->addWidget (w);
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
