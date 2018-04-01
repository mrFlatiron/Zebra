#include "main_settings_window.h"
#include "lazy/widget_visibility_updater.h"
#include "kernel/zebra_settings.h"
#include "user_profile_table_model.h"
#include "model_view/zebra_table_model_adapter.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QTableView>

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
  put_in (m_model, m_zebra);
  put_in (m_adapter, m_model.get ());

  m_profiles_table_view = new QTableView;
  m_profiles_table_view->setModel (m_adapter.get ());
}

void main_settings_window::set_layout ()
{
  QHBoxLayout *hlo_0 = new QHBoxLayout;
  {
    hlo_0->addWidget (m_profiles_table_view);
    hlo_0->addStretch ();
  }
  setLayout (hlo_0);
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
