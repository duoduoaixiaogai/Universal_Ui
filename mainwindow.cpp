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

  void MainWindow::setBackgroundColor() {}

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
    setBackgroundColor();
    setLayout();
    autoCreateMainWindow();
  }

  void GTXLQX_MainWindow::setBackgroundColor() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    mMainWindow->setStyleSheet(pro->mainBackgroundCol);
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
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

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
    Titlebar* titlebar = new Titlebar;
    titlebar->setMainWindow(QSharedPointer<GTXLQX_MainWindow>(this));
    titlebar->setupUi(mProtocol);
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
    contentArea->setupUi(mProtocol);
    mMenu_Content->addWidget(contentArea, 5);
  }
}
