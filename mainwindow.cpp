#include "product.h"
#include "common.h"
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

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
    ,mProtocol(protocol){
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
    setLayoutCentralWidget();
    addTitlebar();
    addDoorface();
    addMenubar();
    addContentWindow();
  }

  void GTXLQX_MainWindow::setLayoutCentralWidget() {
    QHBoxLayout* hLayout = new QHBoxLayout;
    mCentralWidget->setLayout(hLayout);
  }

  void GTXLQX_MainWindow::addTitlebar() {
    Titlebar* titlebar = new Titlebar;
    titlebar->setupUi(mProtocol);
    mCentralWidget->layout()->addWidget(titlebar);
  }

  void GTXLQX_MainWindow::addDoorface() {

  }

  void GTXLQX_MainWindow::addMenubar() {

  }

  void GTXLQX_MainWindow::addContentWindow() {

  }
}
