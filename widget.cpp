/*******************************************************************************
* Description: 小部件实现类(每种小部件都是一个载体，具体想要什么样的界面可以自己设计最后添加到小部件上就行)
* Author: Niu yi qun
* Creation date: 2019/6/25
* Last modified person: Niu yi qun
* Last modified date: 2019/6/25
******************************************************************************/
#include "product.h"

#include <QHBoxLayout>
#include <QMouseEvent>

namespace Jinhui {
  /*
   * Widget
   */
  // cotr
  Widget::Widget(QWidget* parent)
    :QWidget(parent) {}

  void Widget::setMainWindow(QSharedPointer<MainWindow> mainWindow) {
    mMainWindow = mainWindow;
  }

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
    titlebarLabel->setMainWindow(mMainWindow);
    //MinWindow_Label* minWindowLabel = new MinWindow_Label(protocol);
    //minWindowLabel->setMainWindow(mMainWindow);
    //MaxWindow_Label* maxWindowLabel = new MaxWindow_Label(protocol);
    //maxWindowLabel->setMainWindow(mMainWindow);
    //shutdownWindowLabel = new ShutdownWindow_Label(protocol);
    //shutdownWindowLabel->setMainWindow(mMainWindow);
    hLayout->addWidget(titlebarLabel);
    //hLayout->addWidget(titlebarLabel, 5, Qt::AlignLeft);
    //hLayout->addWidget(minWindowLabel, 1, Qt::AlignRight);
    //hLayout->addWidget(maxWindowLabel, 1, Qt::AlignRight);
    //hLayout->addWidget(shutdownWindowLabel, 1, Qt::AlignRight);
    setLayout(hLayout);

    int width = this->width();
    int height = this->height();


    titlebarLabel->setDefPictureWidget();
  }

  void Titlebar::mouseMoveEvent(QMouseEvent *event) {
    if (shutdownWindowLabel->geometry().contains(event->pos())) {
      int i = 10;
    } else {
      int i = 10;
    }
  }

  /*
   * Menubar
   */
  // cotr
  Menubar::Menubar(QWidget* parent)
    :Widget(parent) {

  }

  void Menubar::setupUi(QSharedPointer<const Protocol> protocol) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(protocol);

    QVBoxLayout* vLayout = new QVBoxLayout;
    this->setLayout(vLayout);
    auto menu = pro->menus.begin();
    auto menuEnd = pro->menus.end();
    while (menu != menuEnd) {
      Menu_PushButton* mainMenu = new Menu_PushButton(protocol);
      vLayout->addWidget(mainMenu);
      SubMenu* subMenu = new SubMenu;
      vLayout->addWidget(subMenu);
      ++menu;
    }
  }

  /*
   * SubMenubar
   */
  // cotr
  SubMenu::SubMenu(QWidget* parent)
    :Widget(parent) {}

  void SubMenu::setupUi(QSharedPointer<const Protocol> protocol) {

  }


  /*
   * ContentArea
   */
  // cotr
  ContentArea::ContentArea(QWidget* parent)
    :Widget(parent) {
  }

  void ContentArea::setupUi(QSharedPointer<const Protocol> protocol) {

  }

  /*
   * Menu_PushButton
   */
  // cotr
  Menu_PushButton::Menu_PushButton(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :PushButton(protocol, parent) {}

  void Menu_PushButton::paintEvent(QPaintEvent* ev) {

  }

  /*
   * SubMenu_PushButton
   */
  // cotr
  SubMenu_PushButton::SubMenu_PushButton(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :PushButton(protocol, parent){}

  void SubMenu_PushButton::paintEvent(QPaintEvent *) {

  }

}
