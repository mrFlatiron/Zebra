#include "frame_borders.h"
#include <QFrame>
#include <QMargins>

#include "common/enum_range.h"


void frame_borders::set_visible_borders (QFrame *frame, const std::vector<frame_border> &borders)
{
  frame->setContentsMargins (construct_margins (borders, frame->lineWidth ()));
}

void frame_borders::set_invisible_borders (QFrame *frame, const std::vector<frame_border> &borders)
{
  std::vector<frame_border> visible_borders;
  for (auto b : enum_range<frame_border> ())
    {
      if (std::find (borders.begin (), borders.end (), b) == borders.end ())
        visible_borders.emplace_back (b);
    }

  frame->setContentsMargins (construct_margins (visible_borders, frame->lineWidth ()));
}

void frame_borders::set_width (QFrame *frame, int line_width, int mid_line_width)
{
  frame->setLineWidth (line_width);
  frame->setMidLineWidth (mid_line_width);
}

void frame_borders::set_shape (QFrame *frame, QFrame::Shape shape)
{
  frame->setFrameShape (shape);
}

void frame_borders::set_shadow (QFrame *frame, QFrame::Shadow shadow)
{
  frame->setFrameShadow (shadow);
}

QMargins frame_borders::construct_margins (const std::vector<frame_border> &borders, int line_width)
{
  QMargins marg;
  for (auto b : borders)
    {
      switch (b)
        {
        case frame_border::left:
          marg.setLeft (line_width);
          break;
        case frame_border::top:
          marg.setTop (line_width);
          break;
        case frame_border::right:
          marg.setRight (line_width);
          break;
        case frame_border::bottom:
          marg.setBottom (line_width);
          break;
        case frame_border::COUNT:
          ASSERT_RETURN (false, QMargins ());
        }
    }
  return marg;
}
