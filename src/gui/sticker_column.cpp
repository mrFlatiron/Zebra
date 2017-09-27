#include "sticker_column.h"
#include "sticker_widget.h"
#include "style_utils.h"

#include <QVBoxLayout>
#include <QScrollArea>

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

QSize sticker_column::sizeHint () const
{
  return QSize (400, 150);
}

void sticker_column::init ()
{
  m_borders.set_parent (this);
}

void sticker_column::create_widgets ()
{
  m_vlo_0 = new QVBoxLayout;
  for (int i = 0; i < 5; i++)
    {
      m_stickers.emplace_back (new sticker_widget (this));
      m_stickers[i]->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
      connect (m_stickers[i], SIGNAL (body_expanded ()), this, SLOT (reset_layout ()));
      connect (m_stickers[i], SIGNAL (body_collapsed ()), this, SLOT (reset_layout ()));
    }

}

void sticker_column::set_layout ()
{
  {
    m_vlo_0->setSpacing (0);
    for (int i = 0; i < 5; i++)
      {
        m_vlo_0->addWidget (m_stickers[i]);
      }
    m_vlo_0->addStretch ();
  }
  m_vlo_0->setSizeConstraint (QLayout::SetMinAndMaxSize);
  setLayout (m_vlo_0);
}

void sticker_column::make_connections ()
{

}

void sticker_column::reset_layout ()
{
  updateGeometry ();
}
