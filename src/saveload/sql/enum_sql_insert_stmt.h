#ifndef ENUM_SQL_INSERT_STMT_H
#define ENUM_SQL_INSERT_STMT_H

#include "auto_sql_stmt.h"
#include "common/enum_misc.h"
#include "sqlite3/include/sqlite3.h"


template<typename Enum, typename = use_if_enum<Enum>>
class enum_sql_insert_stmt : public auto_sql_stmt
{
private:
  using self = enum_sql_insert_stmt<Enum>;
  using base = auto_sql_stmt;

  std::vector<Enum> m_cols;
  std::unordered_map<Enum, int> m_enum_to_int;
public:

  explicit enum_sql_insert_stmt (const std::vector<Enum> &cols)
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

  bool bind_value (Enum e, const void *byte_array, size_t size)
  {
    int p = pos (e);
    m_status = sqlite3_bind_blob (m_stmt, p, byte_array, size, SQLITE_TRANSIENT);
    if (m_status == SQLITE_OK)
      return true;
    else
      return false;
  }

  bool bind_value (Enum e, int value)
  {
    int p = pos (e);
    m_status = sqlite3_bind_int (m_stmt, p, value);
    if (m_status == SQLITE_OK)
      return true;
    else
      return false;
  }

  bool bind_value (Enum e, int64_t value)
  {
    int p = pos (e);
    m_status = sqlite3_bind_int64 (m_stmt, p, value);
    if (m_status == SQLITE_OK)
      return true;
    else
      return false;
  }

  bool bind_value (Enum e, double value)
  {
    int p = pos (e);
    m_status = sqlite3_bind_double (m_stmt, p, value);
    if (m_status == SQLITE_OK)
      return true;
    else
      return false;
  }

  bool bind_value (Enum e, const std::string &text)
  {
    int p = pos (e);
    m_status = sqlite3_bind_text (m_stmt, p, text.c_str (), text.length (), SQLITE_TRANSIENT);
    if (m_status == SQLITE_OK)
      return true;
    else
      return false;
  }

  bool bind_value (Enum e, const  std::nullptr_t)
  {
    int p = pos (e);
    m_status = sqlite3_bind_null (m_stmt, p);
    if (m_status == SQLITE_OK)
      return true;
    else
      return false;
  }

private:
  int pos (Enum e) const
  {
    auto it = m_enum_to_int.find (e);
    if (it == m_enum_to_int.end ())
      return 0;

    return it->second;
  }
};

#endif // ENUM_SQL_INSERT_STMT_H
