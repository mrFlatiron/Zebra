#ifndef ZEBRA_TABLE_MODEL_H
#define ZEBRA_TABLE_MODEL_H

#include "sig/sigsignal.h"

#include <QVariant>

template<typename UserIndex>
class zebra_table_model_adapter;

template<typename UserIndex>
class zebra_table_model
{
private:
  friend class zebra_table_model_adapter<UserIndex>;

public:
  zebra_table_model () = default;
  virtual ~zebra_table_model () = default;

public:
  class table_index
  {
  private:
    friend class zebra_table_model;
    UserIndex m_index;
    int m_row;
    int m_col;
    bool m_is_valid;
  public:
    table_index (const UserIndex &uindex, int row, int col, bool is_valid = true)
    {
      m_index = uindex;
      m_row = row;
      m_col = col;
      m_is_valid = is_valid;
    }
    UserIndex user_index () const {return m_index;}
    int row () const {return m_row;}
    int col () const {return m_col;}
    bool is_valid () const {return m_is_valid;}
  };

  using index_t = zebra_table_model<UserIndex>::table_index;

  virtual std::vector<UserIndex> rows () const = 0;
  virtual QVariant data (const index_t &index, int role) const = 0;
  virtual Qt::ItemFlags flags (const index_t &index) const
  {
    FIX_UNUSED (index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }

  virtual QVariant horizontal_header_data (int col, int role) const
  {
    FIX_UNUSED (col, role);
    return QVariant ();
  }

  virtual int cols_count () const {return 1;}

  virtual bool set_data (const index_t &index, const QVariant &data, int role)
  {
    FIX_UNUSED (index, data, role);
    return false;
  }


  sig::signal<> layout_changed;
private:
  bool set_data_actual (const index_t &index, const QVariant &data, int role)
  {
    bool data_changed = set_data (index, data, role);

    if (data_changed)
      layout_changed ();

    return data_changed;
  }
};

#endif // ZEBRA_TABLE_MODEL_H
