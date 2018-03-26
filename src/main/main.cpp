#include <QApplication>

#include "gui/main_window.h"

#include "kernel/zebra_settings.h"

int main(int argc, char *argv[])
{
 QApplication app (argc, argv);

 zebra_settings zebra;

 if (!zebra.load ("ZebraSave.xml"))
 {

   zebra.create_new_profile ();

   auto profile = zebra.current_profile ();

   auto &settings = profile->settings ();

   if (!settings.columns ().size ())
     {
       settings.columns ().create_column ("First Column");

       settings.columns ().create_column ("Second Column");

       settings.columns ().create_column ("Third Column");
     }
 }
 main_window w (zebra);

 w.show ();
  return app.exec ();
}
