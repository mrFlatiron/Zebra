#include "user_profile_table_model.h"
#include "kernel/zebra_settings.h"

user_profile_table_model::user_profile_table_model (zebra_settings &settings)
  : m_zebra_settings (settings)
{
  m_conn.connect_to (settings.settings_changed, layout_changed);
}

user_profile_table_model::~user_profile_table_model ()
{

}

std::vector<user_profile_id> user_profile_table_model::rows () const
{
  return m_zebra_settings.profile_ids ();
}

QVariant user_profile_table_model::data (const zebra_table_model::index_t &index, int role) const
{
  if (!index.is_valid ())
    return QVariant ();

  auto profile = m_zebra_settings.profile (index.user_index ());

  ASSERT_RETURN (profile, QVariant ());

  if (role == Qt::DisplayRole)
    switch (index.col ())
      {
      case 0: return profile->profile_name ();
      case 1: return profile->settings ().columns ().size ();
      default: ASSERT_RETURN (false, QVariant ());
      }

  return QVariant ();
}

QVariant user_profile_table_model::horizontal_header_data (int col, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant ();

  switch (col)
    {
    case 0: return "Profile name";
    case 1: return "Columns count";
    default: ASSERT_RETURN (false, QVariant ());
    }

  return QVariant ();
}

int user_profile_table_model::cols_count () const
{
  return 2;
}
