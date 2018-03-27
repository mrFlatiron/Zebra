#include "main_settings_window.h"
#include "lazy/widget_visibility_updater.h"
#include "kernel/zebra_settings.h"

#include <QLabel>
#include <QHBoxLayout>

main_settings_window::main_settings_window (zebra_settings &zebra, QWidget *parent)
  : QDialog (parent),
    m_zebra (zebra)
{
  create_widgets ();
  set_layout ();
  make_connections ();
}

main_settings_window::~main_settings_window ()
{

}

void main_settings_window::create_widgets ()
{
  put_in (m_updater, this, [this] {set_data_from_zebra ();});
}

void main_settings_window::set_layout ()
{

}

void main_settings_window::make_connections ()
{
  m_conn.connect_to (m_zebra.settings_changed, [this] {m_updater->set_dirty ();});
}

void main_settings_window::apply ()
{

}

void main_settings_window::set_data_from_zebra ()
{

}
