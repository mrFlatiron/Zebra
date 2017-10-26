#ifndef STICKER_BODY_COLLAPSED_H
#define STICKER_BODY_COLLAPSED_H

#include <QFrame>
#include "frame_border_handler.h"
#include "sig/sigslots.h"
#include "kernel/ticket_ptr.h"

class QLabel;
class sticker_button;

class sticker_body_collapsed : public QFrame
{
private:
  QLabel *m_title;
  QLabel *m_hashtags;
  sticker_button *m_next_button;
  frame_border_handler m_borders;

  ticket_ptr m_ticket;

  bool m_next_is_deletion = true; //arrow or trash bin

  sig::connector m_conn;
public:
  sticker_body_collapsed (QWidget *parent = nullptr);
  ~sticker_body_collapsed ();

  QSize sizeHint () const override;
  QSize minimumSizeHint () const override;

  frame_border_handler &borders ();

  void mouseDoubleClickEvent (QMouseEvent *event) override;

  void set_ticket (ticket_ptr ticket);
  void set_next_is_deletion (bool val);
  bool next_is_deletion () const;

  void update_view ();
  sig::signal<> double_clicked;
  sig::signal<> next_button_clicked;
private:
  void init ();

  void create_widgets ();
  void set_layout ();
  void make_connections ();

  QString hash_styled (const QString &str);
  QString title_styled (const QString &str);
};

#endif // STICKER_BODY_COLLAPSED_H
