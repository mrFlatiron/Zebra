#include <QApplication>

#include "gui/main_window.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "kernel/project_handler.h"


int main(int argc, char *argv[])
{
 QApplication app (argc, argv);

 project_handler zebra;

 ticket_object t1;

 t1.set_title ("Zebra 1");
 t1.set_description ("Desc 1");
 t1.set_type (ticket_type::bug);
 t1.set_priority (ticket_priority::high);

 ticket_object t2;

 t2.set_title ("Zebra 2");
 t2.set_description ("Desc 2");
 t2.set_type (ticket_type::feature);
 t2.set_priority (ticket_priority::low);

 ticket_object t3;

 t3.set_title ("Zebra 3");
 t3.set_description ("Desc 3");
 t3.set_type (ticket_type::regular);
 t3.set_priority (ticket_priority::mid);

 ticket_object t4;

 t4.set_title ("Zebra 4");
 t4.set_description ("Desc 4");
 t4.set_type (ticket_type::question);
 t4.set_priority (ticket_priority::low);

 zebra.tickets ().add_ticket (std::move (t1));
 zebra.tickets ().add_ticket (std::move (t2));
 zebra.tickets ().add_ticket (std::move (t3));
 zebra.tickets ().add_ticket (std::move (t4));

 auto ticket_ids = zebra.tickets ().all_ids ();

 std::sort (ticket_ids.begin (), ticket_ids.end ());

 int size = isize (ticket_ids);

 auto col = zebra.columns ().create_column ("First Column");
 auto i = 0;
 for (; i < size; i++)
   zebra.columns ().column (col).add_ticket (ticket_ids[i]);

// for (; i < size / 2; i++)
//   zebra.columns ().column (col).add_ticket (ticket_ids[i]);

 col = zebra.columns ().create_column ("Second Column");

 col = zebra.columns ().create_column ("Third Column");



 main_window w (zebra);

 w.show ();

 return app.exec ();

}
