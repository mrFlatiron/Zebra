#ifndef STICKER_ICON_H
#define STICKER_ICON_H

#include <QPixmap>
#include <QLabel>
#include <QColor>
#include "frame_border_handler.h"
#include "sig/sigsignal.h"

#include <QToolButton>

enum class ticket_type;
enum class priority;

namespace style_utils
{
  QString task_type_to_icon_path (ticket_type type);

  enum class common_icons;
}

class sticker_icon : public QLabel
{
protected:
  QPixmap m_pixmap;

  frame_border_handler m_border_handler;
  QColor m_background_color;
public:
  sticker_icon (QWidget *parent = nullptr);
  virtual ~sticker_icon ();


  void set_icon (const QString &path);
  void set_icon (const QPixmap &icon);
  void set_icon (style_utils::common_icons type);
  void set_icon (ticket_type t);

  void set_background_color (const QColor &color);

  QSize sizeHint () const override;
  QSize minimumSizeHint () const override;

  frame_border_handler &borders ();

  sig::signal<> right_clicked;

  void mouseReleaseEvent (QMouseEvent *ev) override;
private:
  void init ();
  void apply ();
};

#endif // STICKER_ICON_H
