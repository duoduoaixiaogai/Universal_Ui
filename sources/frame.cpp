/*******************************************************************************
* Description: 拥有框架的小部件的基类
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#include "include/product.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QDateTimeEdit>

namespace Jinhui {
  /*
   * Frame
   */
  // cotr
  Frame::Frame(QWidget* parent)
    :QFrame(parent) {}

  void Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    Q_UNUSED(protocol);
  }

  /*
   * OnewayDisplay
   */
  // cotr
  Channel_Frame::Channel_Frame(QWidget* parent)
    :Frame(parent) {
    setFrameStyle(QFrame::WinPanel | QFrame::Plain);
  }

  Channel_Frame::~Channel_Frame() {}

  Channel_Frame::Channel_Frame(const Channel_Frame& other) {
    QPixmap otherPixmap = other.view()->getItem()->pixmap();

    mView = new GraphicsView;
    GraphicsPixmapItem* pixmapItem = new GraphicsPixmapItem(otherPixmap);
    mView->setItem(pixmapItem);
  }

  void Channel_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mView = new Channel_View;
    mainLayout->addWidget(mView);
    setLayout(mainLayout);
  }

  GraphicsView* Channel_Frame::view() const {
    return mView;
  }

  void Channel_Frame::setItem(GraphicsPixmapItem* item) {
    mView->setItem(item);
  }

  /*
   * IVMS4200MenuEx_Frame
   */
  // cotr
  IVMS4200MenuEx_Frame::IVMS4200MenuEx_Frame(QWidget* parent)
    :Frame(parent)
    ,mPreItem(nullptr)
    ,mNextItem(nullptr) {}

  IVMS4200MenuEx_Frame::~IVMS4200MenuEx_Frame() {}

  void IVMS4200MenuEx_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void IVMS4200MenuEx_Frame::setMenuBar(Widget* menuBar) {
    mMenuBar = menuBar;
  }

  void IVMS4200MenuEx_Frame::setTextAlignment(Qt::Alignment alignment) {
    mTextLayout->setAlignment(mContent, alignment);
  }

  Label* IVMS4200MenuEx_Frame::iconLabel() const {
    return mIcon;
  }

  Label* IVMS4200MenuEx_Frame::contentLabel() const {
    return mContent;
  }

  Label* IVMS4200MenuEx_Frame::closeLabel() const {
    return mClose;
  }

  Label* IVMS4200MenuEx_Frame::colorBarLabel() const {
    return mColorBar;
  }

  // public slots:
  void IVMS4200MenuEx_Frame::restoreDefShowMenu() {
    //setStyleSheet(ivms4200MenuEx_FrameBackground);
  }

  void IVMS4200MenuEx_Frame::getNextActiveMenu() {
    QString activeMenu;
    if (mPreItem) {
      activeMenu = mPreItem->productName();
    } else if (mNextItem) {
      activeMenu = mNextItem->productName();
    } else {
      activeMenu = dynamic_cast<IVMS4200Menubar_Widget*>(mMenuBar)->getMenuBarMainButton()->productName();
    }

    emit activeMenuEx(activeMenu);
  }

  void IVMS4200MenuEx_Frame::closeMenu() {
    emit closeMenu(this);
    getNextActiveMenu();
  }

  // protected
  void IVMS4200MenuEx_Frame::initWindow() {
  }

  void IVMS4200MenuEx_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mContentLayout = new QHBoxLayout;
    mIconLayout = new QHBoxLayout;
    mTextLayout = new QHBoxLayout;
    mCloseLayout = new QHBoxLayout;
    mColorBarLayout = new QHBoxLayout;
    mMainLayout->addLayout(mContentLayout);
    mMainLayout->addLayout(mColorBarLayout);
    mMainLayout->setSpacing(0);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mContentLayout->addLayout(mIconLayout);
    mContentLayout->addLayout(mTextLayout);
    mContentLayout->addLayout(mCloseLayout);
    mContentLayout->setSpacing(10);
    mContentLayout->setContentsMargins(10, 4, 10, 4);
    mColorBarLayout->setContentsMargins(0, 0, 0, 0);
  }

  void IVMS4200MenuEx_Frame::init() {
    mIcon = new Label;
    mContent = new Label;
    mClose = new DealWithMouseEventEx_Label;
    mColorBar = new Label;
    //mContentLayout->addStretch();
    //mContentLayout->addWidget(mIcon);
    mIconLayout->addWidget(mIcon);
    //mContentLayout->addStretch();
    //mContentLayout->addWidget(mContent);
    mTextLayout->addWidget(mContent);
    //mContentLayout->addStretch();
    //mContentLayout->addWidget(mClose);
    mCloseLayout->addWidget(mClose);
    //mContentLayout->addStretch();
    mColorBarLayout->addWidget(mColorBar);

    connect(mClose, SIGNAL(leftButtonReleased())
            ,this, SLOT(closeMenu()));
  }

  void IVMS4200MenuEx_Frame::leaveEvent(QEvent *event) {

  }

  void IVMS4200MenuEx_Frame::mouseDoubleClickEvent(QMouseEvent *event) {
  }

  void IVMS4200MenuEx_Frame::mouseMoveEvent(QMouseEvent *event) {
  }

  void IVMS4200MenuEx_Frame::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      event->accept();
      //setStyleSheet(ivms4200MenuEx_FrameClickBackground);
      emit currentMenuExChanged(this);
      emit currentMenuExChanged(this->productName());
      return;
    } else {
      event->ignore();
      return;
    }
  }

  bool IVMS4200MenuEx_Frame::mouseInMenuBar(QPoint currentMousePos) {
    if (mMenuBar->frameGeometry().contains(currentMousePos)) {
      return true;
    }
    return false;
  }

  // private
  void IVMS4200MenuEx_Frame::showClose() {
    mClose->show();
  }

  void IVMS4200MenuEx_Frame::hideClose() {
    mClose->hide();
  }

  void IVMS4200MenuEx_Frame::showColorBar() {
    mColorBar->show();
  }

  void IVMS4200MenuEx_Frame::hideColorBar() {
    mColorBar->hide();
  }

  /*
   * UniversalLabel_Frame
   */
  // cotr
  UniversalLabel_Frame::UniversalLabel_Frame(QWidget* parent)
    :Frame(parent) {}

  UniversalLabel_Frame::~UniversalLabel_Frame() {}

  void UniversalLabel_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  QHBoxLayout* UniversalLabel_Frame::layout() const {
    return  dynamic_cast<QHBoxLayout*>(mMainLayout);
  }

  void UniversalLabel_Frame::initWindow() {
  }

  void UniversalLabel_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void UniversalLabel_Frame::init() {

  }

  void UniversalLabel_Frame::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      event->accept();
      emit leftButtonReleased(this->productName());
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * SingleLabel_Frame
   */
  // cotr
  SingleLabel_Frame::SingleLabel_Frame(QWidget* parent)
    :UniversalLabel_Frame(parent) {}

  SingleLabel_Frame::~SingleLabel_Frame() {}

  void SingleLabel_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  DealWithMouseEventEx_Label* SingleLabel_Frame::label() const {
    return dynamic_cast<DealWithMouseEventEx_Label*>(mLabel);
  }

  // protected
  void SingleLabel_Frame::initWindow() {
  }

  void SingleLabel_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void SingleLabel_Frame::init() {
    mLabel = new DealWithMouseEventEx_Label;
    mMainLayout->addWidget(mLabel);
  }

  /*
   * Search_Frame
   */
  // cotr
  Search_Frame::Search_Frame(QWidget* parent)
    :Frame(parent) {}

  Search_Frame::~Search_Frame() {}

  void Search_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  LineEdit* Search_Frame::content() const {
    return mContent;
  }

  DealWithMouseEvent_Label* Search_Frame::close() const {
    return mClose;
  }

  DealWithMouseEvent_Label* Search_Frame::search() const {
    return mSearch;
  }

  // public slots
  void Search_Frame::contentEdited(const QString& text) {
    if (mContent->text().isEmpty()) {
      mClose->hide();
    } else {
      mClose->show();
    }
  }

  // protected
  void Search_Frame::initWindow() {
  }

  void Search_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void Search_Frame::init() {
    mContent = new LineEdit;
    mClose = new ClearContentWidget_Label(mContent);
    mSearch = new Search_Label;
    mMainLayout->addWidget(mContent);
    mMainLayout->addWidget(mClose);
    mMainLayout->addWidget(mSearch);

    //mContent->setText(tr("Search..."));
    mClose->hide();

    connect(mContent, SIGNAL(textEdited(const QString&)), this, SLOT(contentEdited(const QString&)));
  }

  /*
   * TreeTopLevelItem_Label
   */
  // cotr
  TreeTopLevelItem_Label::TreeTopLevelItem_Label(QWidget* parent)
    :UniversalLabel_Frame(parent) {}

  TreeTopLevelItem_Label::~TreeTopLevelItem_Label() {}

  void TreeTopLevelItem_Label::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  DealWithMouseEvent_Label* TreeTopLevelItem_Label::collapseExpand() const {
    return dynamic_cast<DealWithMouseEvent_Label*>(mCollapseExpand);
  }

  Label* TreeTopLevelItem_Label::icon() const {
    return mIcon;
  }

  Label* TreeTopLevelItem_Label::content() const {
    return mContent;
  }

  OperatorsHorizontal_Frame* TreeTopLevelItem_Label::operating() const {
    return dynamic_cast<OperatorsHorizontal_Frame*>(mOperating);
  }

  QHBoxLayout* TreeTopLevelItem_Label::mainLayout() const {
    return dynamic_cast<QHBoxLayout*>(mMainLayout);
  }

  // protected
  void TreeTopLevelItem_Label::initWindow() {
  }

  void TreeTopLevelItem_Label::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void TreeTopLevelItem_Label::init() {
    mCollapseExpand = new DealWithMouseEvent_Label;
    mIcon = new Label;
    mContent = new Label;
    mOperating = new OperatorsHorizontal_Frame;
    mMainLayout->addWidget(mCollapseExpand);
    mMainLayout->addWidget(mIcon);
    mMainLayout->addWidget(mContent);
    mMainLayout->addStretch();
    mMainLayout->addWidget(mOperating);
  }

  /*
   * TreeChildLevelItem_Label
   */
  // cotr
  TreeChildLevelItem_Label::TreeChildLevelItem_Label(QWidget* parent)
    :TreeTopLevelItem_Label(parent) {}

  TreeChildLevelItem_Label::~TreeChildLevelItem_Label() {}

  void TreeChildLevelItem_Label::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  // protected
  void TreeChildLevelItem_Label::initWindow() {
  }

  void TreeChildLevelItem_Label::initLayout() {
  }

  void TreeChildLevelItem_Label::init() {
    TreeTopLevelItem_Label::setupUi(QSharedPointer<const Protocol>());
    mCollapseExpand->hide();
  }

  /*
   * OperatorsHorizontal_Frame
   */
  // cotr
  OperatorsHorizontal_Frame::OperatorsHorizontal_Frame(QWidget* parent)
    :Frame(parent) {}

  OperatorsHorizontal_Frame::~OperatorsHorizontal_Frame() {}

  void OperatorsHorizontal_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  QHBoxLayout* OperatorsHorizontal_Frame::mainLayout() const {
    return dynamic_cast<QHBoxLayout*>(mMainLayout);
  }

  // protected
  void OperatorsHorizontal_Frame::initWindow() {
  }

  void OperatorsHorizontal_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void OperatorsHorizontal_Frame::init() {

  }

  /*
   * Tree
   */
  // cotr
  Tree::Tree(QWidget* parent)
    :Frame(parent) {}

  Tree::~Tree() {}

  void Tree::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void Tree::addTopLevelItem(Frame* topLevelItem) {
    mTopLevelItems[topLevelItem->objectName()];
    emit addTopLevelItem_Signal(topLevelItem->objectName());
  }

  void Tree::addChildLevelItem(const QString topLevelItem, Frame* childLevelItem) {
    if (mTopLevelItems.contains(topLevelItem)) {
      ChildItems childItems = mTopLevelItems.value(topLevelItem);
      //childItems[childLevelItem->objectName()] = childLevelItem;
      emit addChildLevelItem_Signal(topLevelItem, childLevelItem->objectName());
    }
  }

  void Tree::delTopLevelItem(const QString topLevelItem) {
    if (mTopLevelItems.contains(topLevelItem)) {
      mTopLevelItems.remove(topLevelItem);
      emit delTopLevelItem_Signal(topLevelItem);
    }
  }

  void Tree::delChildLevelItem(const QString topLevelItem, const QString childLevelItem) {
    if (mTopLevelItems.contains(topLevelItem)) {
      ChildItems childItems = mTopLevelItems.value(topLevelItem);
      if (childItems.contains(childLevelItem)) {
        childItems.remove(childLevelItem);
        emit delChildLevelItem_Signal(topLevelItem, childLevelItem);
      }
    }
  }

  QVBoxLayout* Tree::mainLayout() const {
    return dynamic_cast<QVBoxLayout*>(mMainLayout);
  }

  // public slots
  void Tree::addTopLevelItem_Slot(const QString name) {
    //mMainLayout->addWidget(mTopLevelItems.value(name));
  }

  void Tree::addChildLevelItem_Slot(const QString topName, const QString childName) {
  }

  void Tree::delTopLevelItem_Slot(const QString name) {
  }

  void Tree::delChildLevelItem_Slot(const QString topName, const QString childName) {

  }

  // protected
  void Tree::initWindow() {
  }

  void Tree::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void Tree::init() {

  }

  /*
   * IVMS4200ContentAreaStyleModel_Frame
   */
  // cotr
  IVMS4200ContentAreaStyleModel_Frame::IVMS4200ContentAreaStyleModel_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200ContentAreaStyleModel_Frame::~IVMS4200ContentAreaStyleModel_Frame() {}

  void IVMS4200ContentAreaStyleModel_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  QStackedWidget* IVMS4200ContentAreaStyleModel_Frame::leftWgt() const {
    return mLeftWgt;
  }

  IVMS4200MainPreviewMidWgt_Frame* IVMS4200ContentAreaStyleModel_Frame::midWgt() const {
    return dynamic_cast<IVMS4200MainPreviewMidWgt_Frame*>(mMidWgt);
  }

  QStackedWidget* IVMS4200ContentAreaStyleModel_Frame::rightWgt() const {
    return mRightWgt;
  }

  // protected
  void IVMS4200ContentAreaStyleModel_Frame::initWindow() {
  }

  void IVMS4200ContentAreaStyleModel_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void IVMS4200ContentAreaStyleModel_Frame::init() {
    mLeftWgt = new QStackedWidget;
    mMidWgt = new IVMS4200MainPreviewMidWgt_Frame;
    mMidWgt->setupUi(QSharedPointer<const Protocol>());
    mRightWgt = new QStackedWidget;
    mMainLayout->addWidget(mLeftWgt);
    mMainLayout->addWidget(mMidWgt);
    mMainLayout->addWidget(mRightWgt);
  }

  /*
   * IVMS4200MainPreviewLeftWgt_Frame
   */
  // cotr
  IVMS4200MainPreviewLeftWgt_Frame::IVMS4200MainPreviewLeftWgt_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200MainPreviewLeftWgt_Frame::~IVMS4200MainPreviewLeftWgt_Frame() {}

  void IVMS4200MainPreviewLeftWgt_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  IVMS4200TitleWgt_Frame* IVMS4200MainPreviewLeftWgt_Frame::title() const {
    return dynamic_cast<IVMS4200TitleWgt_Frame*>(mTitle);
  }

  // protected
  void IVMS4200MainPreviewLeftWgt_Frame::initWindow() {
  }

  void IVMS4200MainPreviewLeftWgt_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
  }

  void IVMS4200MainPreviewLeftWgt_Frame::init() {
    mTitle = new IVMS4200TitleWgt_Frame;
    mTitle->setupUi(QSharedPointer<const Protocol>());
    mContentArea = new QStackedWidget;
    mMainLayout->addWidget(mTitle);
    mMainLayout->addWidget(mContentArea);
  }

  /*
   * IVMS4200TitleWgt_Frame
   */
  // cotr
  IVMS4200TitleWgt_Frame::IVMS4200TitleWgt_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200TitleWgt_Frame::~IVMS4200TitleWgt_Frame() {}

  void IVMS4200TitleWgt_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  SingleLabel_Frame* IVMS4200TitleWgt_Frame::title1() const {
    return dynamic_cast<SingleLabel_Frame*>(mTitle1);
  }

  SingleLabel_Frame* IVMS4200TitleWgt_Frame::title2() const {
    return dynamic_cast<SingleLabel_Frame*>(mTitle2);
  }

  QHBoxLayout* IVMS4200TitleWgt_Frame::mainLayout() const {
    return dynamic_cast<QHBoxLayout*>(mMainLayout);
  }

  // protected
  void IVMS4200TitleWgt_Frame::initWindow() {
  }

  void IVMS4200TitleWgt_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void IVMS4200TitleWgt_Frame::init() {
    mTitle1 = new SingleLabel_Frame;
    mTitle1->setupUi(QSharedPointer<const Protocol>());
    mTitle2 = new SingleLabel_Frame;
    mTitle2->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addStretch();
    mMainLayout->addWidget(mTitle1);
    mMainLayout->addStretch();
    mMainLayout->addWidget(mTitle2);
    mMainLayout->addStretch();
  }

  /*
   * LatticeView_Frame
   */
  // cotr
  LatticeView_Frame::LatticeView_Frame(QWidget* parent)
    :Frame(parent) {}

  LatticeView_Frame::~LatticeView_Frame() {}

  void LatticeView_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  QStackedWidget* LatticeView_Frame::widgets() const {
    return mWgts;
  }

  // protected
  void LatticeView_Frame::initWindow() {
  }

  void LatticeView_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
  }

  void LatticeView_Frame::init() {
    mWgts = new QStackedWidget;
    mMainLayout->addWidget(mWgts);
  }

  /*
   * IVMS4200Status_Frame
   */
  // cotr
  IVMS4200MainPreviewStatusBar_Frame::IVMS4200MainPreviewStatusBar_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200MainPreviewStatusBar_Frame::~IVMS4200MainPreviewStatusBar_Frame() {}

  void IVMS4200MainPreviewStatusBar_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label1() const {
    return mLabel1;
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label2() const {
    return mLabel2;
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label3() const {
    return mLabel3;
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label4() const {
    return mLabel4;
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label5() const {
    return mLabel5;
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label6() const {
    return mLabel6;
  }

  Label* IVMS4200MainPreviewStatusBar_Frame::label7() const {
    return mLabel7;
  }

  // protected
  void IVMS4200MainPreviewStatusBar_Frame::initWindow() {

  }

  void IVMS4200MainPreviewStatusBar_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void IVMS4200MainPreviewStatusBar_Frame::init() {
    mLabel1 = new DealWithMouseEvent_Label;
    mLabel2 = new DealWithMouseEvent_Label;
    mLabel3 = new DealWithMouseEvent_Label;
    mLabel4 = new DealWithMouseEvent_Label;
    mLabel5 = new DealWithMouseEvent_Label;
    mLabel6 = new DealWithMouseEvent_Label;
    mLabel7 = new DealWithMouseEvent_Label;
    mMainLayout->addWidget(mLabel1);
    mMainLayout->addWidget(mLabel2);
    mMainLayout->addStretch();
    mMainLayout->addWidget(mLabel3);
    mMainLayout->addWidget(mLabel4);
    mMainLayout->addWidget(mLabel5);
    mMainLayout->addWidget(mLabel6);
    mMainLayout->addWidget(mLabel7);
  }

  /*
   * IVMS4200MainPreviewMidWgt_Frame
   */
  // cotr
  IVMS4200MainPreviewMidWgt_Frame::IVMS4200MainPreviewMidWgt_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200MainPreviewMidWgt_Frame::~IVMS4200MainPreviewMidWgt_Frame() {}

  void IVMS4200MainPreviewMidWgt_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* IVMS4200MainPreviewMidWgt_Frame::label() const {
    return mLabel;
  }

  // protected
  void IVMS4200MainPreviewMidWgt_Frame::initWindow() {
  }

  void IVMS4200MainPreviewMidWgt_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
  }

  void IVMS4200MainPreviewMidWgt_Frame::init() {
    mLabel = new DealWithMouseEvent_Label;
    mMainLayout->addStretch();
    mMainLayout->addWidget(mLabel);
    mMainLayout->addStretch();
  }

  /*
   * IVMS4200MainPreviewRigthWgt_Frame
   */
  // cotr
  IVMS4200MainPreviewRightWgt_Frame::IVMS4200MainPreviewRightWgt_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200MainPreviewRightWgt_Frame::~IVMS4200MainPreviewRightWgt_Frame() {}

  void IVMS4200MainPreviewRightWgt_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  LatticeView_Frame* IVMS4200MainPreviewRightWgt_Frame::contentArea() const {
    return dynamic_cast<LatticeView_Frame*>(mContentArea);
  }

  IVMS4200MainPreviewStatusBar_Frame* IVMS4200MainPreviewRightWgt_Frame::statusBar() const {
    return dynamic_cast<IVMS4200MainPreviewStatusBar_Frame*>(mStatusBar);
  }

  // protected
  void IVMS4200MainPreviewRightWgt_Frame::initWindow() {
  }

  void IVMS4200MainPreviewRightWgt_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void IVMS4200MainPreviewRightWgt_Frame::init() {
    mContentArea = new LatticeView_Frame;
    mContentArea->setupUi(QSharedPointer<const Protocol>());
    mStatusBar = new IVMS4200MainPreviewStatusBar_Frame;
    mStatusBar->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addWidget(mContentArea);
    mMainLayout->addWidget(mStatusBar);
  }

  /*
   * VideoShow_Frame
   */
  // cotr
  VideoShow_Frame::VideoShow_Frame(QWidget* parent)
    :Frame(parent) {}

  VideoShow_Frame::~VideoShow_Frame() {}

  void VideoShow_Frame::setupUi(QSharedPointer<const Protocol> protocol) {

  }

  // protected
  void VideoShow_Frame::initWindow() {
  }

  void VideoShow_Frame::initLayout() {
  }

  void VideoShow_Frame::init() {

  }

  /*
   * Lattice_Frame
   */
  // cotr
  Lattice_Frame::Lattice_Frame(const int row, const int column, QWidget* parent)
    :Frame(parent)
    ,mRow(row)
    ,mColumn(column){}

  Lattice_Frame::~Lattice_Frame() {}

  void Lattice_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  // pretected
  void Lattice_Frame::initWindow() {

  }

  void Lattice_Frame::initLayout() {
    mMainLayout = new QGridLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void Lattice_Frame::init() {
    for (int i = 0; i < mRow; ++i) {
      for (int j = 0; j < mColumn; ++j) {
        Frame* wgt = new VideoShow_Frame;
        mWgts[wgt->productName()] = wgt;
        dynamic_cast<QGridLayout*>(mMainLayout)->addWidget(wgt, i, j);
      }
    }
  }

  /*
   * DirectoryItem_Frame
   */
  // cotr
  DirectoryItem_Frame::DirectoryItem_Frame(QWidget* parent)
    :UniversalLabel_Frame(parent) {}

  DirectoryItem_Frame::~DirectoryItem_Frame() {}

  void DirectoryItem_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  DealWithMouseEventEx_Label *DirectoryItem_Frame::label() const {
    return dynamic_cast<DealWithMouseEventEx_Label*>(mLabel);
  }

  // protected
  void DirectoryItem_Frame::initWindow() {
  }

  void DirectoryItem_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void DirectoryItem_Frame::init() {
    mLabel = new DealWithMouseEventEx_Label;
    mMainLayout->addWidget(mLabel, 0, Qt::AlignLeft);
    //mMainLayout->addStretch();

    connect(dynamic_cast<DealWithMouseEventEx_Label*>(mLabel), SIGNAL(leftButtonReleased())
            ,this, SIGNAL(directoryItemClicked()));
  }

  /*
   * DirectoryControl_Frame
   */
  // cotr
  DirectoryControl_Frame::DirectoryControl_Frame(QWidget* parent)
    :Frame(parent)
    ,mDirectoryItem(nullptr)
    ,mIsExpand(true) {}

  DirectoryControl_Frame::~DirectoryControl_Frame() {}

  void DirectoryControl_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void DirectoryControl_Frame::setDirectoryItem(DirectoryItem_Frame* item) {
    if (!mDirectoryItem) {
      mDirectoryItem = item;
      mMainLayout->insertWidget(0, mDirectoryItem);
      connect(mDirectoryItem, SIGNAL(directoryItemClicked())
              ,this, SLOT(directoryItemClicked()));
    }
  }

  DirectoryItem_Frame* DirectoryControl_Frame::directoryItem() const {
    return mDirectoryItem;
  }

  void DirectoryControl_Frame::delDirectoryItem() {
    mMainLayout->removeWidget(mDirectoryItem);
    mDirectoryItem = nullptr;
  }

  void DirectoryControl_Frame::addItem(Frame* item) {
    mItems[item->productName()] = item;
    mMainLayout->addWidget(item);
  }

  void DirectoryControl_Frame::addItemEx(Frame* item) {
    addItem(item);
    DirectoryLabel_Frame* pItem = dynamic_cast<DirectoryLabel_Frame*>(item);
    if (pItem->hasChild()) {
      DirectoryLabelEx_Frame* itemEx = dynamic_cast<DirectoryLabelEx_Frame*>(pItem);
      QHash<const QString, Frame*> subItems = itemEx->subItems();
      auto it = subItems.begin();
      auto end = subItems.end();
      for (; it != end; ++it) {
        mMainLayout->addSpacing(5);
        mMainLayout->addWidget(it.value());
      }
    }
  }

  void DirectoryControl_Frame::delItem(Frame* item) {
    mItems.remove(item->productName());
    mMainLayout->removeWidget(item);
  }

  void DirectoryControl_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  Frame* DirectoryControl_Frame::item(const QString name) const {
    return mItems.value(name);
  }

  bool DirectoryControl_Frame::isExpand() const {
    return mIsExpand;
  }

  void DirectoryControl_Frame::expand() {
    auto it = mItems.begin();
    for (; it != mItems.end(); ++it) {
      DirectoryLabel_Frame* item = dynamic_cast<DirectoryLabel_Frame*>(it.value());
      if (item->hasChild()) {
        dynamic_cast<DirectoryLabelEx_Frame*>(it.value())->expand()->show();
      }
      dynamic_cast<DirectoryLabel_Frame*>(it.value())->content()->show();
    }
    mIsExpand = true;
  }

  void DirectoryControl_Frame::shrink() {
    auto it = mItems.begin();
    for (; it != mItems.end(); ++it) {
      DirectoryLabel_Frame* item = dynamic_cast<DirectoryLabel_Frame*>(it.value());
      if (item->hasChild()) {
        dynamic_cast<DirectoryLabelEx_Frame*>(it.value())->expand()->hide();
      }
      dynamic_cast<DirectoryLabel_Frame*>(it.value())->content()->hide();
    }
    mIsExpand = false;
  }

  // public slots
  void DirectoryControl_Frame::directoryItemClicked() {

  }

  // protected
  void DirectoryControl_Frame::initWindow() {
  }

  void DirectoryControl_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void DirectoryControl_Frame::init() {

  }

  /*
   * DirectoryLabel_Frame
   */
  // cotr
  DirectoryLabel_Frame::DirectoryLabel_Frame(QWidget* parent)
    :UniversalLabel_Frame(parent)
    ,mHasChild(false) {}

  DirectoryLabel_Frame::~DirectoryLabel_Frame() {}

  void DirectoryLabel_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* DirectoryLabel_Frame::icon() const {
    return mIcon;
  }

  Label* DirectoryLabel_Frame::content() const {
    return mContent;
  }

  bool DirectoryLabel_Frame::hasChild() const {
    return mHasChild;
  }

  void DirectoryLabel_Frame::setHasChild(bool hasChild) {
    mHasChild = hasChild;
  }

  // protected
  void DirectoryLabel_Frame::initWindow() {
  }

  void DirectoryLabel_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void DirectoryLabel_Frame::init() {
    mIcon = new Label;
    mContent = new Label;
    mMainLayout->addWidget(mIcon);
    mMainLayout->addWidget(mContent);
    //mMainLayout->addStretch();
  }

  /*
   * DirectoryLabelEx_Frame
   */
  // cotr
  DirectoryLabelEx_Frame::DirectoryLabelEx_Frame(QWidget* parent)
    :DirectoryLabel_Frame(parent)
    ,mVisibleChild(false) {}

  DirectoryLabelEx_Frame::~DirectoryLabelEx_Frame() {}

  void DirectoryLabelEx_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void DirectoryLabelEx_Frame::addChildItem(DirectoryLabelContent_Frame* item) {
    mSubItems[item->productName()] = item;
    if (!mVisibleChild) {
      item->hide();
    }
  }

  Label* DirectoryLabelEx_Frame::expand() const {
    return mExpand;
  }

  QHash<const QString, Frame*> DirectoryLabelEx_Frame::subItems() const {
    return mSubItems;
  }

  // protected
  void DirectoryLabelEx_Frame::initWindow() {
  }

  void DirectoryLabelEx_Frame::initLayout() {
    DirectoryLabel_Frame::initLayout();
  }

  void DirectoryLabelEx_Frame::init() {
    DirectoryLabel_Frame::init();
    mExpand = new Label;
    mMainLayout->addWidget(mExpand);
  }

  void DirectoryLabelEx_Frame::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      event->accept();
      if (mVisibleChild) {
        auto it = mSubItems.begin();
        auto end = mSubItems.end();
        for (; it != end; ++it) {
          it.value()->hide();
        }
        mVisibleChild = false;
      } else {
        auto it = mSubItems.begin();
        auto end = mSubItems.end();
        for (; it != end; ++it) {
          it.value()->show();
        }
        mVisibleChild = true;
      }
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * DirectoryLabelContent_Frame
   */
  // cotr
  DirectoryLabelContent_Frame::DirectoryLabelContent_Frame(QWidget* parent)
    :UniversalLabel_Frame(parent) {}

  DirectoryLabelContent_Frame::~DirectoryLabelContent_Frame() {}

  void DirectoryLabelContent_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* DirectoryLabelContent_Frame::content() const {
    return mContent;
  }

  // protected
  void DirectoryLabelContent_Frame::initWindow() {

  }

  void DirectoryLabelContent_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void DirectoryLabelContent_Frame::init() {
    mContent = new Label;
    mMainLayout->addStretch();
    mMainLayout->addWidget(mContent);
    mMainLayout->addStretch(1);
  }

  /*
   * DirectoryLabelParentChild_Frame
   */
  // cotr
  DirectoryLabelParentChild_Frame::DirectoryLabelParentChild_Frame(QWidget* parent)
    :Frame(parent)
    ,mParentItem(nullptr) {}

  DirectoryLabelParentChild_Frame::~DirectoryLabelParentChild_Frame() {}

  void DirectoryLabelParentChild_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void DirectoryLabelParentChild_Frame::addParentItem(DirectoryLabelEx_Frame* item) {
    if (!mParentItem) {
      mParentItem = item;
      mMainLayout->insertWidget(0, mParentItem);
    }
  }

  void DirectoryLabelParentChild_Frame::addChildItem(DirectoryLabelContent_Frame* item) {
    mItems[item->productName()] = item;
    mMainLayout->addWidget(item);
  }

  void DirectoryLabelParentChild_Frame::delParentItem() {
    mMainLayout->removeWidget(mParentItem);
  }

  void DirectoryLabelParentChild_Frame::delChildItem(const QString productName) {
    if (mItems.contains(productName)) {
      DirectoryLabelContent_Frame* item = mItems.value(productName);
      mItems.remove(productName);
      mMainLayout->removeWidget(item);
    }

  }

  // protected
  void DirectoryLabelParentChild_Frame::initWindow() {
  }

  void DirectoryLabelParentChild_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void DirectoryLabelParentChild_Frame::init() {

  }

  /*
   * RemotePlaybackFeaturesStyleModel_Frame
   */
  // cotr
  RemotePlaybackFeaturesStyleModel_Frame::RemotePlaybackFeaturesStyleModel_Frame(QWidget* parent)
    :Frame(parent) {}

  RemotePlaybackFeaturesStyleModel_Frame::~RemotePlaybackFeaturesStyleModel_Frame() {}

  void RemotePlaybackFeaturesStyleModel_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* RemotePlaybackFeaturesStyleModel_Frame::title() const {
    return mTitle;
  }

  QDateTimeEdit* RemotePlaybackFeaturesStyleModel_Frame::time() const {
    return mTime;
  }

  void RemotePlaybackFeaturesStyleModel_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  // protected
  void RemotePlaybackFeaturesStyleModel_Frame::initWindow() {
  }

  void RemotePlaybackFeaturesStyleModel_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
  }

  void RemotePlaybackFeaturesStyleModel_Frame::init() {
    mTitle = new Label;
    mTime = new QDateTimeEdit;
    mMainLayout->addWidget(mTitle);
    mMainLayout->addWidget(mTime);
  }

  /*
   * RemotePlaybackMonitorFeature_Frame
   */
  // cotr
  RemotePlaybackMonitorFeature_Frame::RemotePlaybackMonitorFeature_Frame(QWidget* parent)
    :RemotePlaybackFeaturesStyleModel_Frame(parent) {}

  RemotePlaybackMonitorFeature_Frame::~RemotePlaybackMonitorFeature_Frame() {}

  void RemotePlaybackMonitorFeature_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    RemotePlaybackFeaturesStyleModel_Frame::setupUi(protocol);
    initWindow();
    initLayout();
    init();
  }

  Label* RemotePlaybackMonitorFeature_Frame::label() const {
    return mLabel;
  }

  Search_Frame* RemotePlaybackMonitorFeature_Frame::search() const {
    return dynamic_cast<Search_Frame*>(mSearch);
  }

  // protected
  void RemotePlaybackMonitorFeature_Frame::initWindow() {
  }

  void RemotePlaybackMonitorFeature_Frame::initLayout() {
  }

  void RemotePlaybackMonitorFeature_Frame::init() {
    mLabel = new Label;
    mSearch = new Search_Frame;
    mSearch->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addWidget(mLabel);
    mMainLayout->addWidget(mSearch);
  }

  /*
   * IVMS4200ContentAreaStyleModel1_Frame
   */
  // cotr
  IVMS4200ContentAreaStyleModel1_Frame::IVMS4200ContentAreaStyleModel1_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200ContentAreaStyleModel1_Frame::~IVMS4200ContentAreaStyleModel1_Frame() {}

  void IVMS4200ContentAreaStyleModel1_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  DirectoryControl_Frame* IVMS4200ContentAreaStyleModel1_Frame::directory() const {
    return dynamic_cast<DirectoryControl_Frame*>(mDirectory);
  }

  IVMS4200ContentAreaStyleModel_Frame* IVMS4200ContentAreaStyleModel1_Frame::styleModel1() const {
    return dynamic_cast<IVMS4200ContentAreaStyleModel_Frame*>(mStyleModel1);
  }

  // protected
  void IVMS4200ContentAreaStyleModel1_Frame::initWindow() {
  }

  void IVMS4200ContentAreaStyleModel1_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void IVMS4200ContentAreaStyleModel1_Frame::init() {
    mDirectory = new DirectoryControl_Frame;
    mDirectory->setupUi(QSharedPointer<const Protocol>());
    mStyleModel1 = new IVMS4200ContentAreaStyleModel_Frame;
    mStyleModel1->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addWidget(mDirectory);
    mMainLayout->addWidget(mStyleModel1);
  }

}
