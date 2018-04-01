#ifndef ZEBRA_TABLE_MODEL_ADAPTER_H
#define ZEBRA_TABLE_MODEL_ADAPTER_H

#include <QAbstractTableModel>
#include "zebra_table_model.h"
#include "sig/connector.h"

template<typename UserIndex>
class zebra_table_model_adapter : public QAbstractTableModel
{
public:
  using index_t = typename zebra_table_model<UserIndex>::table_index;
  zebra_table_model_adapter (zebra_table_model<UserIndex> *model, QObject *parent = nullptr)
    : QAbstractTableModel (parent),
      m_zebra_model (model)
  {
    m_conn.connect_to (model->layout_changed, [this] {handle_layout_changed ();});
    m_zebra_model->layout_changed ();
  }
  ~zebra_table_model_adapter () {}

  int rowCount (const QModelIndex &) const override
  {
    return m_row_count;
  }

  int columnCount (const QModelIndex &) const override
  {
    return m_col_count;
  }

  QVariant data (const QModelIndex &index, int role) const override
  {
    int col = index.column ();
    int row = index.row ();

    return m_zebra_model->data (index_t (
                                  m_rows[row],
                                  row, col, index.isValid ()), role);
  }

  QVariant headerData (int section, Qt::Orientation orientation, int role) const override
  {
    if (orientation == Qt::Vertical)
      return QVariant ();

    return m_zebra_model->horizontal_header_data (section, role);
  }

  bool setData (const QModelIndex &index, const QVariant &value, int role) override
  {
    int col = index.column ();
    int row = index.row ();

    return m_zebra_model->set_data_actual (index_t (
                                             m_rows[row],
                                             row, col, index.isValid ()),
                                           value,
                                           role);
  }

  Qt::ItemFlags flags (const QModelIndex &index) const override
  {
    return m_zebra_model->flags (index_t (
                                   m_rows[index.row ()],
                                 index.row (), index.column (), index.isValid ()));
  }
private:
  zebra_table_model<UserIndex> *m_zebra_model = nullptr;
  sig::connector m_conn;

  int m_row_count = -1;
  int m_col_count = -1;
  std::vector<UserIndex> m_rows;
  void handle_layout_changed ()
  {
    m_rows = m_zebra_model->rows ();
    int new_row_count = isize (m_rows);
    int new_col_count = m_zebra_model->cols_count ();

    if (m_row_count == -1 || m_col_count == -1)
      {
        m_row_count = new_row_count;
        m_col_count = new_col_count;
        return;
      }

    if (m_row_count > 0)
      {
        beginRemoveRows (QModelIndex (), 0, m_row_count);
        m_row_count = 0;
        endRemoveRows ();
      }

    if (new_row_count > 0)
      {
        beginInsertRows (QModelIndex (), 0, new_row_count);
        m_row_count = new_row_count;
        endInsertRows ();
      }

    if (m_col_count > 0)
      {
        beginRemoveColumns (QModelIndex (), 0, m_col_count);
        m_col_count = 0;
        endRemoveColumns ();
      }

    if (new_col_count > 0)
      {
        beginInsertColumns (QModelIndex (), 0, new_col_count);
        m_col_count = new_col_count;
        endInsertColumns ();
      }

    dataChanged (index (0, 0), index (m_row_count - 1, m_col_count - 1));
  }
};

#endif // ZEBRA_TABLE_MODEL_ADAPTER_H
