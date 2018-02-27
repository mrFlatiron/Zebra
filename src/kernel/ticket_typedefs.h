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

static inline std::string enum_to_string (ticket_priority p)
{
  switch (p)
    {
    case ticket_priority::low:
      return "low";
    case ticket_priority::mid:
      return "mid";
    case ticket_priority::high:
      return "high";
    case ticket_priority::COUNT:
      ASSERT_RETURN (false, "");
    }

  ASSERT_RETURN (false, "");
}

static inline std::string enum_to_string (ticket_type t)
{
  switch (t)
    {
    case ticket_type::feature:
      return "feature";
    case ticket_type::bug:
      return "bug";
    case ticket_type::question:
      return "question";
    case ticket_type::regular:
      return "regular";
    case ticket_type::COUNT:
      ASSERT_RETURN (false, "");
    }

  ASSERT_RETURN (false , "");
}

#endif // TICKET_TYPEDEFS_H
