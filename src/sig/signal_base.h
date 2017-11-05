#ifndef SIGNAL_BASE_H
#define SIGNAL_BASE_H

namespace sig
{

  class connector;

  class signal_base
  {
  protected:
    mutable std::set<connector *> m_connectors;
  public:
    signal_base ();
    ~signal_base ();

    signal_base (const signal_base &);
    signal_base (signal_base &&);

    bool add_connect (connector * conn) const;


    virtual void remove_connect (connector *conn) const;
  protected:
    void disconnect_all ();
  };

}
#endif // SIGNAL_BASE_H
