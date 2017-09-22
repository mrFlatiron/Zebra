#include "sticker_icon.h"
#include "kernel/task_object.h"
#include "style_utils.h"

#include <QLabel>

sticker_icon::sticker_icon (QWidget *parent)
  : QLabel (parent)
{
  init ();
}

sticker_icon::~sticker_icon ()
{

}

void sticker_icon::init ()
{
  setAutoFillBackground (true);
  m_border_handler.set_parent (this);
  m_background_color = QColor (Qt::white);
  set_icon (style_settings::common_icons::clipboard);
}

void sticker_icon::apply ()
{
  setPixmap (m_pixmap);
  setAlignment (Qt::AlignCenter);
  QPalette pal = palette ();
  pal.setBrush (backgroundRole (), QBrush (m_background_color));
  setPalette (pal);
}

void sticker_icon::set_icon (const QString &path)
{
  set_icon (QPixmap (path));
//  m_icon = QPixmap (path);
//  setStyleSheet (QString ("background-image:%1").arg (path));
}

void sticker_icon::set_icon (const QPixmap &icon)
{
  m_pixmap = icon;
  apply ();
}

void sticker_icon::set_icon (style_settings::common_icons type)
{
  set_icon (style_settings::get_icon_path (type));
}

void sticker_icon::set_background_color(const QColor &color)
{
  m_background_color = color;
  apply ();
}

QSize sticker_icon::sizeHint() const
{
  return QSize (50, 50);
}

frame_border_handler &sticker_icon::borders ()
{
  return m_border_handler;
}


