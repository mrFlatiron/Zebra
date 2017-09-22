#include "sticker_widget.h"
#include "sticker_colorline.h"
#include "sticker_icon.h"
#include "sticker_body_collapsed.h"
#include "sticker_body_expanded.h"
#include "kernel/task_object.h"

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
  return QSize (300, m_preferred_height);
}

void sticker_widget::expand_body ()
{
}

void sticker_widget::create_widgets ()
{
  m_colorline = new sticker_colorline (this);
  m_colorline->set_color (priority::mid);

  m_icon = new sticker_icon (this);
  m_icon->set_icon (style_settings::common_icons::bug);

  m_body_collapsed = new sticker_body_collapsed (this);
//  m_body_collapsed->hide ();
  m_body_expanded = new sticker_body_expanded (this);
}

void sticker_widget::set_layout ()
{
  using fbh = frame_border_handler;

  m_colorline->borders ().hide_borders      ({fbh::border::right});
  m_icon->borders ().hide_borders           ({fbh::border::right});
  m_body_collapsed->borders ().hide_borders ({fbh::border::bottom});
  m_body_expanded->borders ().hide_borders  ({fbh::border::top});

  QFrame *empty_0 = new QFrame (this);
  QFrame *empty_1 = new QFrame (this);

  empty_0->setFrameShape (QFrame::NoFrame);
  empty_0->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
  empty_1->setFrameShape(QFrame::NoFrame);
  empty_1->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);

  m_icon->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Preferred);
  m_colorline->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Preferred);
  m_body_collapsed->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);

  style_settings::set_background_color (empty_0, common_colors::red);
  style_settings::set_background_color (empty_1, common_colors::mint);

  m_main_layout = new QGridLayout;
  {
    m_main_layout->setSpacing (0);
//    m_main_layout->setContentsMargins (0, 0, 0, 0);
    m_main_layout->addWidget (m_colorline, 0, 0);
    m_main_layout->addWidget (m_icon, 0, 1);
    m_main_layout->addWidget (m_body_collapsed, 0, 2);
    m_main_layout->addWidget (m_body_expanded,  1, 2);
    m_main_layout->addWidget (empty_0, 1, 0);
    m_main_layout->addWidget (empty_1, 1, 1);
    m_main_layout->setRowStretch (2, 2);
    m_main_layout->setColumnStretch (3, 1);
  }
  setLayout (m_main_layout);
}

void sticker_widget::make_connections ()
{

}

