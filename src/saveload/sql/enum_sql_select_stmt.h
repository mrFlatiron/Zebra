#ifndef ENUM_SQL_SELECT_STMT_H
#define ENUM_SQL_SELECT_STMT_H

#include "common/enum_misc.h"
#include "auto_sql_stmt.h"
#include "sqlite3/include/sqlite3.h"

enum class step_status
{
  ROW,
  DONE,
  FAIL,
  COUNT
};

template<typename Enum, typename = use_if_enum<Enum>>
class enum_sql_select_stmt : public auto_sql_stmt
{
private:
  using self = enum_sql_select_stmt<Enum>;
  using base = auto_sql_stmt;

  std::vector<Enum> m_cols;
  std::unordered_map<Enum, int> m_enum_to_int;

  step_status m_step_status = step_status::FAIL;
public:
  enum_sql_select_stmt () = default;
  ~enum_sql_select_stmt () = default;

  explicit enum_sql_select_stmt (const std::vector<Enum> &cols)
    : auto_sql_stmt ()
  {
    set_cols (cols);
  }

  void set_cols (const std::vector<Enum> &cols)
  {
    m_cols = cols;
    m_enum_to_int.clear ();

    for (int i = 0; i < isize (cols); i++)
      m_enum_to_int[cols[i]] = i + 1;
  }

  bool execute () override
  {
    if (step_status::FAIL != step ())
      return true;
    else
      return false;
  }

  step_status step ()
  {
    if (!is_prepared ())
      return step_status::FAIL;

    m_status = sqlite3_step (m_stmt);

    m_step_status = sqlite_to_enum_step_status (m_status);

    return m_step_status;
  }

private:
  static step_status sqlite_to_enum_step_status (int status)
  {
    switch (status)
      {
      case SQLITE_DONE:
        return step_status::DONE;
      case SQLITE_ROW:
        return step_status::ROW;
      case SQLITE_OK:
        DEBUG_PAUSE ("Shouldn't happen");
        return step_status::DONE;
      default:
      }
    return step_status::FAIL;
  }
};

#endif // ENUM_SQL_SELECT_STMT_H
