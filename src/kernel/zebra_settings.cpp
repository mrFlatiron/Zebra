#include "zebra_settings.h"
#include "common/work/work.h"


zebra_settings::~zebra_settings ()
{
  save ("ZebraSave.xml");
}

user_profile *zebra_settings::current_profile ()
{
  return profile (m_current_id);
}

user_profile_id zebra_settings::create_new_profile ()
{
  m_max_id++;

  if (!m_profiles.size ())
    m_current_id = m_max_id;

  m_profiles.emplace (m_current_id, user_profile (m_current_id));

  return m_current_id;
}

user_profile *zebra_settings::profile (user_profile_id id)
{
  auto it = m_profiles.find (id);
  ASSERT_RETURN (it != m_profiles.end (), nullptr);

  return &(it->second);
}

void zebra_settings::change_profile (user_profile_id id)
{
  auto it = m_profiles.find (id);
  ASSERT_RETURN (it != m_profiles.end (), );

  m_current_id = id;
  settings_changed ();
}

bool zebra_settings::load (const QString &save_file_name)
{
  std::string save_file_full_path = QString("%1/%2").arg (m_working_dir, save_file_name).toUtf8 ().data ();
  work::xml_worker loader (work::action_t::load, save_file_full_path);
  worker_process (loader);
  return loader.is_ok ();
}

bool zebra_settings::save (const QString &save_file_name)
{
  QDir ().mkpath (m_working_dir);
  std::string save_file_full_path = QString("%1/%2").arg (m_working_dir, save_file_name).toUtf8 ().data ();
  work::xml_worker saver (work::action_t::save, save_file_full_path);
  worker_process (saver);
  return saver.is_ok ();
}

bool zebra_settings::worker_process (work::xml_worker &worker)
{
  work::process (worker, m_max_id, "max_id");
  work::process (worker, m_working_dir, "working_dir");
  work::process (worker, m_profiles, "profiles");
  return worker.is_ok ();
}
