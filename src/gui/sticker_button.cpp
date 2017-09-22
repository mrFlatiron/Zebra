#include "sticker_button.h"

#include <QToolButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLayout>
#include <QPixmap>


sticker_button::sticker_button (QWidget *parent)
  : QLabel (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_button::~sticker_button ()
{

}

void sticker_button::init ()
{
  setAutoFillBackground (true);
  m_borders.set_parent (this);
}

void sticker_button::create_widgets ()
{
  m_button = new QToolButton (this);

  m_button->setAutoFillBackground (true);
}

void sticker_button::set_layout ()
{
  QHBoxLayout *hlo_0 = new QHBoxLayout;
  {
    hlo_0->addWidget (m_button, 0, Qt::AlignCenter);
  }
  setLayout (hlo_0);
  hlo_0->setContentsMargins (0, 0, 0, 0);
}

void sticker_button::make_connections ()
{

}

void sticker_button::set_icon (const QIcon &icon)
{
  m_button->setIcon (icon);
  m_button->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_button->setMinimumSize (QSize (50, 46));
}

void sticker_button::set_background_color (const QColor &color)
{
  QPalette pal = palette ();
  pal.setBrush (backgroundRole (), QBrush (color));
  setPalette (pal);

  pal = m_button->palette ();
  pal.setBrush (m_button->backgroundRole (), QBrush (color));
  m_button->setPalette (pal);
}

QSize sticker_button::sizeHint() const
{
  return QSize (50, 50);
}

frame_border_handler &sticker_button::borders ()
{
  return m_borders;
}
