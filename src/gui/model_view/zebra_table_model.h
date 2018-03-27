#ifndef ZEBRA_TABLE_MODEL_H
#define ZEBRA_TABLE_MODEL_H

#include "sig/sigsignal.h"

#include <QVariant>

template<typename UserIndex>
class zebra_table_model
{
private:
  using index_t = zebra_table_index<UserIndex>;
public:
  zebra_table_model ();
  virtual ~zebra_table_model () = default;

public:
  class zebra_table_index
  {
  private:
    friend class zebra_table_model;
    UserIndex m_index;
    int m_row;
    int m_col;
    bool m_is_valid;
  public:
    UserIndex user_index () const {return m_index;}
    int row () const {return m_row;}
    int col () const {return m_col;}
    bool is_valid () const {return m_is_valid;}
  };

  virtual std::vector<UserIndex> rows () const = 0;
  virtual QVariant data (const index_t &index) const = 0;
  virtual Qt::ItemFlags flags (const index_t &index) const
  {
    FIX_UNUSED (index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }

  virtual int cols_count () const {return 1;}

  virtual bool set_data (const index_t &index, const QVariant &data)
  {
    FIX_UNUSED (index, data);
    return false;
  }


  sig::signal<> layout_changed;
private:
  void set_data_actual (const index_t &index, const QVariant &data);
}

#endif // ZEBRA_TABLE_MODEL_H
