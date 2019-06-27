/*******************************************************************************
* Description: 小部件实现类(每种小部件都是一个载体，具体想要什么样的界面可以自己设计最后添加到小部件上就行)
* Author: Niu yi qun
* Creation date: 2019/6/25
* Last modified person: Niu yi qun
* Last modified date: 2019/6/25
******************************************************************************/
#include "product.h"
#include "common.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QStackedWidget>

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
    hLayout->setContentsMargins(0, 0, 0, 0);
    TitlebarMinMaxShut_Label* titlebarMinMaxShut = new TitlebarMinMaxShut_Label(protocol);
    titlebarMinMaxShut->setMainWindow(mMainWindow);
    hLayout->addWidget(titlebarMinMaxShut);
    setLayout(hLayout);
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
    vLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vLayout);
    auto menu = pro->menus.begin();
    auto menuEnd = pro->menus.end();
    while (menu != menuEnd) {
      Menu_PushButton* mainMenu = new Menu_PushButton(protocol, menu->menuPicName);
      vLayout->addWidget(mainMenu, 1);
      SubMenu* subMenu = new SubMenu(menu->itemsName);
      subMenu->setupUi(protocol);
      vLayout->addWidget(subMenu, 2);
      ++menu;
    }
  }

  /*
   * SubMenu
   */
  // cotr
  SubMenu::SubMenu(const QStringList& items, QWidget* parent)
    :Widget(parent)
    ,mItems(items) {}

  void SubMenu::setupUi(QSharedPointer<const Protocol> protocol) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(protocol);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setFrameStyle(QFrame::NoFrame);
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* vLayout1 = new QVBoxLayout;
    //vLayout1->setContentsMargins(0, 0, 0, 0);
    auto item = mItems.begin();
    auto itemEnd = mItems.end();
    while (item != itemEnd) {
      MenuItem_PushButton* menuItemButton = new MenuItem_PushButton(protocol, *item);
      vLayout1->addWidget(menuItemButton);
      ++item;
    }
    centralWidget->setLayout(vLayout1);
    scrollArea->setWidget(centralWidget);
    vLayout->addWidget(scrollArea);
    setLayout(vLayout);
  }


  /*
   * ContentArea
   */
  // cotr
  ContentArea::ContentArea(QWidget* parent)
    :Widget(parent) {
  }

  void ContentArea::setupUi(QSharedPointer<const Protocol> protocol) {
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    QStackedWidget* stackedWidget = new QStackedWidget;
    QuadScreen* quadScreen = new QuadScreen;
    quadScreen->setupUi(protocol);
    stackedWidget->addWidget(quadScreen);
    hLayout->addWidget(stackedWidget);
    setLayout(hLayout);
  }

  void ContentArea::addWidgetInContentArea(Widget* widget) {
    mWidgets->addWidget(widget);
    mWidgetsIndex[widget->objectName()] = widget;
  }

  void ContentArea::removeWidgetInContentArea(const QString& name) {
    if (mWidgetsIndex.contains(name)) {
      Widget* widget = mWidgetsIndex.value(name);
      mWidgets->removeWidget(widget);
    }
  }

  /*
  * QuadScreen
  */
  // cotr
  QuadScreen::QuadScreen(QWidget* parent)
    :Widget(parent) {

  }

  void QuadScreen::setupUi(QSharedPointer<const Protocol> protocol) {
    QGridLayout* gridLayout = new QGridLayout;
    //gridLayout->setContentsMargins(0, 0, 0, 0);
    // 行
    for (int i = 0; i < 2; ++i) {
      // 列
      for (int j = 0; j < 2; ++j) {
        Frame* frame = new Frame;
        frame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        frame->setLineWidth(2);
        gridLayout->addWidget(frame, i, j);
      }
    }
    setLayout(gridLayout);
  }

}
