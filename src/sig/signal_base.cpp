#include "signal_base.h"
#include "connector.h"
namespace sig
{
  signal_base::signal_base ()
  {

  }
  signal_base::~signal_base ()
  {
    disconnect_all ();
  }

  signal_base::signal_base (const signal_base &)
  {

  }

  signal_base::signal_base (signal_base &&s)
  {
    s.disconnect_all ();
  }

 int signal_base::add_connect (const connector *conn) const
  {
   int pos = 0;
   int size = isize (m_connectors);
   for (; pos < size; pos++)
     if (m_connectors[pos] == conn)
       break;

   if (pos == size)
        m_connectors.push_back (conn);

   return pos;
 }

  int signal_base::remove_connect (connector *conn) const
  {
    int pos = 0;
    int size = isize (m_connectors);
    for (; pos < size; pos++)
      if (m_connectors[pos] == conn)
        break;

    if (pos == size)
      {
        DEBUG_PAUSE ("No such connector. Check your code");
      }
    else
      m_connectors.erase (m_connectors.begin () + pos);

    return pos;
  }

  void signal_base::disconnect_all ()
  {
    for (auto c : m_connectors)
      {
        c->remove_signal (this);
      }
    m_connectors.clear ();
  }
}
