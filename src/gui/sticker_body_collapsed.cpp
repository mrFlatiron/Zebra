#include "sticker_body_collapsed.h"
#include "style_utils.h"

#include "sticker_button.h"

#include "common/enum_misc.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>

sticker_body_collapsed::sticker_body_collapsed (QWidget *parent)
  : QFrame (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_body_collapsed::~sticker_body_collapsed ()
{

}

QSize sticker_body_collapsed::sizeHint () const
{
  return QSize (300, style_settings::collapsed_height);
}

QSize sticker_body_collapsed::minimumSizeHint () const
{
  return sizeHint ();
}

frame_border_handler &sticker_body_collapsed::borders ()
{
  return m_borders;
}

void sticker_body_collapsed::mouseDoubleClickEvent (QMouseEvent *event)
{
  (void)event;
  double_clicked ();
}

void sticker_body_collapsed::set_ticket (ticket_ptr ticket)
{
  m_ticket = ticket;
  update_view ();
}

void sticker_body_collapsed::update_view ()
{
  m_title->setText (m_ticket.get ()->title ());
}

void sticker_body_collapsed::init ()
{
  m_borders.set_parent (this);
  setAutoFillBackground (true);
  QPalette pal = palette ();
  pal.setBrush (backgroundRole (), QBrush (style_settings::get_color (common_colors::peach)));
  setPalette (pal);
}

void sticker_body_collapsed::create_widgets ()
{
  m_title = new QLabel (title_styled ("Notifies the layout system that this widget has changed and may need to change geometry."), this);
  m_hashtags = new QLabel (hash_styled ("#test2"), this);
  m_hashtags->setTextFormat (Qt::RichText);
  m_hashtags->setAlignment (Qt::AlignBottom);
  m_next_button = new sticker_button (this);

  m_next_button->borders ().hide_borders (vector_of (frame_border_handler::border::COUNT));
  m_next_button->set_icon ((style_settings::get_icon_path (style_settings::common_icons::r_arrow)));
  m_next_button->set_background_color (style_settings::get_color (common_colors::peach));
  m_next_button->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void sticker_body_collapsed::set_layout ()
{
  QHBoxLayout *hlo_0 = new QHBoxLayout;
  {
    hlo_0->setSpacing (0);
    QVBoxLayout *vlo_0 = new QVBoxLayout;
    {
      vlo_0->addWidget (m_title);
      vlo_0->addWidget (m_hashtags);
    }
    hlo_0->addLayout (vlo_0);
    hlo_0->addStretch ();
    hlo_0->addWidget (m_next_button, 0, Qt::AlignRight);
  }
  setLayout (hlo_0);
}

void sticker_body_collapsed::make_connections ()
{
  m_conn.connect_to (m_next_button->clicked, [this] () {this->next_button_clicked ();});
}

QString sticker_body_collapsed::hash_styled (const QString &str)
{
  return style_settings::get_styled_string (str, style_settings::styled_string::hash);
}

QString sticker_body_collapsed::title_styled (const QString &str)
{
  return style_settings::get_styled_string (str, style_settings::styled_string::title);
}
