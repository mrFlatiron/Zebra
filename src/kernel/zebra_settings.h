#ifndef ZEBRA_SETTINGS_H
#define ZEBRA_SETTINGS_H

#include "settings_typedefs.h"
#include "user_profile.h"
#include "sig/sigsignal.h"

#include <QDir>

namespace work
{
  class xml_worker;
}

class zebra_settings
{
private:
  QString m_working_dir = QDir::homePath () + "/.ZebraResources";
  user_profile_id m_max_id;
  user_profile_id m_current_id;
  std::unordered_map<user_profile_id, user_profile> m_profiles;
public:
  zebra_settings () = default;
  ~zebra_settings ();

  user_profile *current_profile ();

  user_profile_id create_new_profile ();

  user_profile *profile (user_profile_id id);

  void change_profile (user_profile_id id);

  bool save (const QString &save_file_name);
  bool load (const QString &save_file_name);

  sig::signal<> settings_changed;

  bool worker_process (work::xml_worker &worker);
};

#endif // ZEBRA_SETTINGS_H
