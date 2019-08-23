/*******************************************************************************
* Description: 滑动条类
* Author: Niu yi qun
* Creation date: 2019/8/23
* Last modified person: Niu yi qun
* Last modified date: 2019/8237
******************************************************************************/
#include "include/product.h"

namespace Jinhui {
  /*
   * Slider
   */
  // cotr
  Slider::Slider(Qt::Orientation ori, QWidget* parent)
    :QSlider(ori, parent) {}

  Slider::~Slider() {}

}
