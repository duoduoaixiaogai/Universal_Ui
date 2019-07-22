/*******************************************************************************
* Description: 按钮类(自定义按钮基类,方便从工厂创建)
* Author: Niu yi qun
* Creation date: 2019/6/26
* Last modified person: Niu yi qun
* Last modified date: 2019/6/26
******************************************************************************/
#include "product.h"
#include "common.h"
#include "signalsrelay.h"

#include <QPainter>
#include <QPaintEvent>

namespace Jinhui {

  /*
   * PushButton
   */
  // cotr
  PushButton::PushButton(QWidget* parent)
    :QPushButton(parent) {}

  PushButton::PushButton(const QString& text, QWidget* parent)
    :QPushButton(text, parent) {}

  PushButton::PushButton(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :QPushButton(parent) {
    mProtocol = protocol;
  }

  /*
   * Menu_PushButton
   */
  // cotr
  Menu_PushButton::Menu_PushButton(QSharedPointer<const Protocol> protocol, const QString &fileName, QWidget* parent)
    :PushButton(protocol, parent)
    ,mFileName(fileName) {}

  void Menu_PushButton::paintEvent(QPaintEvent* ev) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    QPainter painter(this);
    QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, mFileName));
    QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
    painter.drawPixmap(rect(), scaPixmap);

    ev->accept();
  }

  /*
   * SubMenu_PushButton
   */
  // cotr
  MenuItem_PushButton::MenuItem_PushButton(QSharedPointer<const Protocol> protocol, const QString &fileName, QWidget* parent)
    :PushButton(protocol, parent)
    ,mFileName(fileName) {}

  void MenuItem_PushButton::paintEvent(QPaintEvent* ev) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    QPainter painter(this);
    QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, mFileName));
    QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
    painter.drawPixmap(rect(), scaPixmap);

    ev->accept();
  }

}
