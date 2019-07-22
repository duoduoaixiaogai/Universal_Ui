/*******************************************************************************
* Description: 进度条类(自定义进度条基类,方便从工厂创建)
* Author: Niu yi qun
* Creation date: 2019/6/28
* Last modified person: Niu yi qun
* Last modified date: 2019/6/28
******************************************************************************/
#include "include/product.h"

namespace Jinhui {
  /*
   * ProgressBar
   */
  // cotr
  ProgressBar::ProgressBar(QWidget* parent)
    :QProgressBar(parent) {}

  ProgressBar::~ProgressBar() {}
}
