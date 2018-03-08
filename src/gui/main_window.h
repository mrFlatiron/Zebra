#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>

class ticket_container;
class column_handler;
class project_handler;
class sticker_column;
class column_display_proxy;
class sticker_columns_view;
class mw_columns_display_std;

class main_window : public QDialog
{
  Q_OBJECT
private:
  sticker_columns_view *m_columns_view;
  std::unique_ptr<mw_columns_display_std> m_model;
  project_handler &m_zebra;
public:
  main_window (project_handler &zebra, QWidget *parent = 0);
  ~main_window ();
  QSize sizeHint () const override;

  void update_view ();

private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // MAIN_WINDOW_H
