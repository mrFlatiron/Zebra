#include "sticker_column.h"

#include "sticker_column_internal.h"
#include "sticker_button.h"
#include "style_utils.h"
#include "kernel/ticket_object.h"
#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "utils/frame_borders.h"

#include "common/enum_misc.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

#include <QToolBar>

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

QSize sticker_column::minimumSizeHint () const
{
  return QSize (300, 100);
}

void sticker_column::set_col_id (column_id id)
{
  m_internal->set_col_id (id);
}

column_id sticker_column::col_id () const
{
  return m_internal->col_id ();
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

ticket_container &sticker_column::tickets()
{
  return m_internal->tickets ();
}

const ticket_container &sticker_column::tickets () const
{
  return m_internal->tickets ();
}

columns_handler &sticker_column::columns ()
{
  return m_internal->columns ();
}

const columns_handler &sticker_column::columns () const
{
  return m_internal->columns ();
}

void sticker_column::set_is_last (bool val)
{
  m_internal->set_is_last (val);
}

void sticker_column::set_is_first (bool val)
{
  m_internal->set_is_first (val);
}

void sticker_column::init ()
{
}

void sticker_column::create_widgets (ticket_container &tickets, columns_handler &columns, column_id id)
{
  m_colname_label = new QLabel (columns.column (id).name ());

  m_tool_bar_left_aligned = new QToolBar;
  m_tool_bar_right_aligned = new QToolBar;

  m_tool_bar_left_aligned->setOrientation (Qt::Horizontal);
  m_tool_bar_right_aligned->setOrientation (Qt::Horizontal);

  m_tool_bar_left_aligned->addAction (QIcon (style_utils::get_icon_path (style_utils::common_icons::collapse_left)), "Hide");

  m_tool_bar_right_aligned->addAction (QIcon (style_utils::get_icon_path (style_utils::common_icons::settings)), "Settings");
  m_tool_bar_right_aligned->addSeparator ();
  m_tool_bar_right_aligned->addAction (QIcon (style_utils::get_icon_path (style_utils::common_icons::black_plus)), "Add ticket", [this] () {this->add_ticket ();});
  m_tool_bar_right_aligned->addSeparator ();
  m_tool_bar_right_aligned->addAction (QIcon (style_utils::get_icon_path (style_utils::common_icons::x_mark)), "Delete column", [this] () {delete_column ();});

  m_internal = new sticker_column_internal (tickets, columns, id);
  m_add_button = new sticker_button;
  m_add_button->set_background_color (style_utils::get_color (common_colors::mint));
  m_add_button->set_icon (style_utils::common_icons::plus);


  m_internal->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
  frame_borders::set_shape (this, QFrame::Box);
  frame_borders::set_invisible_borders (this, {});
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

    QHBoxLayout *hlo_0 = new QHBoxLayout;
    {
      hlo_0->addWidget (m_tool_bar_left_aligned, Qt::AlignLeft);
      hlo_0->addWidget (m_colname_label, Qt::AlignLeft);
      hlo_0->addWidget (m_tool_bar_right_aligned);
//      hlo_0->addWidget (new QLineEdit, Qt::AlignRight);
    }
    vlo_0->addLayout (hlo_0);

    vlo_0->addWidget (scroll);
//    vlo_0->addWidget (m_add_button);
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
  m_conn.connect_to (m_add_button->clicked, [this] () {this->add_ticket ();});
  m_conn.connect_to (m_internal->transfer_to_next_requested, [this] (ticket_id tid)
  {this->transfer_to_next_requested (tid);});
  m_conn.connect_to (m_internal->transfer_to_prev_requested, [this] (ticket_id tid)
  {this->transfer_to_prev_requested (tid);});
  m_conn.connect_to (m_internal->deletion_requested, [this] (ticket_id tid)
  {
    this->deletion_requested (tid);
  });
}

void sticker_column::add_ticket ()
{
  ticket_object new_ticket;
  auto tid = tickets ().add_ticket (std::move (new_ticket));
  columns ().column (col_id ()).add_ticket (tid);
}

void sticker_column::delete_column ()
{
  //TEMPCODE_BEGIN
  if (columns ().column (col_id ()).tickets ().size ())
    return;
  //TEMPCODE_END
  columns ().delete_column (col_id ());
}
