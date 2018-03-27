#ifndef STYLE_UTILS_H
#define STYLE_UTILS_H

#include <QString>
#include <QColor>

class QWidget;

enum class common_colors
{
  white,
  peach,
  cream,
  mint,
  white_blue,
  lightblue,
  lilac,
  cloud,
  red,
  green,
  yellow,
  orange,
  COUNT
};

enum class ticket_priority;
enum class ticket_type;

namespace style_utils
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
    l_arrow,
    trash,
    check_mark,
    plus,
    collapse_left,
    settings,
    black_plus,
    x_mark,
    COUNT
  };



  QString get_styled_string (const QString &src, styled_string obj);
  QString get_icon_path (common_icons type);
  QColor get_color (common_colors color);
  common_icons type_to_icon (ticket_type p);

  void set_background_color (QWidget *widget, const QColor &color);
  void set_background_color (QWidget *widget, common_colors color);
  void set_edits_background_color (QWidget *widget, const QColor &color);
  void set_edits_background_color (QWidget *widget, common_colors color);
}
#endif // STYLE_UTILS_H
