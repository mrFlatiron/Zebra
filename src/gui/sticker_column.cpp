#include "sticker_column.h"

#include "sticker_column_scroll.h"
#include "sticker_add_button.h"
#include "style_utils.h"

#include "common/enum_misc.h"

#include <QVBoxLayout>

sticker_column::sticker_column (QWidget *parent)
  : QLabel (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_column::~sticker_column ()
{

}

frame_border_handler &sticker_column::borders ()
{
  return m_borders;
}

QSize sticker_column::minimumSizeHint () const
{
 return QSize (300, 100);
}

void sticker_column::init ()
{
  m_borders.set_parent (this);
}

void sticker_column::create_widgets ()
{
  m_scroll = new sticker_column_scroll (this);
  m_add_button = new sticker_add_button (this);
  m_add_button->set_background_color (style_settings::get_color (common_colors::mint));
  m_add_button->set_icon (style_settings::common_icons::plus);


  using borders = frame_border_handler::border;

  m_scroll->borders ().set_shape (QFrame::NoFrame);

//  m_scroll->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
  m_add_button->borders ().hide_borders (vector_of (borders ()));
}

void sticker_column::set_layout ()
{
  QVBoxLayout *vlo_0 = new QVBoxLayout;
  {
    vlo_0->setSpacing (0);
    vlo_0->addWidget (m_scroll);
    vlo_0->addWidget (m_add_button);
  }
  vlo_0->setContentsMargins (0, 0, 0, 0);
  setLayout (vlo_0);
}

void sticker_column::make_connections ()
{

}
