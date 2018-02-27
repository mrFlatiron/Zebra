#ifndef WORKER_PROCESS_IMPLS_H
#define WORKER_PROCESS_IMPLS_H

#include "kernel/typesafe_id.h"
#include <QString>

namespace work
{
  template<typename index_t, typename IdName, typename Worker>
  bool worker_process (Worker &worker, typesafe_id_generic<index_t, IdName> &id)
  {
    auto temp = static_cast<index_t> (id);

    if (worker.action () == work::action_t::save)
      work::process (worker, temp, "typesafe_id");
    else
      {
        work::process (worker, temp, "typesafe_id");
        id = typesafe_id_generic<index_t, IdName> (temp);
      }
    return worker.is_ok ();
  }

  template<typename Worker>
  bool worker_process (Worker &worker, QString &str)
  {
    std::string temp_str (str.toUtf8 ().data ());

    work::process (worker, temp_str, "qstr");

    if (worker.action () == work::action_t::load)
      str = QString::fromUtf8 (temp_str.c_str ());

    return worker.is_ok ();
  }
}
#endif // WORKER_PROCESS_IMPLS_H
