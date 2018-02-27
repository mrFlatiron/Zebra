#include "sticker_body_expanded.h"

#include "style_utils.h"
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

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
  m_title_lbl = new QLabel ("Title");
  m_title =     new QTextEdit ("Real title");
  style_settings::set_edits_background_color (m_title, common_colors::white);
  m_title->setFrameShape (QFrame::NoFrame);
  m_desc_lbl =  new QLabel ("Description");
  m_desc =      new QTextEdit ("Real #description");
  style_settings::set_edits_background_color (m_desc, common_colors::white);
  m_desc->setFrameShape (QFrame::NoFrame);

  m_apply_pb = new QPushButton ("Apply");
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

    QHBoxLayout *hlo_1 = new QHBoxLayout;
    {
      hlo_1->addStretch ();
      hlo_1->addWidget (m_apply_pb);
    }
    vlo_0->addLayout (hlo_1);
  }
  setLayout (vlo_0);
}

void sticker_body_expanded::make_connections ()
{
  connect (m_apply_pb, SIGNAL (clicked ()), this, SLOT (on_apply ()));
}

void sticker_body_expanded::on_apply ()
{
  m_ticket.get ()->set_title (m_title->toPlainText ());
  m_ticket.get ()->set_description (m_desc->toPlainText ());
  apply_clicked ();
}
