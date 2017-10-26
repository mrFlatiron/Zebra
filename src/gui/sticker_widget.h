#ifndef STICKER_WIDGET_H
#define STICKER_WIDGET_H

#include <QWidget>
#include "sig/sigslots.h"
#include "kernel/ticket_ptr.h"


class sticker_colorline;
class sticker_icon;
class sticker_body_collapsed;
class sticker_body_expanded;
class frame_border_handler;
class QGridLayout;
class QVBoxLayout;

class widget_visibility_updater;

class sticker_widget : public QWidget
{
private:
  using fbh = frame_border_handler;

  sticker_colorline *m_colorline;
  sticker_icon *m_icon;
  sticker_body_collapsed *m_body_collapsed;
  sticker_body_expanded *m_body_expanded;

  std::unique_ptr<widget_visibility_updater> m_visibility_updater;

  ticket_ptr m_ticket;
  bool m_is_expanded;


  QVBoxLayout *m_main_layout;

  sig::connector m_conn;
public:
  sticker_widget (QWidget *parent = nullptr);
  ~sticker_widget ();
  QSize sizeHint () const override;

  QSize minimumSizeHint () const override;

  sig::signal<> body_expanded;
  sig::signal<> body_collapsed;
  sig::signal<> next_button_clicked;

  void resize_body ();
  void set_ticket (ticket_ptr ticket);
  void update_view ();

  void set_next_is_deletion (bool val);
  bool next_is_deletion () const;
private:
  void create_widgets ();
  void set_layout ();
  void make_connections ();
  void set_dirty ();
};

#endif // STICKER_WIDGET_H
