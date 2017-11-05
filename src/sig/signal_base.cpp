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

  bool signal_base::add_connect (connector *conn) const
  {
    if (m_connectors.find (conn) == m_connectors.end ())
      {
        m_connectors.insert (conn);
        return true;
      }
    return false;
  }

  void signal_base::remove_connect (connector *conn) const
  {
    auto it = m_connectors.find (conn);
    if (it == m_connectors.end ())
      {
        return;
      }

    m_connectors.erase (it);
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
