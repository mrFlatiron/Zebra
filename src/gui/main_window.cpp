#include "main_window.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>
#include <QSplitter>
#include "sticker_widget.h"
#include  "sticker_column.h"
#include "common/enum_misc.h"

main_window::main_window(QWidget *parent)
  : QDialog (parent)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
}

main_window::~main_window ()
{

}

QSize main_window::sizeHint () const
{
  return QSize (1300, 1300);
}

void main_window::init ()
{
  setWindowFlags (Qt::Window |
                  Qt::CustomizeWindowHint |
                  Qt::MaximizeUsingFullscreenGeometryHint |
                  Qt::WindowMaximizeButtonHint |
                  Qt::WindowCloseButtonHint);
}

void main_window::create_widgets ()
{
  for (int i = 0; i < 3; i++)
    m_columns.emplace_back (new sticker_column (this));
}

void main_window::set_layout ()
{
  QHBoxLayout *hlo_0 = new QHBoxLayout;
  {
    QSplitter *spl_0 = new QSplitter (this);
    {
      spl_0->setLayoutDirection (Qt::LeftToRight);
      for (int i = 0; i < 3; i++)
        {
          m_columns[i]->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred);
          //        if (i != 2)
          //          m_columns[i]->borders ().hide_borders ({frame_border_handler::border::right});
          //        m_columns[i]->borders ().hide_borders (vector_of (frame_border_handler::border ()));
          spl_0->addWidget (m_columns[i]);
          spl_0->setCollapsible (i, false);
        }
    }
    hlo_0->addWidget (spl_0);
  }
  setLayout (hlo_0);
}

void main_window::make_connections()
{

}
