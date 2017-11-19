#include "auto_sql_stmt.h"
#include "auto_sql.h"
#include "sqlite3/include/sqlite3.h"

auto_sql_stmt::~auto_sql_stmt ()
{
  if (is_prepared ())
    m_status = sqlite3_finalize (m_stmt);

  if (m_status != SQLITE_OK)
    DEBUG_PAUSE ("Something went wrong");
}

auto_sql_stmt::auto_sql_stmt (auto_sql *db, const std::string &stmt_string)
{
  set_db (db);
  set_stmt (stmt_string);
  prepare ();
}

auto_sql_stmt::auto_sql_stmt (auto_sql_stmt &&rhs)
{
  *this = std::move (rhs);
}

auto_sql_stmt &auto_sql_stmt::operator= (auto_sql_stmt &&rhs)
{
  m_stmt = rhs.m_stmt;
  m_db = rhs.m_db;
  m_stmt_string = std::move (rhs.m_stmt);
  m_status = rhs.m_status;
  m_is_prepared = rhs.m_is_prepared;
}

void auto_sql_stmt::set_db (auto_sql *db)
{
  m_db = db;
}

void auto_sql_stmt::set_stmt (const std::string &stmt)
{
  m_stmt_string = stmt;
}

bool auto_sql_stmt::prepare ()
{
  if (!m_db || !m_db->is_open ())
    {
      m_stmt = nullptr;
      m_is_prepared = false;
      m_status = SQLITE_ERROR;
      return;
    }
  const char *tail;
  m_status = sqlite3_prepare_v2 (db, m_stmt_string.c_str (), m_stmt_string.length (), &m_stmt, &tail);
  if (m_status == SQLITE_OK && m_stmt)
    m_is_prepared = true;
  else
    m_is_prepared = false;

  return m_is_prepared;
}

bool auto_sql_stmt::is_prepared () const
{
  return m_is_prepared && m_db && m_db->is_open ();
}

int auto_sql_stmt::status () const
{
  return m_status;
}

bool auto_sql_stmt::execute ()
{
  if (!is_prepared ())
    return false;

  m_status = sqlite3_step (m_stmt);

  if (m_status == SQLITE_ROW
      || m_status == SQLITE_DONE)
    return true;
}
