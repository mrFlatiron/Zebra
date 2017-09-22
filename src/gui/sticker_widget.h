#ifndef STICKER_WIDGET_H
#define STICKER_WIDGET_H

#include <QWidget>

class sticker_colorline;
class sticker_icon;
class sticker_body_collapsed;
class sticker_body_expanded;
class QGridLayout;

class sticker_widget : public QWidget
{
  Q_OBJECT
private:
  sticker_colorline *m_colorline;
  sticker_icon *m_icon;
  sticker_body_collapsed *m_body_collapsed;
  sticker_body_expanded *m_body_expanded;
  int m_preferred_height = 50;

  QGridLayout *m_main_layout;
public:
  sticker_widget (QWidget *parent = nullptr);
  ~sticker_widget ();
  QSize sizeHint () const override;

  void expand_body ();
private:
  void create_widgets ();
  void set_layout ();
  void make_connections ();
};

#endif // STICKER_WIDGET_H
