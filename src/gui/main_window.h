#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>

class ticket_container;
class column_handler;
class sticker_column;
class column_display_proxy;
class sticker_columns_view;
class mw_columns_display_std;
class zebra_settings;
class main_settings_window;
class QMenuBar;
class QToolBar;

class main_window : public QDialog
{
private:
  QToolBar *m_main_mb;
  sticker_columns_view *m_columns_view;
  main_settings_window *m_settings_window = nullptr;
  std::unique_ptr<mw_columns_display_std> m_model;
  zebra_settings &m_zebra;
public:
  main_window (zebra_settings &zebra, QWidget *parent = 0);
  ~main_window ();
  QSize sizeHint () const override;

  void update_view ();

private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();

  void open_settings_window ();
};

#endif // MAIN_WINDOW_H
