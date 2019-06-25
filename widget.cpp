/*******************************************************************************
* Description: 小部件实现类(每种小部件都是一个载体，具体想要什么样的界面可以自己设计最后添加到小部件上就行)
* Author: Niu yi qun
* Creation date: 2019/6/25
* Last modified person: Niu yi qun
* Last modified date: 2019/6/25
******************************************************************************/
#include "product.h"

#include <QHBoxLayout>

namespace Jinhui {
  /*
   * Widget
   */
  // cotr
  Widget::Widget(QWidget* parent)
    :QWidget(parent) {}

  void Widget::setupUi(QSharedPointer<const Protocol> protocol) {
    Q_UNUSED(protocol);
  }

  /*
   * Titlebar
   */
  // cotr
  Titlebar::Titlebar(QWidget* parent)
    :Widget(parent) {}

  void Titlebar::setupUi(QSharedPointer<const Protocol> protocol) {
    QHBoxLayout* hLayout = new QHBoxLayout;
    Titlebar_Label* titlebarLabel = new Titlebar_Label(protocol);
    MinWindow_Label* minWindowLabel = new MinWindow_Label(protocol);
    MaxWindow_Label* maxWindowLabel = new MaxWindow_Label(protocol);
    ShutdownWindow_Label* shutdownWindowLabel = new ShutdownWindow_Label(protocol);
    hLayout->addWidget(titlebarLabel, 5, Qt::AlignLeft);
    hLayout->addWidget(minWindowLabel, 1, Qt::AlignRight);
    hLayout->addWidget(maxWindowLabel, 1, Qt::AlignRight);
    hLayout->addWidget(shutdownWindowLabel, 1, Qt::AlignRight);
    setLayout(hLayout);
  }

}
