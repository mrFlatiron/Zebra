#ifndef STICKER_COLUMN_INTERNAL_H
#define STICKER_COLUMN_INTERNAL_H

#include <QLabel>
#include <QScrollArea>
#include "kernel/ticket_typedefs.h"
#include "sig/sigslots.h"
#include "containers/special/indexed_emplacer.h"

class sticker_widget;
class QScrollArea;
class QVBoxLayout;
class columns_handler;
class ticket_container;
class column_display_proxy_abstract;

class sticker_column_internal : public QLabel
{
  Q_OBJECT
private:
  indexed_emplacer<ticket_id, sticker_widget> m_stickers;

  column_id m_col_id;
  columns_handler &m_columns;
  ticket_container &m_tickets;
  column_display_proxy_abstract *m_proxy_model = nullptr;

  bool m_is_last = false;
  bool m_is_first = false;

  sig::connector m_conn;
public:
  sticker_column_internal (ticket_container &tickets, columns_handler &columns, column_id col_id, QWidget *parent = nullptr);
  ~sticker_column_internal ();


  QSize sizeHint () const override;

  void set_col_id (column_id id);
  column_id col_id () const;
  void update_view ();
  void set_model (column_display_proxy_abstract *model);

  columns_handler &columns ();
  const columns_handler &columns () const;

  ticket_container &tickets ();
  const ticket_container &tickets () const;

  void set_is_last (bool val = true);
  void set_is_first (bool val = true);

  sig::signal<ticket_id> transfer_to_next_requested;
  sig::signal<ticket_id> transfer_to_prev_requested;
  sig::signal<ticket_id> deletion_requested;
private:
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_COLUMN_INTERNAL_H
