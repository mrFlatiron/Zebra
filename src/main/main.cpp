#include <QApplication>

#include "gui/main_window.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "kernel/project_handler.h"

#include "saveload/sql/enum_sql.h"

enum class test_enum
{
  id,
  title,
  desc,
  COUNT
};

class sql_test : public enum_sql_table<test_enum>
{
protected:
  std::string column_name (test_enum e) const override
  {
    switch (e)
      {
      case test_enum::id:
        return "ID";
      case test_enum::title:
        return "Title";
      case test_enum::desc:
        return "Description";
      case test_enum::COUNT:
        return "";
      }
    return "";
  }

  std::string column_type (test_enum e) const override
  {
    switch (e)
      {
      case test_enum::id:
        return "INTEGER";
      case test_enum::title:
        return "TEXT";
      case test_enum::desc:
        return "TEXT";
      case test_enum::COUNT:
        return "";
      }
    return "";
  }

  std::string table_name () const override
  {
    return "Test";
  }

  std::string schema_name () const override
  {
    return "schema";
  }

};

int main(int argc, char *argv[])
{
 QApplication app (argc, argv);

// project_handler zebra;

// ticket_object t1;

// t1.set_title ("Zebra 1");
// t1.set_description ("Desc 1");
// t1.set_type (ticket_type::bug);
// t1.set_priority (ticket_priority::high);

// ticket_object t2;

// t2.set_title ("Zebra 2");
// t2.set_description ("Desc 2");
// t2.set_type (ticket_type::feature);
// t2.set_priority (ticket_priority::low);

// ticket_object t3;

// t3.set_title ("Zebra 3");
// t3.set_description ("Desc 3");
// t3.set_type (ticket_type::regular);
// t3.set_priority (ticket_priority::mid);

// ticket_object t4;

// t4.set_title ("Zebra 4");
// t4.set_description ("Desc 4");
// t4.set_type (ticket_type::question);
// t4.set_priority (ticket_priority::low);

// zebra.tickets ().add_ticket (std::move (t1));
// zebra.tickets ().add_ticket (std::move (t2));
// zebra.tickets ().add_ticket (std::move (t3));
// zebra.tickets ().add_ticket (std::move (t4));

// auto ticket_ids = zebra.tickets ().all_ids ();

// std::sort (ticket_ids.begin (), ticket_ids.end ());

// int size = isize (ticket_ids);

// auto col = zebra.columns ().create_column ("First Column");
// auto i = 0;
// for (; i < size; i++)
//   zebra.columns ().column (col).add_ticket (ticket_ids[i]);

//// for (; i < size / 2; i++)
////   zebra.columns ().column (col).add_ticket (ticket_ids[i]);

// col = zebra.columns ().create_column ("Second Column");

// col = zebra.columns ().create_column ("Third Column");



// main_window w (zebra);

// w.show ();

 sql_test table;

 enum_sql_index<test_enum> table_index (&table);
 table_index.set_index_name ("index_test");
 table_index.set_indexed_columns ({test_enum::title});
 table_index.set_unique (true);

 std::cout << table.create_stmt () << std::endl;
 std::cout << table.drop_stmt () << std::endl;
 std::cout << table.insert_stmt ({test_enum::id, test_enum::title}, sql_insert_policy::replace) << std::endl;
 std::cout << table.select_stmt ({test_enum::id}) << std::endl;
 std::cout << table.set_sync_pragma_stmt (false) << std::endl;
 std::cout << table_index.as_string ()<< std::endl;

 return app.exec ();

}
