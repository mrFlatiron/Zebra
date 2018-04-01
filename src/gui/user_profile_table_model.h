#ifndef USER_PROFILE_TABLE_MODEL_H
#define USER_PROFILE_TABLE_MODEL_H

#include "kernel/settings_typedefs.h"
#include "model_view/zebra_table_model.h"
#include "sig/connector.h"

class user_profile_table_model : public zebra_table_model<user_profile_id>
{
private:
  zebra_settings &m_zebra_settings;
  sig::connector m_conn;
public:
  user_profile_table_model (zebra_settings &settings);
  ~user_profile_table_model ();

  std::vector<user_profile_id> rows () const override;
  QVariant data (const index_t &index, int role) const override;
  QVariant horizontal_header_data (int col, int role) const override;
  int cols_count () const override;
};

#endif // USER_PROFILE_TABLE_MODEL_H
