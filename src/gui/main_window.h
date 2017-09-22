#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>

class main_window : public QDialog
{
  Q_OBJECT

public:
  main_window (QWidget *parent = 0);
  ~main_window ();
  QSize sizeHint () const override;
};

#endif // MAIN_WINDOW_H
