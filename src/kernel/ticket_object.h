#ifndef TICKET_OBJECT_H
#define TICKET_OBJECT_H

enum class ticket_priority
{
  low,
  mid,
  high,
  COUNT
};

enum class ticket_type
{
  feature,
  bug,
  question,
  regular,
  COUNT
};

class ticket_object
{
private:
  QString m_title;
  QString m_description;
  ticket_type m_type;
  ticket_priority m_priority;
  int m_dep_component;
public:
  ticket_object ();
  ~ticket_object ();

  void set_title (const QString &str);
  void set_description (const QString &str);
  void set_type (const ticket_type t);
  void set_priority (const ticket_priority p);

  QString title () const;
  QString description () const;
  ticket_type type () const;
  ticket_priority priority () const;
};

#endif // TICKET_OBJECT_H
