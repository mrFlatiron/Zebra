#ifndef auto_sql_H
#define auto_sql_H


struct sqlite3;

enum class sql_open_policy
{
  create_if_not_exist,
  fail_if_not_exist,
  COUNT
};

class auto_sql
{
private:
  using self = auto_sql;
  using SOP = sql_open_policy;

  sqlite3 *m_handle = nullptr;
  std::string m_filename;
  bool m_is_opened = false;
  int m_last_error = SQLITE_OK;
public:
  auto_sql () = default;
  ~auto_sql ();

  auto_sql (std::string filename, SOP policy = SOP::create_if_not_exist);

  bool open (std::string filename, SOP policy = SOP::create_if_not_exist);

  bool close ();

  bool is_open () const;

  operator sqlite3 * () const;

};


#endif // auto_sql_H
