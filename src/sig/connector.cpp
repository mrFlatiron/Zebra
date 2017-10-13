#include "connector.h"
#include "common/template_utils.h"
#include "signal_base.h"

namespace sig
{
  connector::connector ()
  {

  }

  connector::~connector ()
  {
    disconnect_all ();
  }

  connector::connector (const connector &)
  {

  }

  connector::connector (connector &&c)
  {
    c.disconnect_all ();
  }

  connector &connector::operator =(const connector &)
  {
    return *this;
  }

  connector &connector::operator =(connector &&c)
  {
    c.disconnect_all ();
    return *this;
  }

  void connector::remove_signal (signal_base *ptr)
  {
    auto it = m_signals.find (ptr);

    if (it == m_signals.end ())
      {
        DEBUG_PAUSE ("No signal found");
      }

    m_signals.erase (ptr);
  }

  void connector::disconnect_all ()
  {
    for (auto s : m_signals)
      {
        s->remove_connect (this);
      }
    m_signals.clear ();
  }

}
