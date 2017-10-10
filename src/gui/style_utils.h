#ifndef STYLE_UTILS_H
#define STYLE_UTILS_H

#include <QString>
#include <QColor>

class QWidget;

enum class common_colors
{
  peach,
  cream,
  mint,
  lightblue,
  lilac,
  cloud,
  red,
  green,
  yellow,
  orange,
  COUNT
};

namespace style_settings
{
  const int collapsed_height = 80;

  enum class styled_string
  {
    title,
    hash,
    COUNT
  };

  enum class common_icons
  {
    bug,
    lamp,
    clipboard,
    question_mark,
    r_arrow,
    trash,
    check_mark,
    plus,
    COUNT
  };



  QString get_styled_string (const QString &src, styled_string obj);
  QString get_icon_path (common_icons type);
  QColor get_color (common_colors color);

  void set_background_color (QWidget *widget, const QColor &color);
  void set_background_color (QWidget *widget, common_colors color);
}
#endif // STYLE_UTILS_H
