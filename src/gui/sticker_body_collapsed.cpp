#include "sticker_body_collapsed.h"
#include "style_utils.h"
#include "gui/utils/frame_borders.h"

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
  return QSize (300, style_utils::collapsed_height);
}

QSize sticker_body_collapsed::minimumSizeHint () const
{
  return sizeHint ();
}

void sticker_body_collapsed::mouseDoubleClickEvent (QMouseEvent *event)
{
  (void)event;
  double_clicked ();
}

void sticker_body_collapsed::set_ticket (ticket_ptr ticket)
{
  m_ticket = ticket;
}

void sticker_body_collapsed::set_next_is_deletion (bool val)
{
  m_next_is_deletion = val;
  update_view ();
}

bool sticker_body_collapsed::next_is_deletion () const
{
  return m_next_is_deletion;
}

void sticker_body_collapsed::set_prev_button_disabled (bool val)
{
  m_prev_button_disabled = val;
  update_view ();
}

bool sticker_body_collapsed::is_prev_button_disabled () const
{
  return m_prev_button_disabled;
}

void sticker_body_collapsed::update_view ()
{
  m_title->setText (m_ticket.get ()->title ());
  if (!m_next_is_deletion)
    m_next_button->set_icon (style_utils::common_icons::r_arrow);
  else
    m_next_button->set_icon (style_utils::common_icons::trash);

  m_prev_button->setDisabled (m_prev_button_disabled);
  update ();
}

void sticker_body_collapsed::init ()
{
//  m_borders.set_parent (this);
  setAutoFillBackground (true);
  QPalette pal = palette ();
  pal.setBrush (backgroundRole (), QBrush (style_utils::get_color (common_colors::white_blue)));
  setPalette (pal);
}

void sticker_body_collapsed::create_widgets ()
{
  m_title = new QLabel (title_styled ("Notifies the layout system that this widget has changed and may need to change geometry."));
  m_hashtags = new QLabel (hash_styled ("#test2"));
  m_hashtags->setTextFormat (Qt::RichText);
  m_hashtags->setAlignment (Qt::AlignBottom);

  m_next_button = new sticker_button;
  m_prev_button = new sticker_button;

  frame_borders::set_visible_borders (m_next_button, {});
  m_next_button->set_icon ((style_utils::get_icon_path (style_utils::common_icons::r_arrow)));
  m_next_button->set_background_color (style_utils::get_color (common_colors::white_blue));
  m_next_button->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
  m_next_button->setMaximumWidth (35);

  frame_borders::set_visible_borders (m_prev_button, {});
  m_prev_button->set_icon ((style_utils::get_icon_path (style_utils::common_icons::l_arrow)));
  m_prev_button->set_background_color (style_utils::get_color (common_colors::white_blue));
  m_prev_button->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
  m_prev_button->setMaximumWidth (35);
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
    hlo_0->addWidget (m_prev_button, 0, Qt::AlignRight);
    hlo_0->addWidget (m_next_button, 0, Qt::AlignRight);
  }
  setLayout (hlo_0);
}

void sticker_body_collapsed::make_connections ()
{
  m_conn.connect_to (m_next_button->clicked, [this] () {this->next_button_clicked ();});
  m_conn.connect_to (m_prev_button->clicked, [this] () {this->prev_button_clicked ();});
}

QString sticker_body_collapsed::hash_styled (const QString &str)
{
  return style_utils::get_styled_string (str, style_utils::styled_string::hash);
}

QString sticker_body_collapsed::title_styled (const QString &str)
{
  return style_utils::get_styled_string (str, style_utils::styled_string::title);
}
