#include "signal_base.h"
#include "connector.h"

namespace sig
{
  signal_base::signal_base ()
  {

  }
  signal_base::~signal_base ()
  {
    for (auto c : m_connectors)
      {
        c->remove_signal (this);
      }
  }

  bool signal_base::add_connect (connector *conn)
  {
    if (std::find (m_connectors.begin (), m_connectors.end (), conn) ==
        m_connectors.end ())
      {
        m_connectors.push_back (conn);
        return true;
      }
    else
      {
        DEBUG_PAUSE ("Connection is already in vector");
        return false;
      }
  }

  void signal_base::remove_connect (connector *conn)
  {
    auto it = std::find (m_connectors.begin (), m_connectors.end (), conn);
    if (it == m_connectors.end ())
      {
        DEBUG_PAUSE ("No such connector. Check your code");
      }
    m_connectors.erase (it);
  }
}