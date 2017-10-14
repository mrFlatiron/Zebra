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

 zebra.tickets ().add_ticket (t1);
 zebra.tickets ().add_ticket (t2);
 zebra.tickets ().add_ticket (t3);
 zebra.tickets ().add_ticket (t4);

 auto col = zebra.columns ().create_column ("First Column");
 zebra.columns ().column (col).add_ticket (1);
 zebra.columns ().column (col).add_ticket (3);
 zebra.columns ().column (col).add_ticket (4);

 col = zebra.columns ().create_column ("Second Column");
 zebra.columns ().column (col).add_ticket (2);

 main_window w (zebra);

 w.show ();

 return app.exec ();

}
