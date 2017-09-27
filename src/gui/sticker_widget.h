#ifndef STICKER_WIDGET_H
#define STICKER_WIDGET_H

#include <QWidget>

class sticker_colorline;
class sticker_icon;
class sticker_body_collapsed;
class sticker_body_expanded;
class frame_border_handler;
class QGridLayout;
class QVBoxLayout;

class sticker_widget : public QWidget
{
  Q_OBJECT
private:
  using fbh = frame_border_handler;

  sticker_colorline *m_colorline;
  sticker_icon *m_icon;
  sticker_body_collapsed *m_body_collapsed;
  sticker_body_expanded *m_body_expanded;

  bool m_is_expanded;

  QVBoxLayout *m_main_layout;
public:
  sticker_widget (QWidget *parent = nullptr);
  ~sticker_widget ();
  QSize sizeHint () const override;

  QSize minimumSizeHint () const override;
public slots:
  void resize_body ();
signals:
  void body_expanded ();
  void body_collapsed ();
private:
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_WIDGET_H
