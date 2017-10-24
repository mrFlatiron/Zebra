#ifndef SIGNAL_BASE_H
#define SIGNAL_BASE_H

namespace sig
{

  class connector;

  class signal_base
  {
  protected:
    mutable std::vector<const connector *> m_connectors;
  public:
    signal_base ();
    ~signal_base ();

    signal_base (const signal_base &);
    signal_base (signal_base &&);

    int add_connect (const connector * conn) const;

    int add_pos (const connector *conn) const;

    virtual int remove_connect(connector *conn) const;
  private:
    void disconnect_all ();
  };

}
#endif // SIGNAL_BASE_H
