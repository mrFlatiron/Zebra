#include "style_utils.h"
#include <QWidget>

#include "kernel/ticket_typedefs.h"

QString style_settings::get_styled_string (const QString &src, styled_string obj)
{
  switch (obj)
    {
    case styled_string::title:
      return QString ("<h4><b>%1</b></h4>").arg (src);
    case styled_string::hash:
      return QString ("<p><span style=\"color: %1;\"><strong><em>%2</em></strong></span></p>")
          .arg (QColor (86, 82, 82).name (QColor::HexRgb), src);
    case styled_string::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
      return "";
    }
  return "";
}

QString style_settings::get_icon_path (style_settings::common_icons type)
{
  switch (type)
    {
    case common_icons::bug:
      return ":/icons/bug3_32.png";
    case common_icons::check_mark:
      return ":/icons/check_mark.png";
    case common_icons::clipboard:
      return ":/icons/clipboard_32.png";
    case common_icons::lamp:
      return ":/icons/lamp_32.png";
    case common_icons::question_mark:
      return ":/icons/question_mark_32.png";
    case common_icons::r_arrow:
      return ":/icons/r_arrow.png";
    case common_icons::trash:
      return ":/icons/trash.png";
    case common_icons::plus:
      return ":/icons/plus.png";
    case common_icons::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
    }
  return "";
}

QColor style_settings::get_color (common_colors color)
{
  switch (color)
    {
    case common_colors::white:
      return QColor (255, 255, 255);
    case common_colors::peach:
      return QColor (248, 203, 173);
    case common_colors::cream:
      return QColor (255, 230, 153);
    case common_colors::mint:
      return QColor (197, 224, 180);
    case common_colors::lightblue:
      return QColor (189, 215, 238);
    case common_colors::lilac:
      return QColor (217, 179, 255);
    case common_colors::cloud:
      return QColor (217, 217, 217);
    case common_colors::red:
      return QColor (255, 0, 0);
    case common_colors::green:
      return QColor (112, 173, 71);
    case common_colors::yellow:
      return QColor (255, 192, 0);
    case common_colors::orange:
      return QColor (246, 182, 99);
    case common_colors::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
    }
  return QColor ();
}

void style_settings::set_background_color (QWidget *widget, const QColor &color)
{
  QPalette pal = widget->palette ();
  pal.setBrush (widget->backgroundRole (), QBrush (color));
  widget->setPalette (pal);
}

void style_settings::set_edits_background_color (QWidget *widget, const QColor &color)
{
  QPalette pal = widget->palette ();
  pal.setBrush (QPalette::Base, QBrush (color));
  widget->setPalette (pal);
}

void style_settings::set_background_color (QWidget *widget, common_colors color)
{
  set_background_color (widget, get_color (color));
}

style_settings::common_icons style_settings::type_to_icon (ticket_type p)
{
  switch (p)
    {
    case ticket_type::bug:
      return common_icons::bug;
    case ticket_type::feature:
      return common_icons::lamp;
    case ticket_type::question:
      return common_icons::question_mark;
    case ticket_type::regular:
      return common_icons::clipboard;
    case ticket_type::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
    }
  return common_icons::COUNT;
}

void style_settings::set_edits_background_color(QWidget *widget, common_colors color)
{
  set_edits_background_color (widget, get_color (color));
}
