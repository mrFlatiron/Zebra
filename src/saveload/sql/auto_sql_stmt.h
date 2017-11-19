#ifndef AUTO_SQL_STMT_H
#define AUTO_SQL_STMT_H

struct sqlite3_stmt;
class auto_sql;

class auto_sql_stmt
{
protected:
  sqlite3_stmt *m_stmt = nullptr;
  auto_sql *m_db = nullptr;
  std::string m_stmt_string;
  int m_status = 0;
  bool m_is_prepared = false;
public:
  auto_sql_stmt () = default;
  virtual ~auto_sql_stmt ();

  auto_sql_stmt (auto_sql *db, const std::string &stmt_string);

  auto_sql_stmt (const auto_sql_stmt &rhs) = default;
  auto_sql_stmt &operator= (const auto_sql_stmt &rhs) = default;

  auto_sql_stmt (auto_sql_stmt &&rhs);
  auto_sql_stmt &operator= (auto_sql_stmt &&rhs);

  void set_db (auto_sql *db);
  void set_stmt (const std::string &stmt);

  bool prepare ();

  bool is_prepared () const;
  int status () const;

  virtual bool execute ();
};

#endif // AUTO_SQL_STMT_H
