#ifndef STICKER_BODY_EXPANDED_H
#define STICKER_BODY_EXPANDED_H

#include <QFrame>
#include "frame_border_handler.h"
#include "kernel/ticket_ptr.h"

class QTextEdit;
class QLabel;
class QPushButton;

class sticker_body_expanded : public QFrame
{
  Q_OBJECT
private:
  frame_border_handler m_borders;

  QLabel *m_title_lbl;
  QTextEdit *m_title;
  QLabel *m_desc_lbl;
  QTextEdit *m_desc;

  QPushButton *m_apply_pb;

  ticket_ptr m_ticket;
public:
  sticker_body_expanded (QWidget *parent = nullptr);
  ~sticker_body_expanded ();

  frame_border_handler &borders ();

  QSize sizeHint () const override;

  void set_ticket (ticket_ptr ticket);
  void update_view ();

  sig::signal<> apply_clicked;
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();

  Q_SLOT void on_apply ();
};

#endif // STICKER_BODY_EXPANDED_H
