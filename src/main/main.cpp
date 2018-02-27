#include <QApplication>

#include "gui/main_window.h"

#include "kernel/ticket_container.h"
#include "kernel/columns_handler.h"
#include "kernel/project_handler.h"

int main(int argc, char *argv[])
{
 QApplication app (argc, argv);

 project_handler zebra;

 if (!zebra.columns ().size ())
   {
     zebra.columns ().create_column ("First Column");

     zebra.columns ().create_column ("Second Column");

     zebra.columns ().create_column ("Third Column");
   }
 main_window w (zebra);

 w.show ();
  return app.exec ();
}
