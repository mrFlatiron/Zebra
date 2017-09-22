#ifndef STICKER_BODY_COLLAPSED_H
#define STICKER_BODY_COLLAPSED_H

#include <QFrame>
#include "frame_border_handler.h"

class QLabel;
class sticker_button;

class sticker_body_collapsed : public QFrame
{
  Q_OBJECT
private:
  QLabel *m_title;
  QLabel *m_hashtags;
  sticker_button *m_next_button;
  frame_border_handler m_borders;
public:
  sticker_body_collapsed (QWidget *parent = nullptr);
  ~sticker_body_collapsed ();

  QSize sizeHint () const override;

  frame_border_handler &borders ();

  void mouseDoubleClickEvent (QMouseEvent *event) override;

signals:
  void double_clicked ();

private:
  void init ();

  void create_widgets ();
  void set_layout ();
  void make_connections ();

  QString hash_styled (const QString &str);
  QString title_styled (const QString &str);
};

#endif // STICKER_BODY_COLLAPSED_H
