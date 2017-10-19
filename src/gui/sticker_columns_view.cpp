#include "sticker_columns_view.h"
#include "column_display_proxy.h"
#include "mw_columns_display_proxy_abstract.h"
#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "kernel/column_info.h"
#include "sticker_column.h"

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

frame_border_handler &sticker_columns_view::borders ()
{
  return m_borders;
}

void sticker_columns_view::set_model (mw_columns_display_proxy_abstract *model)
{
  m_model = model;
  update_view ();
}

void sticker_columns_view::update_view ()
{
  m_columns_widgets.clear ();
  m_models.clear ();

  if (!m_model)
    return;

  auto ids = m_model->get_shown_indices ();

  for (auto id : ids)
    {
      m_columns_widgets.emplace_back (new sticker_column (tickets (), columns (), id));
      m_models.emplace_back (new column_display_proxy (columns ().column (id)));
      m_columns_widgets.back ()->set_model (m_models.back ().get ());

      m_conn.connect_to (m_columns_widgets.back ()->transfer_to_next_requested,
                         [this, id] (ticket_id tid) {this->transfer_to_next_column (tid, id);});
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
  m_borders.set_parent (this);
}

void sticker_columns_view::create_widgets ()
{

}

void sticker_columns_view::set_layout ()
{
  QHBoxLayout *hlo_0 = new QHBoxLayout;
  {
    QSplitter *spl_0 = new QSplitter (this);
    {
      spl_0->setLayoutDirection (Qt::LeftToRight);
      for (int i = 0; i < isize (m_columns_widgets); i++)
        {
          m_columns_widgets[i]->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred);
          m_columns_widgets[i]->borders ().show_borders (vector_of (frame_border_handler::border ()));
          spl_0->addWidget (m_columns_widgets[i].get ());
          spl_0->setCollapsible (i, false);
        }
    }
    hlo_0->addWidget (spl_0);
  }
  if (layout ())
    {
      delete layout ();
    }
  setLayout (hlo_0);
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
