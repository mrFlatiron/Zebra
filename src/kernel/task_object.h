#ifndef TASK_OBJECT_H
#define TASK_OBJECT_H

enum class priority
{
  low,
  mid,
  high,
  COUNT
};

enum class task_type
{
  feature,
  bug,
  question,
  regular,
  COUNT
};

class task_object
{
public:
  task_object ();
  ~task_object ();
};

#endif // TASK_OBJECT_H
