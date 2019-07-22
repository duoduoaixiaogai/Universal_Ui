/*******************************************************************************
* Description: 视图类(所有自定义视图的抽象)
* Author: Niu yi qun
* Creation date: 2019/6/28
* Last modified person: Niu yi qun
* Last modified date: 2019/6/28
******************************************************************************/
#include "include/product.h"

#include <QHeaderView>
#include <QSqlTableModel>

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

  /*
   * TableView
   */
  // cotr
  TableView::TableView(QWidget* parent)
    :QTableView(parent) {}

  TableView::~TableView() {}

  /*
   * DatabaseTable_View
   */
  // cotr
  DatabaseTable_View::DatabaseTable_View(QWidget* parent)
    :TableView(parent) {
    horizontalHeader()->setStretchLastSection(true);
  }

  DatabaseTable_View::~DatabaseTable_View() {}

  /*
   * GraphicsView
   */
  // cotr
  GraphicsView::GraphicsView(QWidget* parent)
    :QGraphicsView(parent)
    ,mItem(nullptr) {}

  GraphicsView::~GraphicsView() {}

  void GraphicsView::setItem(GraphicsPixmapItem *item) {
    mItem = item;
  }

  GraphicsPixmapItem* GraphicsView::getItem() const {
    return mItem;
  }

  // protected
  void GraphicsView::resizeEvent(QResizeEvent *event) {
    if (mItem) {
      fitInView(mItem);
    }
  }

  /*
   * OnewayView
   */
  // cotr
  Channel_View::Channel_View(QWidget* parent)
    :GraphicsView(parent) {}

  Channel_View::~Channel_View() {}
}
