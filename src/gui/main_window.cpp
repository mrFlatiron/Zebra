#include "main_window.h"

#include <QVBoxLayout>
#include <QToolBar>

#include "kernel/zebra_settings.h"
#include "sticker_columns_view.h"
#include "mw_columns_display_std.h"
#include "main_settings_window.h"

main_window::main_window (zebra_settings &zebra, QWidget *parent)
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
  m_columns_view->update_view ();
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
  m_main_mb = new QToolBar;
  auto settings = m_main_mb->addAction ("Settings");
  connect (settings, &QAction::triggered, this, &main_window::open_settings_window);

  m_columns_view = new sticker_columns_view (m_zebra.current_profile ()->settings ().tickets (), m_zebra.current_profile ()->settings ().columns (), this);
  put_in (m_model, m_zebra.current_profile ()->settings ().columns ());
  m_columns_view->set_model (m_model.get ());
}

void main_window::set_layout ()
{
  QVBoxLayout *vlo_0 = new QVBoxLayout;
  {
    vlo_0->setMenuBar (m_main_mb);
    vlo_0->addWidget (m_columns_view);
  }
  setLayout (vlo_0);
}

void main_window::make_connections ()
{

}

void main_window::open_settings_window ()
{
  if (!m_settings_window)
    m_settings_window = new main_settings_window (m_zebra, this);

  m_settings_window->show ();
  m_settings_window->activateWindow ();
}
