#include "sticker_column_internal.h"
#include "sticker_widget.h"
#include "style_utils.h"

#include <QVBoxLayout>
#include <QScrollArea>

sticker_column_internal::sticker_column_internal (QWidget *parent)
  : QLabel (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

sticker_column_internal::~sticker_column_internal ()
{

}

frame_border_handler &sticker_column_internal::borders ()
{
  return m_borders;
}

QSize sticker_column_internal::sizeHint () const
{
  return QSize (400, 150);
}

void sticker_column_internal::init ()
{
  m_borders.set_parent (this);
}

void sticker_column_internal::create_widgets ()
{
  m_vlo_0 = new QVBoxLayout;
  for (int i = 0; i < 5; i++)
    {
      m_stickers.emplace_back (new sticker_widget (this));
      m_stickers[i]->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
      connect (m_stickers[i], SIGNAL (body_expanded ()), this, SLOT (reset_layout ()));
      connect (m_stickers[i], SIGNAL (body_collapsed ()), this, SLOT (reset_layout ()));
    }

}

void sticker_column_internal::set_layout ()
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

void sticker_column_internal::make_connections ()
{

}

void sticker_column_internal::reset_layout ()
{
  updateGeometry ();
}
