/*******************************************************************************
* Description: 项目基类(涵盖所有项目)
* Author: Niu yi qun
* Creation date: 2019/7/8
* Last modified person: Niu yi qun
* Last modified date: 2019/7/8
******************************************************************************/
#include "include/product.h"

namespace Jinhui {
  /*
   * GraphicsItem
   */
  // cotr
  GraphicsItem::GraphicsItem() {}

  GraphicsItem::~GraphicsItem() {}
  QRectF GraphicsItem::boundingRect() const {
    return QRectF(0, 0, 0, 0);
  }

  void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
  }

  /*
   * GraphicsPixmapItem
   */
  // cotr
  GraphicsPixmapItem::GraphicsPixmapItem(const QPixmap &pixmap)
    :QGraphicsPixmapItem(pixmap) {}

  GraphicsPixmapItem::~GraphicsPixmapItem() {}
}
