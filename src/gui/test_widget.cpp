#include "test_widget.h"
#include <QVBoxLayout>
#include <QLineEdit>

test_widget::test_widget (QWidget *parent)
{
  FIX_UNUSED (parent);
  QLineEdit *l1 = new QLineEdit;
  QLineEdit *l2 = new QLineEdit;

  QVBoxLayout *lay = new QVBoxLayout;

  lay->setSpacing (0);

  lay->addWidget (l1);
  lay->addWidget (l2);
  setLayout (lay);
}
