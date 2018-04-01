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

  connect_current_profile ();
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

std::vector<user_profile_id> zebra_settings::profile_ids () const
{
  return container_keys (m_profiles);
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
  work::process (worker, m_current_id, "current_id");

  if (worker.action () == work::action_t::load)
    make_connections_after_load ();

  return worker.is_ok ();
}

void zebra_settings::connect_current_profile ()
{
  auto cur_id_for_lambda = m_current_id;

  m_conn.connect_to (m_profiles[m_current_id].settings ().tickets ().ticket_deleted,
                     [this, cur_id_for_lambda] (ticket_id id)
  {m_profiles[cur_id_for_lambda].settings ().columns ().notify_ticket_deleted (id);});
}

void zebra_settings::make_connections_after_load ()
{
  for (auto &p : m_profiles)
    {
      auto id_for_lambda = p.first;
      m_conn.connect_to (m_profiles[id_for_lambda].settings ().tickets ().ticket_deleted,
                         [this, id_for_lambda] (ticket_id id)
      {m_profiles[id_for_lambda].settings ().columns ().notify_ticket_deleted (id);});
    }
}
