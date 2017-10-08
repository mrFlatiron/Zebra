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
    for (auto s : m_signals)
      {
        s->remove_connect (this);
      }
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

}
