#include "sticker_body_expanded.h"

#include "style_utils.h"
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

sticker_body_expanded::sticker_body_expanded (QWidget *parent)
  : QFrame (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_body_expanded::~sticker_body_expanded ()
{

}

frame_border_handler &sticker_body_expanded::borders ()
{
  return m_borders;
}

QSize sticker_body_expanded::sizeHint() const
{
  return QSize (500, 300);
}

void sticker_body_expanded::set_ticket (ticket_ptr ticket)
{
  m_ticket = ticket;
  update_view ();
}

void sticker_body_expanded::update_view ()
{
  m_title->setText (m_ticket.get ()->title ());
  m_desc->setText (m_ticket.get ()->description ());
}

void sticker_body_expanded::init ()
{
  m_borders.set_parent (this);
  setAutoFillBackground (true);
  style_settings::set_background_color (this, common_colors::peach);
}

void sticker_body_expanded::create_widgets ()
{
  m_title_lbl = new QLabel ("Title", this);
  m_title =     new QTextEdit ("Real title", this);
  m_desc_lbl =  new QLabel ("Description", this);
  m_desc =      new QTextEdit ("Real #description", this);
}

void sticker_body_expanded::set_layout ()
{
  QVBoxLayout *vlo_0 = new QVBoxLayout;
  {
    vlo_0->addWidget (m_title_lbl, 1, Qt::AlignLeft);
    vlo_0->addWidget (m_title, 2);
    m_title->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred);
    vlo_0->addWidget (m_desc_lbl, 1, Qt::AlignLeft);
    vlo_0->addWidget (m_desc, 4);
    m_desc->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred);
  }
  setLayout (vlo_0);
}

void sticker_body_expanded::make_connections ()
{

}
