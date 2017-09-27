#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>

class sticker_column;

class main_window : public QDialog
{
  Q_OBJECT
private:
  std::vector<sticker_column *> m_columns;
public:
  main_window (QWidget *parent = 0);
  ~main_window ();
  QSize sizeHint () const override;

private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // MAIN_WINDOW_H
