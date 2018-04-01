#ifndef MAIN_SETTINGS_WINDOW_H
#define MAIN_SETTINGS_WINDOW_H

#include <QDialog>

#include "sig/connector.h"

#include "kernel/settings_typedefs.h"

template<typename T>
class zebra_table_model_adapter;

class zebra_settings;
class widget_visibility_updater;
class user_profile_table_model;
class QComboBox;
class QTableView;

class main_settings_window : public QDialog
{
private:
  zebra_settings &m_zebra;

  std::unique_ptr<widget_visibility_updater> m_updater;
  std::unique_ptr<user_profile_table_model> m_model;
  std::unique_ptr<zebra_table_model_adapter<user_profile_id>> m_adapter;

  QTableView *m_profiles_table_view;
  sig::connector m_conn;
public:
  main_settings_window (zebra_settings &zebra, QWidget *parent = nullptr);
  ~main_settings_window ();

private:
  void create_widgets ();
  void set_layout ();
  void make_connections ();

  void apply ();
  void set_data_from_zebra ();
};

#endif // MAIN_SETTINGS_WINDOW_H
