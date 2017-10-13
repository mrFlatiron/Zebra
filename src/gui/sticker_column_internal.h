#ifndef STICKER_COLUMN_INTERNAL_H
#define STICKER_COLUMN_INTERNAL_H

#include <QLabel>
#include <QScrollArea>
#include "frame_border_handler.h"
#include "kernel/ticket_typedefs.h"

class sticker_widget;
class QScrollArea;
class QVBoxLayout;
class columns_handler;
class ticket_container;

class sticker_column_internal : public QLabel
{
  Q_OBJECT
private:
  frame_border_handler m_borders;
  QVBoxLayout *m_vlo_0;

  column_id m_col_id;
  columns_handler &m_columns;
  ticket_container &m_tickets;
public:
  sticker_column_internal (columns_handler &columns, ticket_container &tickets, column_id col_id, QWidget *parent = nullptr);
  ~sticker_column_internal ();


  frame_border_handler &borders ();
  QSize sizeHint () const override;
  void update_view ();
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
private slots:
  void reset_layout ();
};

#endif // STICKER_COLUMN_INTERNAL_H
