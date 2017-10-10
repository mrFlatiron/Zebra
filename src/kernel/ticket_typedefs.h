#ifndef TICKET_TYPEDEFS_H
#define TICKET_TYPEDEFS_H

using ticket_id = int;
using column_id = int;

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

#endif // TICKET_TYPEDEFS_H
