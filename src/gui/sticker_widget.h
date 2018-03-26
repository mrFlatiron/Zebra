#ifndef STICKER_WIDGET_H
#define STICKER_WIDGET_H

#include <QWidget>
#include <QFrame>
#include "sig/sigslots.h"
#include "kernel/ticket_ptr.h"
#include "containers/enum_vector.h"


class sticker_colorline;
class sticker_icon;
class sticker_body_collapsed;
class sticker_body_expanded;
class QGridLayout;
class QVBoxLayout;
class QMenu;
class QAction;

class widget_visibility_updater;

class sticker_widget : public QFrame
{
  Q_OBJECT
private:
  sticker_colorline *m_colorline;
  sticker_icon *m_icon;
  QMenu *m_ticket_type_menu;
  QMenu *m_priority_menu;
  enum_vector<ticket_type, QAction *> m_ticket_type_actions;
  enum_vector<ticket_priority, QAction *> m_priority_actions;
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
  sig::signal<> prev_button_clicked;

  void resize_body ();
  void set_ticket (ticket_ptr ticket);
  void update_view ();

  void set_next_is_deletion (bool val);
  bool next_is_deletion () const;

  void set_prev_button_disabled (bool val = true);
  bool is_prev_button_disabled () const;
private:
  void create_widgets ();
  void set_layout ();
  void make_connections ();
  void set_dirty ();
  Q_SLOT void change_icon_via_menu (QAction *action);
  Q_SLOT void change_colorline_via_menu (QAction *action);
};

#endif // STICKER_WIDGET_H
