#include "auto_sql.h"
#include "sqlite3/include/sqlite3.h"

auto_sql::~auto_sql ()
{
  close ();
}

auto_sql::auto_sql (std::string filename, auto_sql::SOP policy)
{
  open (filename, policy);
}

bool auto_sql::open (std::string filename, auto_sql::SOP policy)
{
  if (!close ())
    return false;

  m_filename = filename;
  int flag_create = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  switch (policy)
    {
    case SOP::create_if_not_exist:
      m_last_error = sqlite3_open_v2 (m_filename.c_str (), &m_handle, flag_create, nullptr);
      break;
    case SOP::fail_if_not_exist:
      m_last_error = sqlite3_open_v2 (m_filename.c_str (), &m_handle, SQLITE_OPEN_READWRITE, nullptr);
      break;
    case SOP::COUNT:
      DEBUG_PAUSE ("Shouldn't happen");
      return;
    }
  if (m_handle && m_last_error == SQLITE_OK)
    m_is_opened = true;
  else
    m_is_opened = false;

  return m_is_opened;
}

bool auto_sql::close ()
{
  if (!is_open ())
    return true;

  m_last_error = sqlite3_close_v2 (m_handle);

  if (SQLITE_OK == m_last_error)
    {
      m_handle = nullptr;
      m_is_opened = false;
      return true;
    }

  return false;
}

bool auto_sql::is_open () const
{
  return m_is_opened;
}

auto_sql::operator sqlite3 *() const
{
  return m_handle;
}
