#ifndef TICKET_TYPEDEFS_H
#define TICKET_TYPEDEFS_H

#include "common/typesafe_id.h"

MAKE_TYPESAFE_ID (ticket_id, int);
MAKE_TYPESAFE_ID (column_id, int);
MAKE_TYPESAFE_ID (ticket_col_id, int);

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
