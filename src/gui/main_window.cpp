#include "main_window.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include "sticker_widget.h"
#include  "sticker_column.h"

main_window::main_window(QWidget *parent)
  : QDialog (parent)
{
  sticker_column *sticker_c = new sticker_column (this);
  sticker_c->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred);
  sticker_column *sticker_c1 = new sticker_column (this);
  sticker_c1->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred);
  sticker_column *sticker_c2 = new sticker_column (this);
  sticker_c2->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred);
  QHBoxLayout *layout = new QHBoxLayout;
  {
    layout->setSpacing (0);

    layout->addWidget (sticker_c);
    layout->addWidget (sticker_c1);
    layout->addWidget (sticker_c2);
  }
  setLayout (layout);

//  QHBoxLayout *hlo_0 = new QHBoxLayout;
//  {

//  }
//  setLayout (hlo_0);
}

main_window::~main_window ()
{

}

QSize main_window::sizeHint () const
{
  return QSize (1300, 780);
}
