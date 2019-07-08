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
    ,mRows(8)
    ,mColumns(4)
    ,mItem(nullptr) {
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(timeouted()));
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

    mScene = new Channel32_Scene(this);

    QGridLayout* mainLayout = new QGridLayout;
    for (int i = 0; i < mRows; ++i) {
      for (int j = 0; j < mColumns; ++j) {
        Channel_Frame* channel = new Channel_Frame;
        channel->setupUi(protocol);
        channel->view()->setScene(mScene);
        mainLayout->addWidget(channel, i, j);
        mChannels.append(channel);
      }
    }

    setLayout(mainLayout);
    const std::string videoStreamAddress = "rtsp://admin:ferret123@192.168.8.31:554/main/Channels/1";
    //cv::VideoCapture vcap;
    vcap.open(videoStreamAddress);
    //while (true) {
    //  cv::Mat frame;
    //  vcap >> frame;
    //  cv::imshow("pic", frame);
    //  cv::waitKey(30);
    //}
    mTimer.start(40);
  }

  void SplitScreenDisplay32Channel::timeouted() {
    //QPixmap oriPixmap("D:\\NYQProject\\UniversalUI\\11.jpg");

    //mScene->addPixmap(QPixmap("D:\\NYQProject\\UniversalUI\\11.jpg"));
    if (mItem) {
      mScene->removeItem(mItem);
      delete mItem;
      mItem = nullptr;
    }
    cv::Mat frame;
    vcap >> frame;
    QPixmap oriPixmap = mConv.cvMatToQPixmap(frame);
    mItem = mScene->addPixmap(oriPixmap);
  }
}
