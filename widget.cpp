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
    mTitlebarMinMaxShut = new TitlebarMinMaxShut_Label(protocol);
    mTitlebarMinMaxShut->setMainWindow(mMainWindow);
    hLayout->addWidget(mTitlebarMinMaxShut);
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
    auto menu = pro->menus.begin();
    auto menuEnd = pro->menus.end();
    while (menu != menuEnd) {
      Menu_Label* mainMenu = new Menu_Label(protocol, menu->menuPicName);
      mainMenu->setObjectName(menu->objectName);
      mMenus[mainMenu->objectName()] = mainMenu;
      vLayout->addWidget(mainMenu);
      SubMenu* subMenu = new SubMenu(menu->subMenu);
      subMenu->setObjectName(menu->subMenu.objectName);
      mSubmenus[subMenu->objectName()] = subMenu;
      subMenu->setupUi(protocol);
      vLayout->addWidget(subMenu, 1);
      ++menu;
    }
    vLayout->addStretch();
    setLayout(vLayout);
  }

  void Menubar::hideAllSubmenus() {
    for (SubMenu* subMenu : mSubmenus) {
      subMenu->hide();
    }
  }

  /*
   * SubMenu
   */
  // cotr
  SubMenu::SubMenu(const GTXLQXPro::Submenu &subMenu, QWidget* parent)
    :Widget(parent)
    ,mSubmenu(subMenu) {}

  void SubMenu::setupUi(QSharedPointer<const Protocol> protocol) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(protocol);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* vLayout1 = new QVBoxLayout;
    auto item = mSubmenu.itemsName.begin();
    auto itemEnd = mSubmenu.itemsName.end();
    while (item != itemEnd) {
      MenuItem_Label* menuItemButton = new MenuItem_Label(protocol
                                                          ,item->itemDefaultPicture
                                                          ,item->itemClickedPicture);
      menuItemButton->setObjectName(item->objectName);
      mMenuItems[menuItemButton->objectName()] = menuItemButton;
      vLayout1->addWidget(menuItemButton);
      ++item;
    }
    vLayout1->addStretch();
    centralWidget->setLayout(vLayout1);
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->setWidget(centralWidget);
    scrollArea->setWidgetResizable(true);
    vLayout->addWidget(scrollArea);
    setLayout(vLayout);
    if (strToBool(mSubmenu.hide)) {
      hide();
    }
  }

  /*
   * ContentArea
   */
  // cotr
  ContentArea::ContentArea(QSharedPointer<const Protocol> configPro, QWidget* parent)
    :Widget(parent) {
    mConfigPro = configPro;
  }

  void ContentArea::setupUi(QSharedPointer<const Protocol> protocol) {
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    mWidgets = new QStackedWidget;
    // 默认展示小部件
    Widget* defWidget = new Widget;
    defWidget->setObjectName(QLatin1String("defaultWidget"));
    addWidgetInContentArea(defWidget);
    QuadScreen* quadScreen = new QuadScreen;
    quadScreen->setupUi(protocol);
    addWidgetInContentArea(quadScreen);
    Test_Widget* testWidget = new Test_Widget;
    testWidget->setupUi(mConfigPro);
    addWidgetInContentArea(testWidget);
    hLayout->addWidget(mWidgets);
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

  void ContentArea::showSpecifiedWidget(Widget* widget) {
    mWidgets->setCurrentWidget(widget);
  }

  /*
  * QuadScreen
  */
  // cotr
  QuadScreen::QuadScreen(QWidget* parent)
    :Widget(parent) {

  }

  void QuadScreen::setupUi(QSharedPointer<const Protocol> protocol) {
    // 预留 本来应该从配置文件中读取objectname，但是目前没有实现内容区中的小部件的配置文件
    setObjectName(QLatin1String("quadScreen"));

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

  /*
   * Test_Widget
   */
  // cotr
  Test_Widget::Test_Widget(QWidget* parent)
    :Widget(parent) {}

  void Test_Widget::setupUi(QSharedPointer<const Protocol> protocol) {
    setObjectName(QLatin1String("testWidget"));

    QVBoxLayout* vLayout = new QVBoxLayout;

    Mysql_Connection connection(protocol);
    connection.openConnection();
    Mysql_Database* database = new Mysql_Database(QSqlDatabase::database(QLatin1String("Mysql")), protocol);
    GTXLQX_Record record;
    record.type = GTXLQX_Table;
    record.index = 1;
    record.lineName = "beijing";
    record.lineDirection = "north";
    record.exportState = "type 1";
    record.defectType = "query 1";
    record.defectName = "line";
    record.picturePath = "http://test.url";
    //database->delete_From(102);
    //for (int i = 0; i < 100; ++i) {
    // record.index = i;
    //  database->append_Into(record);
    //}
    //database->update();
    //database->commit();
    database->selectEx();
    Test_View* view = new Test_View(database);
    vLayout->addWidget(view);
    setLayout(vLayout);
  }

}
