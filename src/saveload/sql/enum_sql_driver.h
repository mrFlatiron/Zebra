#ifndef ENUM_SQL_DRIVER_H
#define ENUM_SQL_DRIVER_H

#include "sqlite3/include/sqlite3.h"

#include "saveload/sql/enum_sql.h"

enum class enum_sql_open_policy
{
  create_if_not_exist,
  fail_if_not_exist,
  COUNT
};

template<typename Enum, typename = use_if_enum<Enum>>
class enum_sql_driver
{
private:
  using self = enum_sql_driver<Enum>;
  using ESOP = enum_sql_open_policy;

  sqlite3 *m_handle = nullptr;
  std::string m_filename;
  bool m_is_opened = false;
public:
  enum_sql_driver () = default;
  ~enum_sql_driver ()
  {
    close ();
  }

  enum_sql_driver (std::string filename, ESOP policy = ESOP::create_if_not_exist)
  {
    open (filename, policy);
  }

  bool open (std::string filename, ESOP policy = ESOP::create_if_not_exist)
  {
    if (!close ())
      return false;

    m_filename = filename;
    int flag_create = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    int error_code;
    switch (policy)
      {
      case ESOP::create_if_not_exist:
        error_code = sqlite3_open_v2 (m_filename.c_str (), &m_handle, flag_create, nullptr);
        break;
      case ESOP::fail_if_not_exist:
        error_code = sqlite3_open_v2 (m_filename.c_str (), &m_handle, SQLITE_OPEN_READWRITE, nullptr);
        break;
      case ESOP::COUNT:
        DEBUG_PAUSE ("Shouldn't happen");
        return;
      }
    if (m_handle && error_code == SQLITE_OK)
      m_is_opened = true;
    else
      m_is_opened = false;

    return m_is_opened;
  }

  bool close ()
  {
    if (!is_open ())
      return true;

    if (SQLITE_OK == sqlite3_close_v2 (m_handle))
      {
        m_handle = nullptr;
        m_is_opened = false;
        return true;
      }

    return false;
  }

  bool is_open () const
  {
    return m_is_opened;
  }

};


#endif // ENUM_SQL_DRIVER_H
