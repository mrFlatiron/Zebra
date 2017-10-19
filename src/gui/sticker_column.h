#ifndef STICKER_COLUMN_H
#define STICKER_COLUMN_H

#include <QLabel>
#include "frame_border_handler.h"
#include "kernel/ticket_typedefs.h"
#include "sig/sigslots.h"

class sticker_column_internal;
class sticker_button;
class ticket_container;
class columns_handler;
class column_display_proxy_abstract;

class sticker_column : public QLabel
{
private:
  frame_border_handler m_borders;
  sticker_column_internal *m_internal;
  sticker_button *m_add_button;


  sig::connector m_conn;
public:
  sticker_column (ticket_container &tickets, columns_handler &columns, column_id id, QWidget *parent = nullptr);
  ~sticker_column ();

  frame_border_handler &borders ();
  QSize minimumSizeHint () const;

  void set_col_id (column_id id);
  column_id col_id () const;

  void set_model (column_display_proxy_abstract *model);
  void update_view ();

  ticket_container &tickets ();
  const ticket_container &tickets () const;

  columns_handler &columns ();
  const columns_handler &columns () const;

  sig::signal<ticket_id> transfer_to_next_requested;
private:
  void init ();
  void create_widgets (ticket_container &tickets, columns_handler &columns, column_id id);
  void set_layout ();
  void make_connections ();
  void add_ticket ();


};

#endif // STICKER_COLUMN_H
