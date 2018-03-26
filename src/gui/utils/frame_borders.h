#ifndef FRAME_BORDERS_H
#define FRAME_BORDERS_H

#include <QFrame>
#include <QMargins>

class QFrame;

enum class frame_border
{
  left,
  top,
  right,
  bottom,
  COUNT
};

class frame_borders
{
public:
  static void set_visible_borders (QFrame *frame, const std::vector<frame_border> &borders);
  static void set_invisible_borders (QFrame *frame, const std::vector<frame_border> &borders);
  static void set_width (QFrame *frame, int line_width = 1, int mid_line_width = 0);
  static void set_shape (QFrame *frame, QFrame::Shape shape);
  static void set_shadow (QFrame *frame, QFrame::Shadow shadow);
  static void set_mid_width (QFrame *frame, int mid_width);
private:
  static QMargins construct_margins (const std::vector<frame_border> &borders, int line_width);
};

#endif // FRAME_BORDERS_H
