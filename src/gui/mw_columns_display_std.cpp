#include "mw_columns_display_std.h"
#include "kernel/columns_handler.h"

mw_columns_display_std::mw_columns_display_std (columns_handler &columns)
  : m_columns (columns)
{
  m_conn.connect_to (columns.column_deleted, [this] {layout_changed ();});
}

mw_columns_display_std::~mw_columns_display_std ()
{

}

std::vector<column_id> mw_columns_display_std::get_shown_indices ()
{
  auto col_ids = m_columns.all_ids ();
  std::sort (col_ids.begin (), col_ids.end ());
  return col_ids;
}
