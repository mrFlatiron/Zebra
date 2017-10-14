#include "main_window.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>
#include <QSplitter>
#include "sticker_widget.h"
#include  "sticker_column.h"
#include "common/enum_misc.h"
#include "kernel/project_handler.h"
#include "column_display_proxy.h"
#include "common/enum_misc.h"

main_window::main_window (project_handler &zebra, QWidget *parent)
  : QDialog (parent),
    m_zebra (zebra)
{
  init ();
  create_widgets ();
  set_layout ();
  make_connections ();
  update_view ();
}

main_window::~main_window ()
{

}

QSize main_window::sizeHint () const
{
  return QSize (1300, 1300);
}

void main_window::update_view ()
{
  //THIS IS A VERY BAD FUNCTION

  m_columns.clear ();
  m_models.clear ();

  auto ids = m_zebra.columns ().all_ids ();

  for (auto id : ids)
    {
      m_columns.push_back (new sticker_column (m_zebra.tickets (), m_zebra.columns (), id, this));
      m_models.emplace_back (m_zebra.columns (), id);
      m_columns.back ()->set_model (&(m_models.back ()));
    }
  set_layout ();
  updateGeometry ();
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

}

void main_window::set_layout ()
{
  QHBoxLayout *hlo_0 = new QHBoxLayout;
  {
    QSplitter *spl_0 = new QSplitter (this);
    {
      spl_0->setLayoutDirection (Qt::LeftToRight);
      for (int i = 0; i < isize (m_columns); i++)
        {
          m_columns[i]->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred);
          m_columns[i]->borders ().show_borders (vector_of (frame_border_handler::border ()));
//          if (i != isize (m_columns) - 1)
//            m_columns[i]->borders ().hide_borders ({frame_border_handler::border::right});
//          m_columns[i]->borders ().hide_borders (vector_of (frame_border_handler::border ()));
          spl_0->addWidget (m_columns[i]);
          spl_0->setCollapsible (i, false);
        }
    }
    hlo_0->addWidget (spl_0);
  }
  if (layout ())
    {
      delete layout ();
    }
  setLayout (hlo_0);
}

void main_window::make_connections()
{

}
