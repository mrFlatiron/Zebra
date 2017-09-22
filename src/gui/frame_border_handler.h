#ifndef FRAME_BORDER_HANDLER_H
#define FRAME_BORDER_HANDLER_H

#include "containers/enum_bitset.h"
#include <QMargins>

#include <QFrame>

class frame_border_handler
{
public:
  enum class border
  {
    left,
    top,
    right,
    bottom,
    COUNT
  };

private:
  QFrame *m_parent;
  int m_border_width;
  int m_border_mid_width;
  QFrame::Shape m_shape;
  QFrame::Shadow m_shadow;
  enum_bitset<border> m_borders_visible;
public:
  frame_border_handler (QFrame *parent = nullptr); //it is not a 'QObject system'-like parent. Wont be destroyed when parent gets destroyed
  ~frame_border_handler ();

  void set_width (const int width, const int mid_width = 2);
  void set_shape (QFrame::Shape shape);
  void set_shadow (QFrame::Shadow shadow);
  void set_parent (QFrame *parent);
  void set_mid_width (const int mid_width);
  void hide_borders (const std::vector<border> &borders);
  void show_borders (const std::vector<border> &borders);
private:
  void apply ();
  QMargins construct_margins ();
};

#endif // FRAME_BORDER_HANDLER_H
