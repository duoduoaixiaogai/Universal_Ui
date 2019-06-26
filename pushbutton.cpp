/*******************************************************************************
* Description: 按钮类(自定义按钮基类,方便从工厂创建)
* Author: Niu yi qun
* Creation date: 2019/6/26
* Last modified person: Niu yi qun
* Last modified date: 2019/6/26
******************************************************************************/
#include "product.h"

namespace Jinhui {

  /*
   * PushButton
   */
  // cotr
  PushButton::PushButton(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :QPushButton(parent) {
    mProtocol = protocol;
  }
}
