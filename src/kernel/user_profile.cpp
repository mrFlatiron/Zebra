#include "user_profile.h"
#include "common/work/work.h"

user_profile::user_profile (user_profile_id id)
{
  m_id = id;
}

user_profile_id user_profile::id () const
{
  return m_id;
}

void user_profile::set_id (user_profile_id id)
{
  m_id = id;
}

QString user_profile::profile_name () const
{
  return m_profile_name;
}

void user_profile::set_profile_name (const QString &profile_name)
{
  m_profile_name = profile_name;
}

user_settings &user_profile::settings ()
{
  return m_settings;
}

const user_settings &user_profile::settings () const
{
  return m_settings;
}

bool user_profile::worker_process (work::xml_worker &worker)
{
  work::process (worker, m_profile_name, "profile_name");
  work::process (worker, m_id, "id");
  work::process (worker, m_settings, "settings");
  return worker.is_ok ();
}
