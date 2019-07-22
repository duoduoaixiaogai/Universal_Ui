/*******************************************************************************
* Description: 小部件实现类(每种小部件都是一个载体，具体想要什么样的界面可以自己设计最后添加到小部件上就行)
* Author: Niu yi qun
* Creation date: 2019/6/25
* Last modified person: Niu yi qun
* Last modified date: 2019/6/25
******************************************************************************/
#include "include/product.h"
#include "include/common.h"
#include "include/exception.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QStackedWidget>
#include <QSplitter>

// ui
#include <QDateTimeEdit>

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

  void Widget::setupUi() {}

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
    ReviewResultQuery_Widget* revResQueWidget = new ReviewResultQuery_Widget;
    revResQueWidget->setupUi(mConfigPro);
    addWidgetInContentArea(revResQueWidget);
    SplitScreenDisplay32Channel* display32Channel = new SplitScreenDisplay32Channel;
    display32Channel->setupUi(protocol);
    addWidgetInContentArea(display32Channel);
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
  //Test_Widget::Test_Widget(QWidget* parent)
  //  :Widget(parent) {}

  //void Test_Widget::setupUi(QSharedPointer<const Protocol> protocol) {
  //  setObjectName(QLatin1String("testWidget"));

  //  QVBoxLayout* vLayout = new QVBoxLayout;

  //  Mysql_Connection connection(protocol);
  //  connection.openConnection();
  //  Mysql_Database* database = new Mysql_Database(QSqlDatabase::database(QLatin1String("Mysql")), protocol);
  //  GTXLQX_Record record;
  //  record.type = GTXLQX_Table;
  //  record.index = 1;
  //  record.lineName = "beijing";
  //  record.lineDirection = "north";
  //  record.exportState = "type 1";
  //  record.defectType = "query 1";
  //  record.defectName = "line";
  //  record.picturePath = "http://test.url";
  //  //database->delete_From(102);
  //  //for (int i = 0; i < 100; ++i) {
  //  // record.index = i;
  //  //  database->append_Into(record);
  //  //}
  //  //database->update();
  //  //database->commit();
  //  database->selectEx();
  //  Test_View* view = new Test_View(database);
  //  vLayout->addWidget(view);
  //  setLayout(vLayout);
  //}

  /*
   * ReviewResultQuery_Widget
   */
  // cotr
  ReviewResultQuery_Widget::ReviewResultQuery_Widget(QWidget* parent)
    :Widget(parent) {}

  ReviewResultQuery_Widget::~ReviewResultQuery_Widget() {}

  void ReviewResultQuery_Widget::setupUi(QSharedPointer<const Protocol> protocol) {
    setObjectName(QLatin1String("reviewResultQuery"));

    Mysql_Connection connection(protocol);
    connection.openConnection();
    mDatabase = QSharedPointer<Database>(new MySQL_Database(protocol, connection.getConnectionName()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* upLayout = new QHBoxLayout;
    QHBoxLayout* queryLayout = new QHBoxLayout;
    QVBoxLayout* leftQueryLayout = new QVBoxLayout;
    QVBoxLayout* left1QueryLayout = new QVBoxLayout;
    QVBoxLayout* midQueryLayout = new QVBoxLayout;
    QVBoxLayout* mid1QueryLayout = new QVBoxLayout;
    QVBoxLayout* rightQueryLayout = new QVBoxLayout;
    QHBoxLayout* rigUpQueryLayout = new QHBoxLayout;
    QHBoxLayout* rigBotQueryLayout = new QHBoxLayout;
    QVBoxLayout* pictureLayout = new QVBoxLayout;
    QHBoxLayout* viewLayout = new QHBoxLayout;
    QHBoxLayout* operLayout = new QHBoxLayout;
    QHBoxLayout* progressLayout = new QHBoxLayout;

    mLineName_Label = new Label(tr("Line name:"));
    mLineName_Combobox = new ComboBox;
    mLineDirection_Label = new Label(tr("Line direction:"));
    mLineDirection_Combobox = new ComboBox;
    mExportState_Label = new Label(tr("Export state:"));
    mExportState_Combobox = new ComboBox;
    mDefectName_Label = new Label(tr("Defect name:"));
    mDefectName_Combobox = new ComboBox;
    mAuditType_Label = new Label(tr("Audit type:"));
    mAuditType_Combobox = new ComboBox;
    mStartTime_Label = new Label(tr("Start time:"));
    mStartTime_TimeEdit = new QDateTimeEdit;
    mEndTime = new Label(tr("End time:"));
    mEndTime_TimeEdit = new QDateTimeEdit;
    mQuery_Btn = new PushButton(tr("Query"));
    mCount_Label = new Label(tr("0"));
    mTotal_Label = new Label(tr("Total:"));

    leftQueryLayout->addWidget(mLineName_Label);
    leftQueryLayout->addWidget(mDefectName_Label);
    leftQueryLayout->addWidget(mStartTime_Label);

    left1QueryLayout->addWidget(mLineName_Combobox);
    left1QueryLayout->addWidget(mDefectName_Combobox);
    left1QueryLayout->addWidget(mStartTime_TimeEdit);

    midQueryLayout->addWidget(mLineDirection_Label );
    midQueryLayout->addWidget(mAuditType_Label);
    midQueryLayout->addWidget(mEndTime);

    mid1QueryLayout->addWidget(mLineDirection_Combobox );
    mid1QueryLayout->addWidget(mAuditType_Combobox);
    mid1QueryLayout->addWidget(mEndTime_TimeEdit);

    rigUpQueryLayout->addWidget(mExportState_Label);
    rigUpQueryLayout->addWidget(mExportState_Combobox);


    rigBotQueryLayout->addWidget(mQuery_Btn);
    rigBotQueryLayout->addWidget(mTotal_Label);
    rigBotQueryLayout->addWidget(mCount_Label);

    rightQueryLayout->addLayout(rigUpQueryLayout);
    rightQueryLayout->addStretch();
    rightQueryLayout->addLayout(rigBotQueryLayout);

    mPicture_Label = new Label;
    pictureLayout->addWidget(mPicture_Label);

    mView = new DatabaseTable_View;
    viewLayout->addWidget(mView);

    PushButton* selectAll_Btn = new PushButton(tr("Select all"));
    PushButton* exportSelecteds  = new PushButton(tr("Export selecteds"));
    PushButton* exportAll = new PushButton(tr("Export all"));
    PushButton* prePage = new PushButton(tr("Previous page"));
    PushButton* nextPage = new PushButton(tr("Next page"));
    operLayout->addStretch();
    operLayout->addWidget(selectAll_Btn);
    operLayout->addStretch();
    operLayout->addWidget(exportSelecteds);
    operLayout->addStretch();
    operLayout->addWidget(exportAll);
    operLayout->addStretch();
    operLayout->addWidget(prePage);
    operLayout->addStretch();
    operLayout->addWidget(nextPage);
    operLayout->addStretch();

    ProgressBar* proBar = new ProgressBar;
    progressLayout->addWidget(proBar);

    queryLayout->addLayout(leftQueryLayout);
    queryLayout->addLayout(left1QueryLayout);
    queryLayout->addLayout(midQueryLayout);
    queryLayout->addLayout(mid1QueryLayout);
    queryLayout->addLayout(rightQueryLayout);
    upLayout->addLayout(queryLayout);
    upLayout->addStretch();
    upLayout->addLayout(pictureLayout);
    mainLayout->addLayout(upLayout);
    mainLayout->addLayout(viewLayout, 1);
    mainLayout->addLayout(operLayout);
    mainLayout->addLayout(progressLayout);
    setLayout(mainLayout);

    mModel = new GTXLQX_Model;
    mView->setModel(mModel);

    createConnection();
  }

  void ReviewResultQuery_Widget::createConnection() {
    connect(mQuery_Btn, SIGNAL(clicked()), this, SLOT(queryBtnClicked()));
  }

  void ReviewResultQuery_Widget::queryBtnClicked() {
    qSharedPointerDynamicCast<MySQL_Database, Database>(mDatabase)->selectAll();
    QVector<Record> records = mDatabase->getData(mModel->getHeader());
    //mModel->updateModel(mDatabase->getData(mModel->getHeader()));
    QList<Record> records1 = records.toList();
    dynamic_cast<GTXLQX_Model*>(mModel)->showReviewResult(records1);
  }

  /*
   * SplitScreenDisplay32Channel
   */
  // cotr
  SplitScreenDisplay32Channel::SplitScreenDisplay32Channel(QWidget* parent)
    :Widget(parent)
    ,mItem(nullptr)
    ,mController(new Channel32_Controller){
    //connect(&mTimer, SIGNAL(timeout()), this, SLOT(timeouted()));
    connect(dynamic_cast<Channel32_Controller*>(mController.data())->mWorker, SIGNAL(resultReady(QVariantHash))
            ,this, SLOT(handleResults(QVariantHash)));
    connect(dynamic_cast<Channel32_Controller*>(mController.data()), SIGNAL(operate())
            ,dynamic_cast<Channel32_Controller*>(mController.data())->mWorker, SLOT(doWork()));
  }

  SplitScreenDisplay32Channel::~SplitScreenDisplay32Channel() {}

  void SplitScreenDisplay32Channel::setupUi(QSharedPointer<const Protocol> protocol) {
    //mH1Splitter = new QSplitter;
    //mH2Splitter = new QSplitter;
    //mH3Splitter = new QSplitter;
    //mH4Splitter = new QSplitter;
    //mH5Splitter = new QSplitter;
    //mH6Splitter = new QSplitter;
    //mH7Splitter = new QSplitter;
    //mH8Splitter = new QSplitter;

    //QSplitter* vSplitter = new QSplitter;
    //vSplitter->setOrientation(Qt::Vertical);
    //vSplitter->addWidget(mH1Splitter);
    //vSplitter->addWidget(mH2Splitter);
    //vSplitter->addWidget(mH3Splitter);
    //vSplitter->addWidget(mH4Splitter);
    //vSplitter->addWidget(mH5Splitter);
    //vSplitter->addWidget(mH6Splitter);
    //vSplitter->addWidget(mH7Splitter);
    //vSplitter->addWidget(mH8Splitter);


    //QSplitter* h1Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h2Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h3Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h4Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h5Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h6Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h7Splitter = new QSplitter(Qt::Vertical);
    //QSplitter* h8Splitter = new QSplitter(Qt::Vertical);
    //mHSplitters.append(h1Splitter);
    //mHSplitters.append(h2Splitter);
    //mHSplitters.append(h3Splitter);
    //mHSplitters.append(h4Splitter);
    //mHSplitters.append(h5Splitter);
    //mHSplitters.append(h6Splitter);
    //mHSplitters.append(h7Splitter);
    //mHSplitters.append(h8Splitter);

    //QSplitter* vSplitter = new QSplitter;
    //vSplitter->setOrientation(Qt::Vertical);
    //vSplitter->addWidget(h1Splitter);
    //vSplitter->addWidget(h2Splitter);
    //vSplitter->addWidget(h3Splitter);
    //vSplitter->addWidget(h4Splitter);
    //vSplitter->addWidget(h5Splitter);
    //vSplitter->addWidget(h6Splitter);
    //vSplitter->addWidget(h7Splitter);
    //vSplitter->addWidget(h8Splitter);

    //for (int i = 0; i < mRows; ++i) {
    //  QSplitter* hSplitter = mHSplitters.at(0);
    //  for (int j = 0; j < mColumns; ++j) {
    //    OnewayDisplay* display = new OnewayDisplay;
    //    hSplitter->addWidget(display);
    //  }
    //}

    //QHBoxLayout* mainLayout = new QHBoxLayout;
    //mainLayout->addWidget(vSplitter);
    //setLayout(mainLayout);

    setObjectName(QLatin1String("splitScreenDisplay32Channel"));

    populateScene();

    int index = 0;
    RowsColumns rowsColumns = splitScreenToSize(THIRTYTWO);
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    for (int i = 0; i < rowsColumns.rows; ++i) {
      for (int j = 0; j < rowsColumns.columns; ++j) {
        Channel_Frame* channel = new Channel_Frame;
        channel->setupUi(protocol);
        channel->view()->setScene(mScene);
        channel->setItem(mItems.value(index));
        mainLayout->addWidget(channel, i, j);
        mChannels.append(channel);
        ++index;
      }
    }

    setLayout(mainLayout);
    //const std::string videoStreamAddress = "rtsp://admin:ferret123@192.168.8.31:554/main/Channels/1";
    //cv::VideoCapture vcap;
    //vcap.open(videoStreamAddress);
    //while (true) {
    //  cv::Mat frame;
    //  vcap >> frame;
    //  cv::imshow("pic", frame);
    //  cv::waitKey(30);
    //}
    //mTimer.start(40);
    emit dynamic_cast<Channel32_Controller*>(mController.data())->operate();
  }

  void SplitScreenDisplay32Channel::timeouted() {
    //QPixmap oriPixmap("D:\\NYQProject\\UniversalUI\\11.jpg");

    //mScene->addPixmap(QPixmap("D:\\NYQProject\\UniversalUI\\11.jpg"));
    //if (mItem) {
    //  mScene->removeItem(mItem);
    //  delete mItem;
    //  mItem = nullptr;
    //}
    //cv::Mat frame;
    //vcap >> frame;
    //QPixmap oriPixmap = mConv.cvMatToQPixmap(frame);
    ////mItem = mScene->addPixmap(oriPixmap);
    //for(int i = 0; i < mRows * mColumns; ++i) {
    //  QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(mItems.value(i));
    //  if (pixmapItem) {
    //    pixmapItem->setPixmap(oriPixmap);
    //  }
    //}
  }

  void SplitScreenDisplay32Channel::populateScene() {
    mScene = new Channel32_Scene(this);

    RowsColumns rowsColumns = splitScreenToSize(THIRTYTWO);
    for(int i = 0; i < rowsColumns.rows * rowsColumns.columns; ++i) {
      //mItems[i] = dynamic_cast<GraphicsPixmapItem*>(mScene->addPixmap(QPixmap(resolutionToSize(P1080))));
      //QGraphicsPixmapItem* item = mScene->addPixmap(QPixmap(resolutionToSize(P1080)));
      mItems[i] = static_cast<GraphicsPixmapItem*>(mScene->addPixmap(QPixmap(resolutionToSize(P1080))));
    }
  }

  // public slots
  void SplitScreenDisplay32Channel::handleResults(QVariantHash pixmaps) {
    RowsColumns rowsColumns = splitScreenToSize(THIRTYTWO);
    try {
      if (rowsColumns.rows * rowsColumns.columns != pixmaps.size()) {
        throw ContainerItemsNumIncorrect();
      }
    } catch (ContainerException& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
      return;
    }

    for(int i = 0; i < rowsColumns.rows * rowsColumns.columns; ++i) {
      QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(mItems.value(i));
      if (pixmapItem) {
        pixmapItem->setPixmap(pixmaps.value(QString::number(i)).value<QPixmap>());
      }
    }
  }

  /*
   * IVMS4200Menubar_Widget
   */
  // cotr
  IVMS4200Menubar_Widget::IVMS4200Menubar_Widget(QWidget* parent)
    :Widget(parent) {
    connect(this, SIGNAL(addMenuFront_Signal()), this, SLOT(addMenuFront_Slot()));
  }

  IVMS4200Menubar_Widget::~IVMS4200Menubar_Widget() {}

  void IVMS4200Menubar_Widget::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
  }

  void IVMS4200Menubar_Widget::addMenuFront(IVMS4200Menu_Widget* menu) {
    addMenuStack(menu);
    emit addMenuFront_Signal();
  }

  void IVMS4200Menubar_Widget::setMenuBarMainButton(IVMS4200MenuBarMainBtn_Widget* mainBtn) {
    mMainLayout->insertWidget(0, mainBtn);
  }

  void IVMS4200Menubar_Widget::cancelMenuBarMainButton(IVMS4200MenuBarMainBtn_Widget* mainBtn) {
    mMainLayout->removeWidget(mainBtn);
  }

  void IVMS4200Menubar_Widget::cancelMenuBarMainButton(const int index) {
    mMainLayout->removeWidget(mMainLayout->itemAt(index)->widget());
  }

  // public slots
  void IVMS4200Menubar_Widget::addMenuFront_Slot() {
    IVMS4200Menu_Widget* menu = mMenusStack.pop();
    // 首元素
    if (mMenusStack.isEmpty()) {
      menu->mPreSeparator->setupUi(QSharedPointer<const Protocol>());
      mMainLayout->insertWidget(0, menu->mPreSeparator);
      mMainLayout->insertWidget(0, menu);
      menu->mNextSeparator->setupUi(QSharedPointer<const Protocol>());
      mMainLayout->insertWidget(0, menu->mNextSeparator);
    } else {
      mMainLayout->insertWidget(1, menu);
      mMainLayout->insertWidget(1, menu->mPreSeparator);
    }
    mMenusStack.push(menu);
  }

  // protected
  void IVMS4200Menubar_Widget::addMenuStack(IVMS4200Menu_Widget* menu) {
    // 首元素
    if (mMenusStack.isEmpty()) {
      menu->mPreItem = nullptr;
      menu->mNextItem = nullptr;
      menu->mPreSeparator = new IVMS4200MenuBarSeparator_Widget;
      menu->mNextSeparator = new IVMS4200MenuBarSeparator_Widget;
    } else {
      IVMS4200Menu_Widget* lastMenu = mMenusStack.pop();
      menu->mPreItem = nullptr;
      menu->mNextItem = lastMenu;
      menu->mPreSeparator = new IVMS4200MenuBarSeparator_Widget;
      menu->mNextSeparator = lastMenu->mPreSeparator;

      lastMenu->mPreItem = menu;

      mMenusStack.push(lastMenu);
    }

    mMenusStack.push(menu);
  }

  void IVMS4200Menubar_Widget::initWindow() {
    setFixedHeight(30);
  }

  void IVMS4200Menubar_Widget::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
    mMainLayout->addStretch();
  }

  /*
   * IVMS4200Menu_Widget
   */
  // cotr
  IVMS4200Menu_Widget::IVMS4200Menu_Widget(QWidget* parent)
    :Widget(parent)
    ,mPreItem(nullptr)
    ,mNextItem(nullptr) {}

  IVMS4200Menu_Widget::~IVMS4200Menu_Widget() {}

  void IVMS4200Menu_Widget::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* IVMS4200Menu_Widget::iconLabel() const {
    return mIcon;
  }

  Label* IVMS4200Menu_Widget::contentLabel() const {
    return mContent;
  }

  Label* IVMS4200Menu_Widget::closeLabel() const {
    return mClose;
  }

  Label* IVMS4200Menu_Widget::colorBarLabel() const {
    return mColorBar;
  }

  // protected
  void IVMS4200Menu_Widget::initWindow() {
    setMaximumWidth(170);
    setStyleSheet(QString("background-color:black"));
  }
  void IVMS4200Menu_Widget::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mContentLayout = new QHBoxLayout;
    mColorBarLayout = new QHBoxLayout;
    mMainLayout->setSpacing(0);
    mMainLayout->addLayout(mContentLayout);
    mMainLayout->addLayout(mColorBarLayout);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    //mContentLayout->setContentsMargins(4, 4, 4, 4);
    mColorBarLayout->setContentsMargins(0, 0, 0, 0);
  }

  void IVMS4200Menu_Widget::init() {
    mIcon = new Label;
    mContent = new Label;
    mClose = new Label;
    mColorBar = new Label;
    mColorBar->setFixedHeight(3);
    mColorBar->setStyleSheet(QString("background-color:red"));
    mContentLayout->addStretch();
    mContentLayout->addWidget(mIcon);
    mContentLayout->addStretch();
    mContentLayout->addWidget(mContent);
    mContentLayout->addStretch();
    mContentLayout->addWidget(mClose);
    mContentLayout->addStretch();
    mColorBarLayout->addWidget(mColorBar);
  }

  /*
   * IntrusionDetection_Window
   */
  // cotr
  IntrusionDetection_MainWindow::IntrusionDetection_MainWindow(QWidget* parent)
    :Widget(parent) {}

  IntrusionDetection_MainWindow::~IntrusionDetection_MainWindow() {}

  void IntrusionDetection_MainWindow::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  IVMS4200TitleBar_Widget* IntrusionDetection_MainWindow::titleBar() const {
    return dynamic_cast<IVMS4200TitleBar_Widget*>(mTitleBar);
  }

  IVMS4200Menubar_Widget* IntrusionDetection_MainWindow::menuBar() const {
    return dynamic_cast<IVMS4200Menubar_Widget*>(mMenuBar);
  }

  IVMS4200ContentArea_Widget* IntrusionDetection_MainWindow::contentArea() const {
    return dynamic_cast<IVMS4200ContentArea_Widget*>(mContentArea);
  }

  IVMS4200StatusBar_Widget* IntrusionDetection_MainWindow::statusBar() const {
    return dynamic_cast<IVMS4200StatusBar_Widget*>(mStatusBar);
  }

  void IntrusionDetection_MainWindow::addMenuFront(IVMS4200Menu_Widget* menu) {
    dynamic_cast<IVMS4200Menubar_Widget*>(mMenuBar)->addMenuFront(menu);
  }

  void IntrusionDetection_MainWindow::insertMenu(const int index, IVMS4200Menu_Widget* menu) {

  }

  // protected
  void IntrusionDetection_MainWindow::setMenuBar(Widget *menuBar) {
    mMenuLayout->addWidget(menuBar);
  }

  void IntrusionDetection_MainWindow::setTitleBar(Widget *titleBar) {
    mTitleLayout->addWidget(titleBar);
  }

  void IntrusionDetection_MainWindow::setContentArea(Widget* contentArea) {
    mContentLayout->addWidget(contentArea);
  }

  void IntrusionDetection_MainWindow::setStatusBar(Widget* statusBar) {
    mStatusBarLayout->addWidget(statusBar);
  }

  void IntrusionDetection_MainWindow::initWindow() {
    setWindowFlag(Qt::FramelessWindowHint);
    setMinimumSize(QSize(1000, 800));
  }

  void IntrusionDetection_MainWindow::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mTitleLayout = new QHBoxLayout;
    mMenuLayout = new QHBoxLayout;
    mContentLayout = new QHBoxLayout;
    mStatusBarLayout = new QHBoxLayout;
    mMainLayout->addLayout(mTitleLayout);
    mMainLayout->addLayout(mMenuLayout);
    mMainLayout->addLayout(mContentLayout);
    mMainLayout->addLayout(mStatusBarLayout);

    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mTitleLayout->setContentsMargins(0, 0, 0, 0);
    mMenuLayout->setContentsMargins(0, 0, 0, 0);
    mStatusBarLayout->setContentsMargins(0, 0, 0, 0);
  }

  void IntrusionDetection_MainWindow::init() {
    mTitleBar = new IVMS4200TitleBar_Widget;
    mTitleBar->setupUi(QSharedPointer<const Protocol>());
    mMenuBar = new IVMS4200Menubar_Widget;
    mMenuBar ->setupUi(QSharedPointer<const Protocol>());
    mContentArea = new IVMS4200ContentArea_Widget;
    mContentArea->setupUi(QSharedPointer<const Protocol>());
    mStatusBar = new IVMS4200StatusBar_Widget;
    mStatusBar->setupUi(QSharedPointer<const Protocol>());

    setTitleBar(mTitleBar);
    setMenuBar(mMenuBar);
    setContentArea(mContentArea);
    setStatusBar(mStatusBar);
  }

  /*
   * IVMS4200TitleBar_Widget
   */
  // cotr
  IVMS4200TitleBar_Widget::IVMS4200TitleBar_Widget(QWidget* parent)
    :Widget(parent) {
    initWindow();
  }

  IVMS4200TitleBar_Widget::~IVMS4200TitleBar_Widget() {}

  void IVMS4200TitleBar_Widget::initWindow() {
    setFixedHeight(40);
  }

  /*
   * IVMS4200ContentArea_Widget
   */
  // cotr
  IVMS4200ContentArea_Widget::IVMS4200ContentArea_Widget(QWidget* parent) {
  }

  IVMS4200ContentArea_Widget::~IVMS4200ContentArea_Widget() {}

  /*
   * IVMS4200StatusBar_Widget
   */
  // cotr
  IVMS4200StatusBar_Widget::IVMS4200StatusBar_Widget(QWidget* parent) {
    void initWindow();
  }

  IVMS4200StatusBar_Widget::~IVMS4200StatusBar_Widget() {}

  void IVMS4200StatusBar_Widget::initWindow() {
    setFixedHeight(50);
  }

  /*
   * IVMSMenuBarMainBtn
   */
  // cotr
  IVMS4200MenuBarMainBtn_Widget::IVMS4200MenuBarMainBtn_Widget(QWidget* parent)
    :Widget(parent) {}

  IVMS4200MenuBarMainBtn_Widget::~IVMS4200MenuBarMainBtn_Widget() {}

  /*
   * IVMS4200MenuBarSeparator_Widget
   */
  // cotr
  IVMS4200MenuBarSeparator_Widget::IVMS4200MenuBarSeparator_Widget(QWidget* parent)
    :Widget(parent) {

  }

  IVMS4200MenuBarSeparator_Widget::~IVMS4200MenuBarSeparator_Widget() {}

  void IVMS4200MenuBarSeparator_Widget::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  // protected
  void IVMS4200MenuBarSeparator_Widget::initWindow() {
    setFixedWidth(5);
  }

  void IVMS4200MenuBarSeparator_Widget::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
  }

  void IVMS4200MenuBarSeparator_Widget::init() {
    mLabel = new Label;
    mLabel->setFixedHeight(20);
    mLabel->setStyleSheet(QString("background-color:green"));
    mMainLayout->addWidget(mLabel);
    mMainLayout->addStretch();
  }

}
