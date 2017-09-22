#include "main_window.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include "sticker_widget.h"

main_window::main_window(QWidget *parent)
  : QDialog (parent)
{
  sticker_widget *sticker = new sticker_widget (this);
  QHBoxLayout *layout = new QHBoxLayout;
  {
    layout->addWidget (sticker);
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
  return QSize (1024, 780);
}
