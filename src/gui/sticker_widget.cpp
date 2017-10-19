#include "sticker_widget.h"
#include "sticker_colorline.h"
#include "sticker_icon.h"
#include "sticker_body_collapsed.h"
#include "sticker_body_expanded.h"
#include "kernel/ticket_object.h"
#include "kernel/ticket_ptr.h"
#include "lazy/widget_visibility_updater.h"

#include "style_utils.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

sticker_widget::sticker_widget (QWidget *parent)
  : QWidget (parent)
{
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_widget::~sticker_widget ()
{

}

QSize sticker_widget::sizeHint () const
{
  if (m_is_expanded)
    return QSize (300, style_settings::collapsed_height + 300);
  else
    return QSize (300, style_settings::collapsed_height);
}

QSize sticker_widget::minimumSizeHint () const
{
  return sizeHint ();
}

void sticker_widget::resize_body ()
{
  if (!m_is_expanded)
    {
      m_body_expanded->show ();
      m_main_layout->addWidget (m_body_expanded);
      m_body_collapsed->borders ().hide_borders ({fbh::border::bottom});
      m_is_expanded = true;
      body_expanded ();
    }
  else
    {
      m_body_expanded->hide ();
      m_main_layout->removeWidget (m_body_expanded);
      m_body_collapsed->borders ().show_borders ({fbh::border::bottom});
      m_is_expanded = false;
      body_collapsed ();
    }

}

void sticker_widget::set_ticket (ticket_ptr ticket)
{
  m_ticket = ticket;
  m_body_collapsed->set_ticket (ticket);
  m_body_expanded->set_ticket (ticket);

  if (m_ticket.is_valid ())
    m_conn.connect_to (m_ticket.get ()->data_changed, [this] () {this->set_dirty ();});

  update_view ();
}

void sticker_widget::update_view ()
{
  if (!m_ticket.is_valid ())
    {
      DEBUG_PAUSE ("Check");
      //TODO: do something here
      return;
    }
  m_colorline->set_color (m_ticket.get ()->priority ());
  m_icon->set_icon (m_ticket.get ()->type ());
  m_body_expanded->update_view ();
  m_body_collapsed->update_view ();
}

void sticker_widget::create_widgets ()
{
  put_in (m_visibility_updater);

  m_colorline = new sticker_colorline (this);
  m_colorline->set_color (ticket_priority::mid);

  m_icon = new sticker_icon (this);
  m_icon->set_icon (style_settings::common_icons::bug);

  m_body_collapsed = new sticker_body_collapsed (this);
  m_body_expanded = new sticker_body_expanded (this);

  m_is_expanded = false;
}

void sticker_widget::set_layout ()
{

  m_colorline->borders ().hide_borders      ({fbh::border::right});
  m_icon->borders ().hide_borders           ({fbh::border::right});
  m_body_expanded->borders ().hide_borders  ({fbh::border::top});
  m_body_expanded->hide ();

  m_main_layout = new QVBoxLayout;
  {
    m_main_layout->setSpacing (0);
    QHBoxLayout *hlo_0 = new QHBoxLayout;
    {
      hlo_0->setSpacing (0);
      hlo_0->addWidget (m_colorline);
      hlo_0->addWidget (m_icon);
      hlo_0->addWidget (m_body_collapsed);

    }
    m_main_layout->addLayout (hlo_0);
    m_main_layout->addStretch ();

  }
  setLayout (m_main_layout);
}

void sticker_widget::make_connections ()
{
  m_conn.connect_to (m_body_collapsed->double_clicked, [this] () {this->resize_body ();});
  m_conn.connect_to (m_body_collapsed->next_button_clicked, [this] () {this->next_button_clicked ();});

  m_visibility_updater->set_widget_and_updater (this, [this] () {this->update_view ();});
}

void sticker_widget::set_dirty ()
{
  m_visibility_updater->set_dirty ();
}

