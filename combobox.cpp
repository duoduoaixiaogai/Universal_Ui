/*******************************************************************************
* Description: 组合框类(自定义组合框基类,方便从工厂创建)
* Author: Niu yi qun
* Creation date: 2019/6/28
* Last modified person: Niu yi qun
* Last modified date: 2019/6/28
******************************************************************************/
#include "product.h"

namespace Jinhui {
  /*
   * Combobox
   */
  // cotr
  ComboBox::ComboBox(QWidget* parent)
    :QComboBox(parent) {}

  ComboBox::~ComboBox() {}
}
