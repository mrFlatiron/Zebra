#include "sticker_column.h"
#include "sticker_widget.h"
#include "style_utils.h"

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

void sticker_column::init ()
{
  m_borders.set_parent (this);
}

void sticker_column::create_widgets ()
{
  for (int i = 0; i < 20; i++)
    {
      m_stickers.emplace_back (new sticker_widget (this));
      m_stickers[i]->setMinimumWidth (400);
    }
}

void sticker_column::set_layout ()
{
  QVBoxLayout *vlo_0 = new QVBoxLayout;
  {
    vlo_0->setSpacing (0);
    for (int i = 0; i < 20; i++)
      {
        vlo_0->addWidget (m_stickers[i], 0, Qt::AlignTop);
      }
  }
  setLayout (vlo_0);
}

void sticker_column::make_connections ()
{

}
