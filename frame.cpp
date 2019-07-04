/*******************************************************************************
* Description: 拥有框架的小部件的基类
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#include "product.h"

namespace Jinhui {
  /*
   * Frame
   */
  // cotr
  Frame::Frame(QWidget* parent)
    :QFrame(parent) {}

  void Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    Q_UNUSED(protocol);
  }
}