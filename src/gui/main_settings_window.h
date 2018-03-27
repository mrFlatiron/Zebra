#ifndef MAIN_SETTINGS_WINDOW_H
#define MAIN_SETTINGS_WINDOW_H

#include <QDialog>

#include "sig/connector.h"

class zebra_settings;
class widget_visibility_updater;

class main_settings_window : public QDialog
{
private:
  zebra_settings &m_zebra;

  std::unique_ptr<widget_visibility_updater> m_updater;

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
