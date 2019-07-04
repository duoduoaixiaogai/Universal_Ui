/*******************************************************************************
* Description: 视图类(所有自定义视图的抽象)
* Author: Niu yi qun
* Creation date: 2019/6/28
* Last modified person: Niu yi qun
* Last modified date: 2019/6/28
******************************************************************************/
#include "product.h"

#include <QHeaderView>

namespace Jinhui {
  /*
   * Test_View
   */
  // cotr
  Test_View::Test_View(QSqlTableModel* model, QWidget* parent)
    :QTableView(parent) {
      setModel(model);

      horizontalHeader()->setStretchLastSection(true);
      horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
  }
}