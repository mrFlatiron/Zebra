#ifndef WIDGET_VISIBILITY_UPDATER_H
#define WIDGET_VISIBILITY_UPDATER_H

#include <QObject>

class QWidget;

class widget_visibility_updater : public QObject
{
private:
  QWidget *m_widget_to_watch = nullptr;
  std::function<void ()> m_updater_func;
  bool m_is_dirty = true;
public:
  widget_visibility_updater ();
  ~widget_visibility_updater ();

  void set_widget_and_updater (QWidget *widget,const std::function<void ()> &updater);

  bool eventFilter (QObject *watched, QEvent *event) override;

  bool is_dirty () const;
  void set_dirty ();
  void update ();
private:
  void set_uptodate ();
};

#endif // WIDGET_VISIBILITY_UPDATER_H
