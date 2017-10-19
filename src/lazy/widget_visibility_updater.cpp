#include "widget_visibility_updater.h"
#include <QWidget>
#include <QEvent>

widget_visibility_updater::widget_visibility_updater ()
{

}

widget_visibility_updater::~widget_visibility_updater ()
{

}

void widget_visibility_updater::set_widget_and_updater (QWidget *widget, const std::function<void ()> &updater)
{
  m_widget_to_watch = widget;
  if (!widget)
    return;
  m_widget_to_watch->installEventFilter (this);
  m_updater_func = updater;
}

bool widget_visibility_updater::eventFilter (QObject *watched, QEvent *event)
{
  if (event->type () == QEvent::Paint ||
      event->type () == QEvent::Resize ||
      event->type () == QEvent::Show)
    {
      if (is_dirty ())
        m_updater_func ();

      set_uptodate ();
    }
  return QObject::eventFilter (watched, event);
}

bool widget_visibility_updater::is_dirty () const
{
  return m_is_dirty;
}

void widget_visibility_updater::set_dirty ()
{
  m_is_dirty = true;
}

void widget_visibility_updater::set_uptodate ()
{
  m_is_dirty = false;
}
