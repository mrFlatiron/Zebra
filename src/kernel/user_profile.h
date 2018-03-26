#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <QString>
#include "typesafe_id.h"

MAKE_TYPESAFE_ID (user_profile_id, int64_t);

class user_profile
{
private:
  QString m_profile_name;
  user_profile_id m_id;


public:
  user_profile () = default;
  ~user_profile () = default;
};

#endif // USER_PROFILE_H
