#include "product.h"
#include "common.h"
#include "exception.h"
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Jinhui {
  /*
   * MainWindow
   */
  // cotr
  //MainWindow::MainWindow(QWidget *parent)
  //  :Product()
  //  ,mMainWindow(QSharedPointer<QMainWindow>(new QMainWindow(parent)))
  //  ,mUi(QSharedPointer<Ui::MainWindow>(new Ui::MainWindow))
  //  ,mCentralWidget(new QWidget)
  //{
  //  mUi->setupUi(mMainWindow.data());
  //  mMainWindow->setCentralWidget(mCentralWidget);
  //  //autoCreateMainWindow();
  //}

  //void MainWindow::setBackgroundColor() {}

  //MainWindow::~MainWindow()
  //{
  //  delete ui;
  //}

  /*
   * MainWindow类的重新实现
   */
  // cotr
  MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,mCentralWidget(new QWidget)
    ,mUi(new Ui::MainWindow) {
    mUi->setupUi(this);
    setCentralWidget(mCentralWidget);
  }

  MainWindow::~MainWindow() {
    if (mUi) {
      delete mUi;
      mUi = nullptr;
    }
  }

  void MainWindow::setBackgroundColor() {}

  void MainWindow::doDeleteLater(Product *obj) {
    MainWindow* mainWindow = dynamic_cast<MainWindow*>(obj);
    if (mainWindow) {
      mainWindow->deleteLater();
    }
  }

  /*
   * GTXLQX_MainWindow
   */
  // cotr
  GTXLQX_MainWindow::GTXLQX_MainWindow(QSharedPointer<const Protocol> uiPro,
                                       QSharedPointer<const Protocol> configPro, QWidget* parent)
    :MainWindow(parent)
    ,mUiPro(uiPro)
    ,mConfigPro(configPro)
    ,mVLayout(new QVBoxLayout)
    ,mTitleLayout(new QHBoxLayout)
    ,mDoorfaceLayout(new QHBoxLayout)
    ,mMenu_Content(new QHBoxLayout){
    setBackgroundColor();
    setLayout();
    autoCreateMainWindow();
    createConnect();
  }

  void GTXLQX_MainWindow::setBackgroundColor() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    setStyleSheet(pro->mainBackgroundCol);
  }

  GTXLQX_MainWindow::~GTXLQX_MainWindow() {}

  // automatically create the main window
  void GTXLQX_MainWindow::autoCreateMainWindow() {
    setMainWindowFlags();
    setMenubar();
    setStatusbar();
    setMainWinMinSize();
    setCentralWidget();
  }

  void GTXLQX_MainWindow::setMainWindowFlags() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    bool rimless = strToBool(pro->rimless);
    if (rimless) {
      setWindowFlag(Qt::FramelessWindowHint);
    }
  }

  void GTXLQX_MainWindow::setMenubar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    bool menubar = strToBool(pro->menubar);
    if (!menubar) {
      setMenuBar(nullptr);
    }
  }

  void GTXLQX_MainWindow::setStatusbar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    bool statusbar = strToBool(pro->statusbar);
    if (!statusbar) {
      setStatusBar(nullptr);
    }
  }

  void GTXLQX_MainWindow::setMainWinMinSize() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    int minWidth = pro->mainMinWidth.toInt();
    int minHeight = pro->mainMinHeight.toInt();
    setMinimumSize(minWidth, minHeight);
  }

  void GTXLQX_MainWindow::setCentralWidget() {
    addTitlebar();
    addDoorface();
    addMenubar();
    addContentWindow();
  }

  void GTXLQX_MainWindow::setLayout() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    mCentralWidget->setLayout(mVLayout);
    mVLayout->addLayout(mTitleLayout, pro->titlebarStretch.toInt());
    mVLayout->addLayout(mDoorfaceLayout, pro->doorfaceStretch.toInt());
    mVLayout->addLayout(mMenu_Content, pro->menuContentStretch.toInt());
    mVLayout->setSpacing(pro->mainwindowSpacing.toInt());
    QString separator = pro->separator;
    try {
      QStringList contentsMargins = pro->mainwindowContentsMargins.split(separator);
      if (4 != contentsMargins.count()) {
        throw IncorrectNumberParameters();
      }
      mVLayout->setContentsMargins(contentsMargins.at(0).toInt()
                                   ,contentsMargins.at(1).toInt()
                                   ,contentsMargins.at(2).toInt()
                                   ,contentsMargins.at(3).toInt());
      contentsMargins = pro->titlebarContentsMargins.split(separator);
      if (4 != contentsMargins.count()) {
        throw IncorrectNumberParameters();
      }
      mTitleLayout->setContentsMargins(contentsMargins.at(0).toInt()
                                       ,contentsMargins.at(1).toInt()
                                       ,contentsMargins.at(2).toInt()
                                       ,contentsMargins.at(3).toInt());
      contentsMargins = pro->doorfaceContentsMargins.split(separator);
      if (4 != contentsMargins.count()) {
        throw IncorrectNumberParameters();
      }
      mDoorfaceLayout->setContentsMargins(contentsMargins.at(0).toInt()
                                          ,contentsMargins.at(1).toInt()
                                          ,contentsMargins.at(2).toInt()
                                          ,contentsMargins.at(3).toInt());
      contentsMargins = pro->menuContentsMargins.split(separator);
      if (4 != contentsMargins.count()) {
        throw IncorrectNumberParameters();
      }
      mMenu_Content->setContentsMargins(contentsMargins.at(0).toInt()
                                        ,contentsMargins.at(1).toInt()
                                        ,contentsMargins.at(2).toInt()
                                        ,contentsMargins.at(3).toInt());

    } catch (ParameterException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }
    //mLayout->setContentsMargins(8, 8, 8, 8);
  }

  void GTXLQX_MainWindow::addTitlebar() {
    mTitlebar = new Titlebar;
    mTitlebar->setMainWindow(QSharedPointer<GTXLQX_MainWindow>(this));
    mTitlebar->setupUi(mUiPro);
    mTitleLayout->addWidget(mTitlebar);
  }

  void GTXLQX_MainWindow::addDoorface() {
    mDoorfaceLabel = new Doorface_Label(mUiPro);
    mDoorfaceLayout->addWidget(mDoorfaceLabel);
  }

  void GTXLQX_MainWindow::addMenubar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    mMenubar = new Menubar;
    mMenubar->setupUi(mUiPro);
    mMenu_Content->addWidget(mMenubar, pro->menubarStretch.toInt());
  }

  void GTXLQX_MainWindow::addContentWindow() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    mContentArea = new ContentArea(mConfigPro);
    mContentArea->setupUi(mUiPro);
    mMenu_Content->addWidget(mContentArea, pro->contentStretch.toInt());
  }

  void GTXLQX_MainWindow::createConnect() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    /*
     * 菜单栏
     */
    // 主菜单
    connect(mMenubar->mMenus.value(pro->menus.at(0).objectName), SIGNAL(clicked())
            ,this, SLOT(menu1Clicked()));
    connect(mMenubar->mMenus.value(pro->menus.at(1).objectName), SIGNAL(clicked())
            ,this, SLOT(menu2Clicked()));
    connect(mMenubar->mMenus.value(pro->menus.at(2).objectName), SIGNAL(clicked())
            ,this, SLOT(menu3Clicked()));
    // 子菜单
    // 菜单项
    // 四分屏
    connect(mMenubar->mSubmenus.value(pro->menus.at(0).subMenu.objectName)
            ->mMenuItems.value(pro->menus.at(0).subMenu.itemsName.at(0).objectName), SIGNAL(clicked())
            ,this, SLOT(menu1Submenu1Item1Clicked()));
    // MySQL数据库表格展示
    connect(mMenubar->mSubmenus.value(pro->menus.at(1).subMenu.objectName)
            ->mMenuItems.value(pro->menus.at(1).subMenu.itemsName.at(1).objectName), SIGNAL(clicked())
            ,this, SLOT(menu2Submenu1Item2Clicked()));
    // 32路显示
    connect(mMenubar->mSubmenus.value(pro->menus.at(2).subMenu.objectName)
            ->mMenuItems.value(pro->menus.at(2).subMenu.itemsName.at(0).objectName), SIGNAL(clicked())
            ,this, SLOT(menu3Submenu1Item1Clicked()));
    /*
     * 内容区
     */

  }

  // public slots
  void GTXLQX_MainWindow::menu1Clicked() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    SubMenu* subMenu = mMenubar->mSubmenus.value(pro->menus.at(0).subMenu.objectName);
    if (subMenu) {
      mMenubar->hideAllSubmenus();
      subMenu->show();
    }
  }

  void GTXLQX_MainWindow::menu2Clicked() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    SubMenu* subMenu = mMenubar->mSubmenus.value(pro->menus.at(1).subMenu.objectName);
    if (subMenu) {
      mMenubar->hideAllSubmenus();
      subMenu->show();
    }
  }

  void GTXLQX_MainWindow::menu3Clicked() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    SubMenu* subMenu = mMenubar->mSubmenus.value(pro->menus.at(2).subMenu.objectName);
    if (subMenu) {
      mMenubar->hideAllSubmenus();
      subMenu->show();
    }
  }

  void GTXLQX_MainWindow::menu1Submenu1Item1Clicked() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    Widget* widget = mContentArea->mWidgetsIndex.value(QLatin1String("quadScreen"));
    if (widget) {
      mContentArea->showSpecifiedWidget(widget);
    }
  }

  void GTXLQX_MainWindow::menu2Submenu1Item2Clicked() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    Widget* widget = mContentArea->mWidgetsIndex.value(QLatin1String("reviewResultQuery"));
    if (widget) {
      mContentArea->showSpecifiedWidget(widget);
    }
  }

  void GTXLQX_MainWindow::menu3Submenu1Item1Clicked() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mUiPro);

    Widget* widget = mContentArea->mWidgetsIndex.value(QLatin1String("splitScreenDisplay32Channel"));
    if (widget) {
      mContentArea->showSpecifiedWidget(widget);
    }
  }
}
