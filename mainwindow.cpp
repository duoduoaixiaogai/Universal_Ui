#include "product.h"
#include "common.h"
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Jinhui {
  /*
   * MainWindow
   */
  // cotr
  MainWindow::MainWindow(QWidget *parent)
    :Product()
    ,mMainWindow(QSharedPointer<QMainWindow>(new QMainWindow(parent)))
    ,mUi(QSharedPointer<Ui::MainWindow>(new Ui::MainWindow))
    ,mCentralWidget(new QWidget)
  {
    mUi->setupUi(mMainWindow.data());
    mMainWindow->setCentralWidget(mCentralWidget);
    //autoCreateMainWindow();
  }

  //MainWindow::~MainWindow()
  //{
  //  delete ui;
  //}

  /*
   * GTXLQX_MainWindow
   */
  // cotr
  GTXLQX_MainWindow::GTXLQX_MainWindow(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :MainWindow(parent)
    ,mProtocol(protocol)
    ,mVLayout(new QVBoxLayout)
  ,mTitleLayout(new QHBoxLayout)
  ,mDoorfaceLayout(new QHBoxLayout)
  ,mMenu_Content(new QHBoxLayout){
    setLayout();
    autoCreateMainWindow();
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
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool rimless = strToBool(pro->rimless);
    if (rimless) {
      mMainWindow->setWindowFlag(Qt::FramelessWindowHint);
    }
  }

  void GTXLQX_MainWindow::setMenubar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool menubar = strToBool(pro->menubar);
    if (!menubar) {
      mMainWindow->setMenuBar(nullptr);
    }
  }

  void GTXLQX_MainWindow::setStatusbar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool statusbar = strToBool(pro->statusbar);
    if (!statusbar) {
      mMainWindow->setStatusBar(nullptr);
    }
  }

  void GTXLQX_MainWindow::setMainWinMinSize() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->mainMinWidth.toInt();
    int minHeight = pro->mainMinHeight.toInt();
    mMainWindow->setMinimumSize(minWidth, minHeight);
  }

  void GTXLQX_MainWindow::setCentralWidget() {
    addTitlebar();
    addDoorface();
    addMenubar();
    addContentWindow();
  }

  void GTXLQX_MainWindow::setLayout() {
    mCentralWidget->setLayout(mVLayout);
    mVLayout->addLayout(mTitleLayout, 1);
    mVLayout->addLayout(mDoorfaceLayout, 4);
    mVLayout->addLayout(mMenu_Content, 50);
    //mLayout->setContentsMargins(8, 8, 8, 8);
  }

  void GTXLQX_MainWindow::addTitlebar() {
    Titlebar* titlebar = new Titlebar;
    titlebar->setMainWindow(QSharedPointer<GTXLQX_MainWindow>(this));
    mTitleLayout->addWidget(titlebar);
  }

  void GTXLQX_MainWindow::addDoorface() {
    Doorface_Label* doorfaceLabel = new Doorface_Label(mProtocol);
    mDoorfaceLayout->addWidget(doorfaceLabel);
  }

  void GTXLQX_MainWindow::addMenubar() {
    Menubar* menubar = new Menubar;
    menubar->setupUi(mProtocol);
    mMenu_Content->addWidget(menubar, 1);
  }

  void GTXLQX_MainWindow::addContentWindow() {
    ContentArea* contentArea = new ContentArea;
    mMenu_Content->addWidget(contentArea, 5);
  }
}
