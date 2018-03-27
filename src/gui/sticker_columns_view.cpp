#include "sticker_columns_view.h"
#include "column_display_proxy.h"
#include "mw_columns_display_proxy_abstract.h"
#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "kernel/column_info.h"
#include "sticker_column.h"
#include "utils/frame_borders.h"

#include <QHBoxLayout>
#include <QSplitter>

sticker_columns_view::sticker_columns_view (ticket_container &tickets, columns_handler &columns, QWidget *parent)
  : QLabel (parent),
    m_tickets (tickets),
    m_columns (columns)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
  update_view ();
}

sticker_columns_view::~sticker_columns_view()
{

}

void sticker_columns_view::set_model (mw_columns_display_proxy_abstract *model)
{
  m_conn.disconnect_all ();
  m_model = model;
  m_conn.connect_to (model->layout_changed, [this] {update_view ();});
  update_view ();
}

void sticker_columns_view::update_view ()
{
  if (!m_model)
    return;


  m_columns_widgets.set_new_ids (m_model->get_shown_indices ());
  m_models.set_new_ids (m_model->get_shown_indices ());

  auto ids = m_columns_widgets.values_that_need_construction ();
  for (auto id : ids)
    {
      m_columns_widgets.emplace (id, tickets (), columns (), id);
      m_models.emplace (id, columns ().column (id));
      m_columns_widgets[id]->set_model (m_models[id]);

      m_conn.connect_to (m_columns_widgets[id]->transfer_to_next_requested,
                         [this, id] (ticket_id tid) {this->transfer_to_next_column (tid, id);});
      m_conn.connect_to (m_columns_widgets[id]->transfer_to_prev_requested,
                         [this, id] (ticket_id tid) {this->transfer_to_prev_column (tid, id);});
      m_conn.connect_to (m_columns_widgets[id]->deletion_requested,
                         [this, id] (ticket_id tid) {this->delete_ticket (tid, id);});
      m_columns_widgets[id]->set_is_last (id == m_columns_widgets.current_indices_ref ().back ());

      m_columns_widgets[id]->set_is_first (id == m_columns_widgets.current_indices_ref ().front ());
    }
  set_layout ();
  updateGeometry ();
}

ticket_container &sticker_columns_view::tickets ()
{
  return m_tickets;
}

columns_handler &sticker_columns_view::columns ()
{
  return m_columns;
}

void sticker_columns_view::init ()
{
//  m_borders.set_parent (this);
}

void sticker_columns_view::create_widgets ()
{

}

void sticker_columns_view::set_layout ()
{
  if (!m_hlo_0)
    m_hlo_0 = new QHBoxLayout;

  if (!m_spl_0)
    {
      m_spl_0 = new QSplitter;
      m_hlo_0->addWidget (m_spl_0);
      setLayout (m_hlo_0);
    }

  m_spl_0->setLayoutDirection (Qt::LeftToRight);


  for (auto w : m_columns_widgets.unused_values ())
    w->hide ();

  int i = 0;

  for (auto w : m_columns_widgets.values ())
    {
      w->show ();
      w->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred);
      frame_borders::set_invisible_borders (w, {});
      m_spl_0->insertWidget (i, w);
      m_spl_0->setCollapsible (i, false);
      i++;
    }

  if (m_columns_widgets.values ().size ())
    {
      m_columns_widgets.values ().front ()->set_is_first ();
      m_columns_widgets.values ().back ()->set_is_last ();
    }
}

void sticker_columns_view::make_connections ()
{

}

void sticker_columns_view::transfer_to_next_column (ticket_id tid, column_id from)
{
  if (!m_model)
    return;

  auto ids = m_model->get_shown_indices ();

  for (int i = 0; i < isize (ids) - 1; i++)
    {
      if (ids[i] == from)
        {
          m_columns.transfer_ticket (tid, from, ids[i + 1]);
        }
    }
}

void sticker_columns_view::transfer_to_prev_column (ticket_id tid, column_id from)
{
  if (!m_model)
    return;

  auto ids = m_model->get_shown_indices ();

  for (int i = isize (ids) - 1; i >= 1; i--)
    {
      if (ids[i] == from)
        {
          m_columns.transfer_ticket (tid, from, ids[i - 1]);
        }
    }

}

void sticker_columns_view::delete_ticket (ticket_id tid, column_id cur_col_id)
{
  m_tickets.erase (tid);
  m_columns.column (cur_col_id).remove_ticket (tid);
}
