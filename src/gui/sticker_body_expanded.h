#ifndef STICKER_BODY_EXPANDED_H
#define STICKER_BODY_EXPANDED_H

#include <QFrame>
#include "frame_border_handler.h"

class QTextEdit;
class QLabel;

class sticker_body_expanded : public QFrame
{
private:
  frame_border_handler m_borders;

  QLabel *m_title_lbl;
  QTextEdit *m_title;
  QLabel *m_desc_lbl;
  QTextEdit *m_desc;
public:
  sticker_body_expanded (QWidget *parent = nullptr);
  ~sticker_body_expanded ();

  frame_border_handler &borders ();

  QSize sizeHint () const override;
private:
  void init ();
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_BODY_EXPANDED_H
