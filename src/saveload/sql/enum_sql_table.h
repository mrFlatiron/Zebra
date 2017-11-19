#ifndef ENUM_SQL_TABLE_H
#define ENUM_SQL_TABLE_H

#include "common/enum_misc.h"
#include "enum_sql_insert_stmt.h"
#include "enum_sql_select_stmt.h"

enum class sql_insert_policy
{
  replace,
  rollback,
  ignore,
  abort,
  fail,
  COUNT
};

enum class sql_data_type
{
  INTEGER,
  REAL,
  TEXT,
  BLOB,
  Null,
  COUNT
};

std::string enum_to_string (sql_insert_policy e)
{
  switch (e)
    {
    case sql_insert_policy::replace:
      return "REPLACE";
    case sql_insert_policy::rollback:
      return "ROLLBACK";
    case sql_insert_policy::ignore:
      return "IGNORE";
    case sql_insert_policy::fail:
      return "FAIL";
    case sql_insert_policy::abort:
      return "ABORT";
    case sql_insert_policy::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
      return "";
    }
  return "";
}

std::string enum_to_string (sql_data_type t)
{
  switch (t)
    {
    case sql_data_type::INTEGER:
      return "INTEGER";
    case sql_data_type::REAL:
      return "REAL";
    case sql_data_type::TEXT:
      return "TEXT";
    case sql_data_type::BLOB:
      return "BLOB";
    case sql_data_type::Null:
      return "NULL";
    case sql_data_type::COUNT:
      DEBUG_PAUSE("Shouldn't happen");
      return "";
    }
  return "";
}

template<typename Enum, typename = use_if_enum<Enum>>
class enum_sql_table
{
public:
  enum_sql_table () = default;
  virtual ~enum_sql_table () = default;
public:
  virtual sql_data_type column_type (Enum)  const    = 0;
  virtual std::string column_name (Enum)  const    = 0;
  virtual std::string table_name ()       const    = 0;


  virtual std::string table_constr(Enum)  const {return "";}
  virtual std::string schema_name ()      const {return "";}
  virtual bool is_skipped (Enum)          const {return false;}

public:
  enum_sql_select_stmt select_stmt (const std::vector<Enum> &cols) const
  {
    std::string cols_to_select;

    bool is_first = true;
    for (Enum e : cols)
      {
        if (!is_first)
          {
            cols_to_select.append (", ");
          }
        cols_to_select.append (column_name (e));
        is_first = false;
      }
    std::string stmt = "SELECT (";
    stmt.append (cols_to_select);
    stmt.append (") ");
    stmt.append ("FROM ");
    stmt.append (full_table_name ());

    enum_sql_select_stmt<Enum> retval (cols);
    retval.set_stmt (stmt);
    return retval;
  }

  auto_sql_stmt drop_stmt () const
  {
    std::string stmt = "DROP TABLE ";
    stmt.append (full_table_name ());

    return stmt;
  }

  enum_sql_insert_stmt<Enum> insert_stmt (const std::vector<Enum> &cols, sql_insert_policy policy) const
  {
    std::string stmt = "INSERT OR ";
    stmt.append (enum_to_string (policy));
    stmt.append (" INTO ");
    stmt.append (full_table_name ());
    stmt.append (" (");

    std::string q_marks = "(";
    bool is_first = true;
    for (auto col : cols)
      {
        if (!is_first)
          {
            stmt.append (", ");
            q_marks.append (", ");
          }
        stmt.append (column_name (col));
        q_marks.append ("?");
        is_first = false;
      }
    stmt.append (") VALUES ");
    q_marks.append (")");
    stmt.append (q_marks);

    return stmt;
  }

  auto_sql_stmt create_stmt () const
  {
    std::string stmt = "CREATE TABLE ";
    stmt.append (full_table_name ());
    stmt.append (" (");

    bool is_first = true;
    for (auto e : enum_range<Enum> ())
      {
        if (is_skipped (e))
          continue;

        if (!is_first)
          {
            stmt.append (",\n");
          }
        stmt.append (full_column_def (e));
        is_first = false;
      }

    stmt.append (")");
    return stmt;
  }
  auto_sql_stmt set_sync_pragma_stmt (bool is_on) const
  {
    std::string stmt = "PRAGMA ";
    stmt.append (schema_name ());
    if (!schema_name ().empty ())
      stmt.append (".");
    stmt.append ("synchronous ");
    stmt.append ("= ");
    if (is_on)
      stmt.append ("NORMAL");
    else
      stmt.append ("OFF");

    return stmt;
  }
  std::string full_table_name () const
  {
    std::string stmt;
    stmt.append (schema_name ());
    if (!schema_name ().empty ())
        stmt.append (".");
    stmt.append (table_name ());
    return stmt;
  }
protected:
  std::string full_column_def (Enum e) const
  {
    std::string def;
    def.append (column_name (e));
    def.append (" ");
    def.append (enum_to_string (column_type (e)));
    if (!table_constr (e).empty ())
      def.append (" ");
    def.append (table_constr (e));

    return def;
  }
};


#endif // ENUM_SQL_TABLE_H
