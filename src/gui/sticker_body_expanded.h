#ifndef STICKER_BODY_EXPANDED_H
#define STICKER_BODY_EXPANDED_H

#include <QFrame>
#include "kernel/ticket_ptr.h"

class QTextEdit;
class QLabel;
class QPushButton;
class QLineEdit;
class sticker_button;
class QToolButton;
class QToolBar;

class sticker_body_expanded : public QFrame
{
private:
  QLabel *m_title_lbl;
  QLineEdit *m_title;
  QLabel *m_desc_lbl;
  QTextEdit *m_desc;

//  sticker_button *m_apply_pb;
  QToolButton *m_apply_pb;
  QToolBar *m_apply_toolbar;

  ticket_ptr m_ticket;

  sig::connector m_conn;
public:
  sticker_body_expanded (QWidget *parent = nullptr);
  ~sticker_body_expanded ();

  QSize sizeHint () const override;

  void set_ticket (ticket_ptr ticket);
  void update_view ();

  sig::signal<> apply_clicked;

  void on_apply_clicked ();
  void apply ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();


};

#endif // STICKER_BODY_EXPANDED_H
