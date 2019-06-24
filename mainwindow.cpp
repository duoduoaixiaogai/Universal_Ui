#include "product.h"
#include "common.h"
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

namespace Jinhui {
  /*
   * MainWindow
   */
  // cotr
  MainWindow::MainWindow(QWidget *parent)
    :Product(parent)
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
   * MainWindow_GTXLQX
   */
  // cotr
  MainWindow_GTXLQX::MainWindow_GTXLQX(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :MainWindow(parent)
    ,mProtocol(protocol){
    autoCreateMainWindow();
  }

  MainWindow_GTXLQX::~MainWindow_GTXLQX() {}

  // automatically create the main window
  void MainWindow_GTXLQX::autoCreateMainWindow() {
    setMainWindowFlags();
    setMenubar();
    setStatusbar();
    setMainWinMinSize();
    setCentralWidget();
  }

  void MainWindow_GTXLQX::setMainWindowFlags() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool rimless = strToBool(pro->rimless);
    if (rimless) {
      mMainWindow->setWindowFlag(Qt::FramelessWindowHint);
    }
  }

  void MainWindow_GTXLQX::setMenubar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool menubar = strToBool(pro->menubar);
    if (!menubar) {
      mMainWindow->setMenuBar(nullptr);
    }
  }

  void MainWindow_GTXLQX::setStatusbar() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool statusbar = strToBool(pro->statusbar);
    if (!statusbar) {
      mMainWindow->setStatusBar(nullptr);
    }
  }

  void MainWindow_GTXLQX::setMainWinMinSize() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->mainMinWidth.toInt();
    int minHeight = pro->mainMinHeight.toInt();
    mMainWindow->setMinimumSize(minWidth, minHeight);
  }

  void MainWindow_GTXLQX::setCentralWidget() {

  }
}
