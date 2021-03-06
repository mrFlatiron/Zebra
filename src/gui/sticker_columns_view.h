#ifndef STICKER_COLUMNS_VIEW_H
#define STICKER_COLUMNS_VIEW_H

#include "sig/sigslots.h"
#include "kernel/ticket_typedefs.h"
#include <QLabel>
#include "containers/special/indexed_emplacer.h"

class mw_columns_display_proxy_abstract;
class column_display_proxy;
class sticker_column;
class ticket_container;
class columns_handler;

class QSplitter;
class QHBoxLayout;

class sticker_columns_view : public QLabel
{
private:
  ticket_container &m_tickets;
  columns_handler &m_columns;

  QHBoxLayout *m_hlo_0 = nullptr;
  QSplitter *m_spl_0 = nullptr;

  indexed_emplacer<column_id, sticker_column> m_columns_widgets;
  indexed_emplacer<column_id, column_display_proxy> m_models;

  mw_columns_display_proxy_abstract *m_model = nullptr;

  sig::connector m_conn;
public:
  sticker_columns_view (ticket_container &tickets,
                        columns_handler &columns,
                        QWidget *parent = nullptr);
  ~sticker_columns_view ();

  void set_model (mw_columns_display_proxy_abstract *model);

  void update_view ();

  ticket_container &tickets ();
  columns_handler &columns ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
  void transfer_to_next_column (ticket_id tid, column_id from);
  void transfer_to_prev_column (ticket_id tid, column_id from);
  void delete_ticket (ticket_id tid, column_id cur_col_id);
};

#endif // STICKER_COLUMNS_VIEW_H
