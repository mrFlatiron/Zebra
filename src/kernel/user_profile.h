#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <QString>

#include "settings_typedefs.h"
#include "user_settings.h"

namespace work
{
  class xml_worker;
}

class user_profile
{
private:
  QString m_profile_name = "New User";
  user_profile_id m_id;
  user_settings m_settings;

public:
  user_profile () = default;
  ~user_profile () = default;

  user_profile (user_profile_id id);

  user_profile_id id () const;
  void set_id (user_profile_id id);

  QString profile_name () const;
  void set_profile_name (const QString &profile_name);

  user_settings &settings ();
  const user_settings &settings () const;

  bool worker_process (work::xml_worker &worker);
};

#endif // USER_PROFILE_H
