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
#include <QScrollArea>
#include <QHeaderView>

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
    //mMainLayout->setContentsMargins(0, 0, 0, 0);
    //mMainLayout->setSpacing(0);
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
      mContent->setStyleSheet("background-image: url(:/icon/searchbackground.png)");
    } else {
      mClose->show();
      mContent->setStyleSheet("background: red");
    }
  }

  void Search_Frame::contentCleared() {
    contentEdited("");
  }

  // protected
  void Search_Frame::initWindow() {
  }

  void Search_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    //mMainLayout->setContentsMargins(0, 0, 0, 0);
    //mMainLayout->setSpacing(0);
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
    connect(mClose, SIGNAL(clearCompleted()), this, SLOT(contentCleared()));
  }

  /*
   * TreeTopLevelItem_Label
   */
  // cotr
  TreeItem_Label::TreeItem_Label(QWidget* parent)
    :UniversalLabel_Frame(parent) {
    setMouseTracking(true);
  }

  TreeItem_Label::~TreeItem_Label() {}

  void TreeItem_Label::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  DealWithMouseEventEx_Label *TreeItem_Label::collapseExpand() const {
    return dynamic_cast<DealWithMouseEventEx_Label*>(mCollapseExpand);
  }

  Label* TreeItem_Label::icon() const {
    return mIcon;
  }

  Label* TreeItem_Label::content() const {
    return mContent;
  }

  OperatorsHorizontal_Frame* TreeItem_Label::operating() const {
    return dynamic_cast<OperatorsHorizontal_Frame*>(mOperating);
  }

  QHBoxLayout* TreeItem_Label::mainLayout() const {
    return dynamic_cast<QHBoxLayout*>(mMainLayout);
  }

  void TreeItem_Label::insertStretch(int index) {
    mMainLayout->insertStretch(index);
  }

  bool TreeItem_Label::hasChild() const {
    return !mChilds.isEmpty();
  }

  bool TreeItem_Label::isExpand() const {
    return mExpand;
  }

  void TreeItem_Label::collapse() {
    if (!mChilds.isEmpty()) {
      auto it = mChilds.begin();
      auto end = mChilds.end();
      for (; it != end; ++it) {
        (*it)->hide();
      }
      mExpand = false;
    }
  }

  void TreeItem_Label::expand(){
    if (!mChilds.isEmpty()) {
      auto it = mChilds.begin();
      auto end = mChilds.end();
      for (; it != end; ++it) {
        (*it)->show();
      }
      mExpand = true;
    }
  }

  // protected
  void TreeItem_Label::initWindow() {
  }

  void TreeItem_Label::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void TreeItem_Label::init() {
    mCollapseExpand = new DealWithMouseEventEx_Label;
    mIcon = new Label;
    mContent = new Label;
    mOperating = new OperatorsHorizontal_Frame;
    mOperating->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addWidget(mCollapseExpand);
    mMainLayout->addWidget(mIcon);
    mMainLayout->addWidget(mContent);
    mMainLayout->addStretch();
    mMainLayout->addWidget(mOperating);
  }

  void TreeItem_Label::leaveEvent(QEvent *event) {
      mOperating->hide();
  }

  void TreeItem_Label::mouseMoveEvent(QMouseEvent *event) {
      mOperating->show();
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

  void Tree::addTopLevelItem(TreeItem_Label* topLevelItem, bool collapseShow
                             ,bool iconShow, bool contentShow, bool operatFrameShow) {
    mItems[topLevelItem->objectName()] = topLevelItem;

    topLevelItem->collapseExpand()->setVisible(collapseShow);
    topLevelItem->icon()->setVisible(iconShow);
    topLevelItem->content()->setVisible(contentShow);
    topLevelItem->operating()->setVisible(operatFrameShow);
    topLevelItem->mParent = nullptr;
    mMainLayout->addWidget(topLevelItem);
    //emit addTopLevelItem_Signal(topLevelItem->objectName());
  }

  void Tree::addChildLevelItem(const QString topLevelItem, Jinhui::TreeItem_Label *childLevelItem
                               ,bool collapseShow, bool iconShow
                               ,bool contentShow, bool operatFrameShow) {
    if (mItems.contains(topLevelItem)) {
      mItems[childLevelItem->objectName()] = childLevelItem;

      TreeItem_Label* topItem = dynamic_cast<TreeItem_Label*>(mItems.value(topLevelItem));
      topItem->mChilds.append(childLevelItem);
      childLevelItem->mParent = topItem;
      childLevelItem->collapseExpand()->setVisible(collapseShow);
      childLevelItem->icon()->setVisible(iconShow);
      childLevelItem->content()->setVisible(contentShow);
      childLevelItem->operating()->setVisible(operatFrameShow);
      childLevelItem->insertStretch(0);
      mMainLayout->insertWidget(mMainLayout->indexOf(topItem) + 1, childLevelItem);
      if (!topItem->mChilds.isEmpty()) {
        topItem->collapseExpand()->setVisible(true);
      }
      //emit addChildLevelItem_Signal(topLevelItem, childLevelItem->objectName());
    }
  }

  void Tree::delTopLevelItem(const QString topLevelItem) {
    if (mItems.contains(topLevelItem)) {
      TreeItem_Label* topItem = dynamic_cast<TreeItem_Label*>(mItems.value(topLevelItem));
      auto it = topItem->mChilds.begin();
      auto end = topItem->mChilds.end();
      for (; it != end; ++it) {
        mMainLayout->removeWidget(*it);
        mItems.remove((*it)->objectName());
      }
      topItem->mChilds.clear();
      mMainLayout->removeWidget(topItem);
      mItems.remove(topLevelItem);
      //emit delTopLevelItem_Signal(topLevelItem);
    }
  }

  void Tree::delChildLevelItem(const QString childLevelItem) {
    if (mItems.contains(childLevelItem)) {
      TreeItem_Label* childItem = dynamic_cast<TreeItem_Label*>(mItems.value(childLevelItem));
      childItem->mParent->mChilds.remove(childItem->mParent->mChilds.indexOf(childItem));
      mMainLayout->removeWidget(mItems.value(childLevelItem));
      mItems.value(childLevelItem)->hide();
      mItems.remove(childLevelItem);
      if (childItem->mParent->mChilds.isEmpty()) {
        childItem->mParent->collapseExpand()->setVisible(false);
      }
        //emit delChildLevelItem_Signal(topLevelItem, childLevelItem);
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

  void IVMS4200ContentAreaStyleModel_Frame::leftAddWgt(Frame* wgt) {
    mLeftWgt->addWidget(wgt);
    mLeftwgts[wgt->productName()] = wgt;
  }

  void IVMS4200ContentAreaStyleModel_Frame::rightAddWgt(Frame* wgt) {
    if (!wgt) {
      return;
    }
    mRightWgt->addWidget(wgt);
    mRightwgts[wgt->productName()] = wgt;
  }

  Frame* IVMS4200ContentAreaStyleModel_Frame::leftContentAreaWgt(const QString proName) const {
    if (mLeftwgts.contains(proName)) {
      return mLeftwgts.value(proName);
    }
    return nullptr;
  }

  IVMS4200MainPreviewMidWgt_Frame* IVMS4200ContentAreaStyleModel_Frame::midWgt() const {
    return dynamic_cast<IVMS4200MainPreviewMidWgt_Frame*>(mMidWgt);
  }

  Frame* IVMS4200ContentAreaStyleModel_Frame::rightContentAreaWgt(const QString proName) const {
    if (mRightwgts.contains(proName)) {
      return mRightwgts.value(proName);
    }
    return nullptr;
  }

  void IVMS4200ContentAreaStyleModel_Frame::setLeftContentAreaCurrentWgt(const QString proName) {
    if (mLeftwgts.contains(proName)) {
      mLeftWgt->setCurrentWidget(mLeftwgts.value(proName));
    }
  }

  void IVMS4200ContentAreaStyleModel_Frame::setRightContentAreaCurrentWgt(const QString proName) {
    if (mRightwgts.contains(proName)) {
      mRightWgt->setCurrentWidget(mRightwgts.value(proName));
    }
  }

  void IVMS4200ContentAreaStyleModel_Frame::hideLeftContentArea() {
    mLeftWgt->hide();
  }

  void IVMS4200ContentAreaStyleModel_Frame::hideMidContentArea() {
    mMidWgt->hide();
  }

  void IVMS4200ContentAreaStyleModel_Frame::hideRightContentArea() {
    mRightWgt->hide();
  }

  void IVMS4200ContentAreaStyleModel_Frame::showLeftContentArea() {
    mLeftWgt->show();
  }

  void IVMS4200ContentAreaStyleModel_Frame::showMidContentArea() {
    mMidWgt->show();
  }

  void IVMS4200ContentAreaStyleModel_Frame::showRightContentArea() {
    mRightWgt->show();
  }

  // protected
  void IVMS4200ContentAreaStyleModel_Frame::initWindow() {
  }

  void IVMS4200ContentAreaStyleModel_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mLeftLayout = new QHBoxLayout;
    mMidLayout = new QHBoxLayout;
    mRightLayout = new QHBoxLayout;
    mMainLayout->addLayout(mLeftLayout);
    mMainLayout->addLayout(mMidLayout);
    mMainLayout->addLayout(mRightLayout);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void IVMS4200ContentAreaStyleModel_Frame::init() {
    mLeftWgt = new QStackedWidget;
    mMidWgt = new IVMS4200MainPreviewMidWgt_Frame;
    mMidWgt->setupUi(QSharedPointer<const Protocol>());
    mRightWgt = new QStackedWidget;
    mLeftLayout->addWidget(mLeftWgt);
    mMidLayout->addWidget(mMidWgt);
    mRightLayout->addWidget(mRightWgt);
  }

  /*
   * IVMS4200MainPreviewLeftResWgt_Frame
   */
  // cotr
  IVMS4200MainPreviewLeftResWgt_Frame::IVMS4200MainPreviewLeftResWgt_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200MainPreviewLeftResWgt_Frame::~IVMS4200MainPreviewLeftResWgt_Frame() {}

  void IVMS4200MainPreviewLeftResWgt_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  TitleWidget_Frame* IVMS4200MainPreviewLeftResWgt_Frame::view() const {
    return dynamic_cast<TitleWidget_Frame*>(mView);
  }

  TitleWidget_Frame* IVMS4200MainPreviewLeftResWgt_Frame::monitor() const {
    return dynamic_cast<TitleWidget_Frame*>(mMonitor);
  }

  void IVMS4200MainPreviewLeftResWgt_Frame::addStretch() {
    mMainLayout->addStretch();
  }
  // protected
  void IVMS4200MainPreviewLeftResWgt_Frame::initWindow() {
  }

  void IVMS4200MainPreviewLeftResWgt_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void IVMS4200MainPreviewLeftResWgt_Frame::init() {
    mView = new TitleWidget_Frame;
    mView->setupUi(QSharedPointer<const Protocol>());
    Frame* searchTree = new SearchTree_Frame;
    searchTree->setupUi(QSharedPointer<const Protocol>());
    dynamic_cast<TitleWidget_Frame*>(mView)->addWidget(searchTree);
    mMonitor = new TitleWidget_Frame;
    mMonitor->setupUi(QSharedPointer<const Protocol>());
    Frame* searchList = new SearchList_Frame;
    searchList->setupUi(QSharedPointer<const Protocol>());
    dynamic_cast<TitleWidget_Frame*>(mMonitor)->addWidget(searchList);
    mMainLayout->addWidget(mView);
    mMainLayout->addWidget(mMonitor);
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

  IVMS4200MainPreviewLeftResWgt_Frame* IVMS4200MainPreviewLeftWgt_Frame::res() const {
    return dynamic_cast<IVMS4200MainPreviewLeftResWgt_Frame*>(mRes);
  }

  void IVMS4200MainPreviewLeftWgt_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  // protected
  void IVMS4200MainPreviewLeftWgt_Frame::initWindow() {
  }

  void IVMS4200MainPreviewLeftWgt_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
  }

  void IVMS4200MainPreviewLeftWgt_Frame::init() {
    mTitle = new IVMS4200TitleWgt_Frame;
    mTitle->setupUi(QSharedPointer<const Protocol>());
    mContentArea = new QStackedWidget;
    mMainLayout->addWidget(mTitle);
    mMainLayout->addWidget(mContentArea);
    mRes = new IVMS4200MainPreviewLeftResWgt_Frame;
    mRes->setupUi(QSharedPointer<const Protocol>());
    mContentArea->addWidget(mRes);
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

  /*
   * HMenuBar_Frame
   */
  // cotr
  HMenuBar_Frame::HMenuBar_Frame(QWidget* parent)
    :Frame(parent) {}

  HMenuBar_Frame::~HMenuBar_Frame() {}

  void HMenuBar_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void HMenuBar_Frame::addMenu(const QString text, const QString frameObjName, const QString iconObjName) {
    Label_Frame* menu = new Label_Frame;
    menu->setupUi(QSharedPointer<const Protocol>());
    menu->setObjectName(frameObjName);
    menu->label()->setObjectName(iconObjName);
    menu->label()->setText(text);
    mMenus[frameObjName] = menu;
    mMainLayout->addWidget(menu);
  }

  void HMenuBar_Frame::addDirectoryLabelMenu(const QString text, const QString frameObjName
                                             ,const QString iconObjName, const QString contentObjName) {
    DirectoryLabel_Frame* menu = new DirectoryLabel_Frame;
    menu->setupUi(QSharedPointer<const Protocol>());
    menu->setObjectName(frameObjName);
    menu->icon()->setObjectName(iconObjName);
    menu->content()->setText(text);
    menu->content()->setObjectName(contentObjName);
    mMenus[frameObjName] = menu;
    mMainLayout->addWidget(menu);
  }

  void HMenuBar_Frame::delMenu(const QString objName) {
    if (mMenus.contains(objName)) {
      Frame* menu = mMenus.value(objName);
      mMainLayout->removeWidget(menu);
      mMenus.remove(objName);
    }
  }

  void HMenuBar_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  Label_Frame *HMenuBar_Frame::menu(const QString objName) const {
    if (mMenus.contains(objName)) {
      return dynamic_cast<Label_Frame*>(mMenus.value(objName));
    }
    return nullptr;
  }
  // protected
  void HMenuBar_Frame::initWindow() {}

  void HMenuBar_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void HMenuBar_Frame::init() {}

  /*
   * Filter_Frame
   */
  // cotr
  Filter_Frame::Filter_Frame(QWidget* parent)
    :Search_Frame(parent) {}

  Filter_Frame::~Filter_Frame() {}

  void Filter_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    Search_Frame::setupUi(protocol);
    init();
  }
  // protected
  void Filter_Frame::init() {
    mSearch->hide();
  }

  /*
   * FilterTitleBar_Frame
   */
  // cotr
  FilterMenuBar_Frame::FilterMenuBar_Frame(QWidget* parent)
    :Frame(parent) {}

  FilterMenuBar_Frame::~FilterMenuBar_Frame() {}

  void FilterMenuBar_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void FilterMenuBar_Frame::leftAddMenu(const QString text, const QString frameObjName
                                        ,const QString iconObjName, const QString contentObjName) {
    DirectoryLabel_Frame* label = new DirectoryLabel_Frame;
    label->setupUi(QSharedPointer<const Protocol>());
    label->setObjectName(frameObjName);
    label->icon()->setObjectName(iconObjName);
    label->content()->setObjectName(contentObjName);
    label->content()->setText(text);
    mWgts[label->objectName()] = label;
    mLeftLayout->addWidget(label);
  }

  void FilterMenuBar_Frame::rightAddMenu(const QString text, const QString frameObjName, const QString contentObjName) {
    DirectoryLabelContent_Frame* label = new DirectoryLabelContent_Frame;
    label->setupUi(QSharedPointer<const Protocol>());
    label->setObjectName(frameObjName);
    label->content()->setObjectName(contentObjName);
    label->content()->setText(text);
    mRightLayout->addWidget(label);
  }

  DirectoryLabel_Frame* FilterMenuBar_Frame::leftMenu(const QString frameObjName) const {
    if (mWgts.contains(frameObjName)) {
      return dynamic_cast<DirectoryLabel_Frame*>(mWgts.value(frameObjName));
    }
    return nullptr;
  }

  DirectoryLabel_Frame* FilterMenuBar_Frame::rightMenu(const QString frameObjName) const {
    return leftMenu(frameObjName);
  }

  Filter_Frame* FilterMenuBar_Frame::filter() const {
    return dynamic_cast<Filter_Frame*>(mFilter);
  }

  // protected
  void FilterMenuBar_Frame::initWindow() {
  }

  void FilterMenuBar_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mLeftLayout = new QHBoxLayout;
    mRightLayout = new QHBoxLayout;
    mFilterLayout = new QHBoxLayout;
    mMainLayout->addLayout(mLeftLayout);
    mMainLayout->addStretch(1);
    mMainLayout->addLayout(mRightLayout);
    mMainLayout->addLayout(mFilterLayout);
  }

  void FilterMenuBar_Frame::init() {
    mFilter = new Filter_Frame;
    mFilter->setupUi(QSharedPointer<const Protocol>());
    mFilterLayout->addWidget(mFilter);
  }

  /*
   * FilterMenuBarTable_Frame
   */
  // cotr
  FilterMenuBarTable_Frame::FilterMenuBarTable_Frame(QWidget* parent)
    :Frame(parent) {}

  FilterMenuBarTable_Frame::~FilterMenuBarTable_Frame() {}

  void FilterMenuBarTable_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  FilterMenuBar_Frame* FilterMenuBarTable_Frame::filterMenuBar() const {
    return dynamic_cast<FilterMenuBar_Frame*>(mFilterMenuBar);
  }

  void FilterMenuBarTable_Frame::setModel(TableModel* model) {
    mTable->setModel(model);
  }

  void FilterMenuBarTable_Frame::showHorHeader() {
    mTable->horizontalHeader()->show();
    int loginIndex = mTable->horizontalHeader()->logicalIndex(1);
    mTable->horizontalHeader()->setSortIndicatorShown(true);
    mTable->horizontalHeader()->setSortIndicator(loginIndex, Qt::DescendingOrder);
    bool b = mTable->horizontalHeader()->isSortIndicatorShown();
  }

  // protected
  void FilterMenuBarTable_Frame::initWindow() {
  }

  void FilterMenuBarTable_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void FilterMenuBarTable_Frame::init() {
    mFilterMenuBar = new FilterMenuBar_Frame;
    mFilterMenuBar->setupUi(QSharedPointer<const Protocol>());
    mTable = new QTableView;
    mMainLayout->addWidget(mFilterMenuBar, 0, Qt::AlignTop);
    mMainLayout->addWidget(mTable);
  }

  /*
   * IVMS4200Device_Frame
   */
  // cotr
  IVMS4200Device_Frame::IVMS4200Device_Frame(QWidget* parent)
    :Frame(parent) {}

  IVMS4200Device_Frame::~IVMS4200Device_Frame() {}

  void IVMS4200Device_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  HMenuBar_Frame* IVMS4200Device_Frame::menuBar() const {
    return dynamic_cast<HMenuBar_Frame*>(mMenuBar);
  }

  void IVMS4200Device_Frame::addWidget(Frame* wgt) {
    mStackedWgt->addWidget(wgt);
    mWgts[wgt->productName()] = wgt;
  }

  void IVMS4200Device_Frame::setCurrentWgt(const QString proName) {
    if (mWgts.contains(proName)) {
      mStackedWgt->setCurrentWidget(mWgts.value(proName));
    }
  }

  // protected
  void IVMS4200Device_Frame::initWindow() {
  }

  void IVMS4200Device_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void IVMS4200Device_Frame::init() {
    mMenuBar = new HMenuBar_Frame;
    mMenuBar->setupUi(QSharedPointer<const Protocol>());
    mStackedWgt = new QStackedWidget;
    mMainLayout->addWidget(mMenuBar, 0, Qt::AlignTop);
    mMainLayout->addWidget(mStackedWgt);
  }

  /*
   * Label_Frame
   */
  // cotr
  Label_Frame::Label_Frame(QWidget* parent)
    :UniversalLabel_Frame(parent) {}

  Label_Frame::~Label_Frame() {}

  void Label_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    UniversalLabel_Frame::setupUi(protocol);
    init();
  }

  Label* Label_Frame::label() const {
    return mLabel;
  }
  // protected
  void Label_Frame::init() {
    mLabel = new Label;
    mMainLayout->addWidget(mLabel);
  }

  /*
   * StorePlanFeature_Frame
   */
  // cotr
  StorePlanFeature_Frame::StorePlanFeature_Frame(QWidget* parent)
    :Frame(parent) {}

  StorePlanFeature_Frame::~StorePlanFeature_Frame() {}

  void StorePlanFeature_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* StorePlanFeature_Frame::title() const {
    return mTitle;
  }

  Search_Frame* StorePlanFeature_Frame::search() const {
    return dynamic_cast<Search_Frame*>(mSearch);
  }
  // protected
  void StorePlanFeature_Frame::initWindow() {
  }

  void StorePlanFeature_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mTitleLayout = new QHBoxLayout;
    mSearchLayout = new QHBoxLayout;
    mTreeLayout = new QHBoxLayout;
    mMainLayout->addLayout(mTitleLayout);
    mMainLayout->addLayout(mSearchLayout);
    mMainLayout->addLayout(mTreeLayout);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
  }

  void StorePlanFeature_Frame::init() {
    mTitle = new Label;
    mSearch = new Search_Frame;
    mSearch->setupUi(QSharedPointer<const Protocol>());
    mTitleLayout->addWidget(mTitle);
    mSearchLayout->addWidget(mSearch);
  }

  /*
   * StretchDisplay_Frame
   */
  // cotr
  StretchDisplay_Frame::StretchDisplay_Frame(int frontStretch, int backStretch, QWidget* parent)
    :Frame(parent)
    ,mFrontStretch(frontStretch)
    ,mBackStretch(backStretch) {}

  StretchDisplay_Frame::~StretchDisplay_Frame() {}

  void StretchDisplay_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }
  void StretchDisplay_Frame::addIcon(Label* icon) {
    mIconLayout->addWidget(icon);
    mIcon = icon;
  }

  void StretchDisplay_Frame::addWidget(Widget* widget) {
    mWidgetLayout->addWidget(widget);
    mWidget = widget;
  }

  void StretchDisplay_Frame::addWidget(CheckBox* widget) {
    mWidgetLayout->addWidget(widget);
    mCheckBox = widget;
  }

  void StretchDisplay_Frame::addWidget(ComboBox* widget) {
    mWidgetLayout->addWidget(widget);
    mComboBox = widget;
  }

  void StretchDisplay_Frame::addWidget(Frame* widget) {
    mWidgetLayout->addWidget(widget);
    mFrame = widget;
  }

  void StretchDisplay_Frame::addWidget(Label* widget) {
    mWidgetLayout->addWidget(widget);
    mLabel = widget;
  }

  void StretchDisplay_Frame::addWidget(RadioButton* widget) {
    mWidgetLayout->addWidget(widget);
    mRadioBtn = widget;
  }

  void StretchDisplay_Frame::addWidget(DoubleSpinBox* widget) {
    mWidgetLayout->addWidget(widget);
    mDoubleSpinBtn = widget;
  }

  //protected
  void StretchDisplay_Frame::initWindow() {
  }

  void StretchDisplay_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mIconLayout = new QHBoxLayout;
    mWidgetLayout = new QHBoxLayout;
    mMainLayout->addStretch(mFrontStretch);
    mMainLayout->addLayout(mIconLayout);
    mMainLayout->addLayout(mWidgetLayout);
    mMainLayout->addStretch(mBackStretch);
  }

  void StretchDisplay_Frame::init() {

  }

  /*
   * TitleMultiContent_Frame
   */
  // cotr
  TitleMultiContent_Frame::TitleMultiContent_Frame(QWidget* parent)
    :Frame(parent) {}

  TitleMultiContent_Frame::~TitleMultiContent_Frame() {}

  void TitleMultiContent_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void TitleMultiContent_Frame::setTitle(const QString title) {
    mTitle->setText(title);
  }

  void TitleMultiContent_Frame::addRow(Label* icon, Widget* widget) {
    StretchDisplay_Frame* row = new StretchDisplay_Frame;
    row->setupUi(QSharedPointer<const Protocol>());
    if (icon) {
      row->addIcon(icon);
    }
    if (widget) {
      row->addWidget(widget);
    }
    mMainLayout->addWidget(row);
  }

  void TitleMultiContent_Frame::addRow(Label* icon, CheckBox* widget) {
    StretchDisplay_Frame* row = new StretchDisplay_Frame;
    row->setupUi(QSharedPointer<const Protocol>());
    if (icon) {
      row->addIcon(icon);
    }
    if (widget) {
      row->addWidget(widget);
    }
    mMainLayout->addWidget(row);
  }

  void TitleMultiContent_Frame::addRow(Label* icon, ComboBox* widget) {
    StretchDisplay_Frame* row = new StretchDisplay_Frame;
    row->setupUi(QSharedPointer<const Protocol>());
    if (icon) {
      row->addIcon(icon);
    }
    if (widget) {
      row->addWidget(widget);
    }
    mMainLayout->addWidget(row);
  }

  void TitleMultiContent_Frame::addRow(Label* icon, Frame* widget) {
    StretchDisplay_Frame* row = new StretchDisplay_Frame;
    row->setupUi(QSharedPointer<const Protocol>());
    if (icon) {
      row->addIcon(icon);
    }
    if (widget) {
      row->addWidget(widget);
    }
    mMainLayout->addWidget(row);
  }

  // protected
  void TitleMultiContent_Frame::initWindow() {
  }

  void TitleMultiContent_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void TitleMultiContent_Frame::init() {
    mTitle = new Label;
    mMainLayout->addWidget(mTitle);
  }

  /*
   * StorePlanContentAreaContent_Frame
   */
  // cotr
  StorePlanContentAreaContent_Frame::StorePlanContentAreaContent_Frame(QWidget* parent)
    :Frame(parent) {}

  StorePlanContentAreaContent_Frame::~StorePlanContentAreaContent_Frame() {}

  void StorePlanContentAreaContent_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void StorePlanContentAreaContent_Frame::addContent(Frame* content) {
    mMainLayout->addWidget(content);
  }

  void StorePlanContentAreaContent_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  // protected
  void StorePlanContentAreaContent_Frame::initWindow() {
  }

  void StorePlanContentAreaContent_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void StorePlanContentAreaContent_Frame::init() {

  }

  /*
   * StorePlanContentArea_Frame
   */
  // cotr
  StorePlanContentArea_Frame::StorePlanContentArea_Frame(QWidget* parent)
    :Frame(parent) {}

  StorePlanContentArea_Frame::~StorePlanContentArea_Frame() {}

  void StorePlanContentArea_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* StorePlanContentArea_Frame::titleLeft() const {
    return mTitle;
  }

  Label* StorePlanContentArea_Frame::titleRight() const {
    return mDisplay;
  }

  StorePlanContentAreaContent_Frame* StorePlanContentArea_Frame::content() const {
    return dynamic_cast<StorePlanContentAreaContent_Frame*>(mContent);
  }

  Frame* StorePlanContentArea_Frame::seprator() const {
    return mSeprator;
  }

  StretchDisplay_Frame* StorePlanContentArea_Frame::bottom() const {
    return dynamic_cast<StretchDisplay_Frame*>(mBottom);
  }

  // protected
  void StorePlanContentArea_Frame::initWindow() {
  }

  void StorePlanContentArea_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mTitleLayout = new QHBoxLayout;
    mTitleLeftLayout = new QHBoxLayout;
    mTitleRightLayout = new QHBoxLayout;
    mContentLayout = new QHBoxLayout;
    mSepratorLayout = new QHBoxLayout;
    mBottomLayout = new QHBoxLayout;
    mMainLayout->addLayout(mTitleLayout);
    mMainLayout->addLayout(mContentLayout);
    mMainLayout->addLayout(mSepratorLayout);
    mMainLayout->addLayout(mBottomLayout);
    mTitleLayout->addLayout(mTitleLeftLayout);
    mTitleLayout->addStretch();
    mTitleLayout->addLayout(mTitleRightLayout);
  }

  void StorePlanContentArea_Frame::init() {
    mTitle = new Label;
    mDisplay = new Label;
    mContent = new StorePlanContentAreaContent_Frame;
    mContent->setupUi(QSharedPointer<const Protocol>());
    mSeprator = new Frame;
    mSeprator->setupUi(QSharedPointer<const Protocol>());
    mBottom = new StretchDisplay_Frame;
    mBottom->setupUi(QSharedPointer<const Protocol>());
    mTitleLeftLayout->addWidget(mTitle);
    mTitleRightLayout->addWidget(mDisplay);
    mContentLayout->addWidget(mContent);
    mSepratorLayout->addWidget(mSeprator);
    mBottomLayout->addWidget(mBottom);
    mSeprator->setFrameStyle(QFrame::HLine | QFrame::Plain);
  }

  /*
   * UserManageFeature_Frame
   */
  // cotr
  UserManageFeature_Frame::UserManageFeature_Frame(QWidget* parent)
    :Frame(parent) {}

  UserManageFeature_Frame::~UserManageFeature_Frame() {}

  void UserManageFeature_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  HMenuBar_Frame* UserManageFeature_Frame::menuBar() const {
    return dynamic_cast<HMenuBar_Frame*>(mMenu);
  }

  Search_Frame* UserManageFeature_Frame::search() const {
    return dynamic_cast<Search_Frame*>(mSearch);
  }

  DirectoryControl_Frame* UserManageFeature_Frame::directory() const {
    return dynamic_cast<DirectoryControl_Frame*>(mDirectory);
  }

  void UserManageFeature_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  // protected
  void UserManageFeature_Frame::initWindow() {
  }

  void UserManageFeature_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMenuLayout = new QHBoxLayout;
    mSearchLayout = new QHBoxLayout;
    mDirectoryLayout = new QHBoxLayout;
    mMainLayout->addLayout(mMenuLayout);
    mMainLayout->addLayout(mSearchLayout);
    mMainLayout->addLayout(mDirectoryLayout);
  }

  void UserManageFeature_Frame::init() {
    mMenu = new HMenuBar_Frame;
    mMenu->setupUi(QSharedPointer<const Protocol>());
    mSearch = new Search_Frame;
    mSearch->setupUi(QSharedPointer<const Protocol>());
    mDirectory = new DirectoryControl_Frame;
    mDirectory->setupUi(QSharedPointer<const Protocol>());
    mMenuLayout->addWidget(mMenu);
    mSearchLayout->addWidget(mSearch);
    mDirectoryLayout->addWidget(mDirectory);
  }

  /*
   * CheckBox_Frame
   */
  // cotr
  CheckBox_Frame::CheckBox_Frame(QWidget* parent)
    :UniversalLabel_Frame(parent) {}

  CheckBox_Frame::~CheckBox_Frame() {}

  void CheckBox_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    UniversalLabel_Frame::setupUi(protocol);
    init();
  }

  CheckBox* CheckBox_Frame::checkBox() const {
    return mCheckBox;
  }
  // protected
  void CheckBox_Frame::init() {
    mCheckBox = new CheckBox;
    mMainLayout->addWidget(mCheckBox);
  }

  /*
   * MultiRowCheckBox_Frame
   */
  // cotr
  MultiRowCheckBox_Frame::MultiRowCheckBox_Frame(QWidget* parent)
    :Frame(parent) {}

  MultiRowCheckBox_Frame::~MultiRowCheckBox_Frame() {}

  void MultiRowCheckBox_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void MultiRowCheckBox_Frame::addCheckBox(Frame* checkBox) {
    mMainLayout->addWidget(checkBox);
    mWgts[checkBox->productName()] = checkBox;
  }

  CheckBox_Frame* MultiRowCheckBox_Frame::checkBox(const QString proName) const {
    if (mWgts.contains(proName)) {
      return dynamic_cast<CheckBox_Frame*>(mWgts.value(proName));
    }
    return nullptr;
  }
  // protected
  void MultiRowCheckBox_Frame::initWindow() {
  }

  void MultiRowCheckBox_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void MultiRowCheckBox_Frame::init() {

  }

  /*
   * ScrollBarMultiRowCheckBox_Frame
   */
  // cotr
  ScrollBarMultiRowCheckBox_Frame::ScrollBarMultiRowCheckBox_Frame(QWidget* parent)
    :Frame(parent) {}

  ScrollBarMultiRowCheckBox_Frame::~ScrollBarMultiRowCheckBox_Frame() {}

  void ScrollBarMultiRowCheckBox_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  QScrollArea* ScrollBarMultiRowCheckBox_Frame::scrollArea() const {
    return mScrollArea;
  }

  MultiRowCheckBox_Frame* ScrollBarMultiRowCheckBox_Frame::multiRowCheckBoxFrame() const {
    return dynamic_cast<MultiRowCheckBox_Frame*>(mFrame);
  }
  // protected
  void ScrollBarMultiRowCheckBox_Frame::initWindow() {
  }

  void ScrollBarMultiRowCheckBox_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void ScrollBarMultiRowCheckBox_Frame::init() {
    mScrollArea = new QScrollArea;
    mFrame = new MultiRowCheckBox_Frame;
    mFrame->setupUi(QSharedPointer<const Protocol>());
    mScrollArea->setWidget(mFrame);
    mMainLayout->addWidget(mScrollArea);
  }

  /*
   * TitleWidget_Frame
   */
  // cotr
  TitleWidget_Frame::TitleWidget_Frame(QWidget* parent)
    :Frame(parent) {}

  TitleWidget_Frame::~TitleWidget_Frame() {}

  void TitleWidget_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* TitleWidget_Frame::title() const {
    return mTitle;
  }

  void TitleWidget_Frame::addWidget(Frame* widget) {
    mWidget = widget;
    mWidgetLayout->addWidget(widget);
  }

  Frame* TitleWidget_Frame::widget() const {
    return mWidget;
  }

  void TitleWidget_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  // protected
  void TitleWidget_Frame::initWindow() {
  }

  void TitleWidget_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mTitleLayout = new QHBoxLayout;
    mWidgetLayout = new QHBoxLayout;
    mMainLayout->addLayout(mTitleLayout);
    mMainLayout->addLayout(mWidgetLayout);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mWidgetLayout->setContentsMargins(0, 0, 0, 0);
  }

  void TitleWidget_Frame::init() {
    mTitle = new Label;
    mTitleLayout->addWidget(mTitle);
  }

  /*
   * UserManageContentArea_Frame
   */
  // cotr
  UserManageContentArea_Frame::UserManageContentArea_Frame(QWidget* parent)
    :Frame(parent) {}

  UserManageContentArea_Frame::~UserManageContentArea_Frame() {}

  void UserManageContentArea_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* UserManageContentArea_Frame::userType() const {
    return mUserType;
  }

  Label* UserManageContentArea_Frame::userName() const {
    return mUserName;
  }

  Label* UserManageContentArea_Frame::password() const {
    return mPassword;
  }

  Label* UserManageContentArea_Frame::userPriority() const {
    return mUserPriority;
  }

  ComboBox* UserManageContentArea_Frame::userTypeWgt() const {
    return mUserTypeWgt;
  }

  LineEdit* UserManageContentArea_Frame::userNameWgt() const {
    return mUserNameWgt;
  }

  Label_Frame* UserManageContentArea_Frame::passwordWgt() const {
    return dynamic_cast<Label_Frame*>(mPasswordWgt);
  }

  TitleWidget_Frame* UserManageContentArea_Frame::userPriorityWgt() const {
    return dynamic_cast<TitleWidget_Frame*>(mUserPriorityWgt);
  }

  HMenuBar_Frame* UserManageContentArea_Frame::bottom() const {
    return dynamic_cast<HMenuBar_Frame*>(mBottom);
  }

  TitleWidget_Frame* UserManageContentArea_Frame::resourcePriorityWgt() const {
    return dynamic_cast<TitleWidget_Frame*>(mResPriortyWgt);
  }

  void UserManageContentArea_Frame::leftAreaAddStretch() {
    mLeftLayout->addStretch();
  }

  void UserManageContentArea_Frame::midAreaAddStretch() {
    mMidLayout->addStretch();
  }

  void UserManageContentArea_Frame::rightAreaAddStretch() {
    mRightLayout->addStretch();
  }

  // protected
  void UserManageContentArea_Frame::initWindow() {
  }

  void UserManageContentArea_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mLeftLayout = new QVBoxLayout;
    mMidLayout = new QVBoxLayout;
    mRightLayout = new QVBoxLayout;
    mMainLayout->addLayout(mLeftLayout);
    mMainLayout->addLayout(mMidLayout);
    mMainLayout->addLayout(mRightLayout);
  }

  void UserManageContentArea_Frame::init() {
    mUserType = new Label;
    mUserName = new Label;
    mPassword = new Label;
    mUserPriority = new Label;
    mUserTypeWgt = new ComboBox;
    mUserNameWgt = new LineEdit;
    mPasswordWgt = new Label_Frame;
    mPasswordWgt->setupUi(QSharedPointer<const Protocol>());
    mUserPriorityWgt = new TitleWidget_Frame;
    mUserPriorityWgt->setupUi(QSharedPointer<const Protocol>());
    mResPriortyWgt = new TitleWidget_Frame;
    mResPriortyWgt->setupUi(QSharedPointer<const Protocol>());
    mBottom = new HMenuBar_Frame;
    mBottom->setupUi(QSharedPointer<const Protocol>());
    mLeftLayout->addWidget(mUserType);
    mLeftLayout->addWidget(mUserName);
    mLeftLayout->addWidget(mPassword);
    mLeftLayout->addWidget(mUserPriority);
    mMidLayout->addWidget(mUserTypeWgt);
    mMidLayout->addWidget(mUserNameWgt);
    mMidLayout->addWidget(mPasswordWgt);
    mMidLayout->addWidget(mUserPriorityWgt);
    mMidLayout->addWidget(mBottom);
    mRightLayout->addStretch();
    mRightLayout->addWidget(mResPriortyWgt);
    mRightLayout->addStretch();
  }

  /*
   * SystemConfigureFeature_Frame
   */
  // cotr
  SystemConfigureFeature_Frame::SystemConfigureFeature_Frame(QWidget* parent)
    :Frame(parent) {}

  SystemConfigureFeature_Frame::~SystemConfigureFeature_Frame() {}

  void SystemConfigureFeature_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  DirectoryControl_Frame* SystemConfigureFeature_Frame::directory() const {
    return dynamic_cast<DirectoryControl_Frame*>(mDirectory);
  }
  // protected
  void SystemConfigureFeature_Frame::initWindow() {
  }

  void SystemConfigureFeature_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void SystemConfigureFeature_Frame::init() {
    mDirectory = new DirectoryControl_Frame;
    mDirectory->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addWidget(mDirectory);
  }

  /*
   * SystemConfigureCommonlyUsed_Frame
   */
  // cotr
  SystemConfigureCommonlyUsed_Frame::SystemConfigureCommonlyUsed_Frame(QWidget* parent)
    :Frame(parent) {}

  SystemConfigureCommonlyUsed_Frame::~SystemConfigureCommonlyUsed_Frame() {}

  void SystemConfigureCommonlyUsed_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  StretchDisplay_Frame* SystemConfigureCommonlyUsed_Frame::title() const {
    return dynamic_cast<StretchDisplay_Frame*>(mTitle);
  }

  TwoLabelWidget_Frame* SystemConfigureCommonlyUsed_Frame::log() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mLog);
  }

  TwoLabelWidget_Frame* SystemConfigureCommonlyUsed_Frame::appMax() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mAppMax);
  }

  TwoLabelWidget_Frame* SystemConfigureCommonlyUsed_Frame::network() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mNetwork);
  }

  TwoLabelWidget_Frame* SystemConfigureCommonlyUsed_Frame::keybord() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mKeybord);
  }

  TwoLabelWidget_Frame* SystemConfigureCommonlyUsed_Frame::autoTime() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mAutoTime);
  }

  TwoLabelWidget_Frame* SystemConfigureCommonlyUsed_Frame::beginTime() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mBeginTime);
  }

  HMenuBar_Frame* SystemConfigureCommonlyUsed_Frame::bottom() const {
    return dynamic_cast<HMenuBar_Frame*>(dynamic_cast<TwoLabelWidget_Frame*>(mBottom)->mFrame);
  }

  void SystemConfigureCommonlyUsed_Frame::addStretch() {
    mMainLayout->addStretch();
  }

  // protected
  void SystemConfigureCommonlyUsed_Frame::initWindow() {

  }

  void SystemConfigureCommonlyUsed_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void SystemConfigureCommonlyUsed_Frame::init() {
    mTitle = new StretchDisplay_Frame;
    mTitle->setupUi(QSharedPointer<const Protocol>());
    Label* icon = new Label;
    Label* text = new Label;
    dynamic_cast<StretchDisplay_Frame*>(mTitle)->addIcon(icon);
    dynamic_cast<StretchDisplay_Frame*>(mTitle)->addWidget(text);
    mLog = new TwoLabelWidget_Frame;
    mLog->setupUi(QSharedPointer<const Protocol>());
    ComboBox* logComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mLog)->addWidget(logComboBox);;
    mAppMax = new TwoLabelWidget_Frame;
    mAppMax->setupUi(QSharedPointer<const Protocol>());
    ComboBox* appMaxComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mAppMax)->addWidget(appMaxComboBox);
    mNetwork = new TwoLabelWidget_Frame;
    mNetwork->setupUi(QSharedPointer<const Protocol>());
    Frame* multiRadio = new MultiRadioButton_Frame;
    multiRadio->setupUi(QSharedPointer<const Protocol>());
    dynamic_cast<MultiRadioButton_Frame*>(multiRadio)->addRadioButton();
    dynamic_cast<MultiRadioButton_Frame*>(multiRadio)->addRadioButton();
    dynamic_cast<MultiRadioButton_Frame*>(multiRadio)->addRadioButton();
    dynamic_cast<TwoLabelWidget_Frame*>(mNetwork)->addWidget(multiRadio);
    mKeybord = new TwoLabelWidget_Frame;
    mKeybord->setupUi(QSharedPointer<const Protocol>());
    mAutoTime = new TwoLabelWidget_Frame;
    mAutoTime->setupUi(QSharedPointer<const Protocol>());
    CheckBox* autoTimeCheckBox = new CheckBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mAutoTime)->addWidget(autoTimeCheckBox);
    mBeginTime = new TwoLabelWidget_Frame;
    mBeginTime->setupUi(QSharedPointer<const Protocol>());
    DoubleSpinBox* beginTimeDouSpinBox = new DoubleSpinBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mBeginTime)->addWidget(beginTimeDouSpinBox);
    mBottom = new TwoLabelWidget_Frame;
    mBottom->setupUi(QSharedPointer<const Protocol>());
    Frame* mBottomMenu = new HMenuBar_Frame;
    mBottomMenu->setupUi(QSharedPointer<const Protocol>());
    dynamic_cast<TwoLabelWidget_Frame*>(mBottom)->addWidget(mBottomMenu);
    mMainLayout->addWidget(mTitle);
    mMainLayout->addWidget(mLog);
    mMainLayout->addWidget(mAppMax);
    mMainLayout->addWidget(mNetwork);
    mMainLayout->addWidget(mKeybord);
    mMainLayout->addWidget(mAutoTime);
    mMainLayout->addWidget(mBeginTime);
    mMainLayout->addWidget(mBottom);
  }

  /*
   * MultiRadioButton_Frame
   */
  // cotr
  MultiRadioButton_Frame::MultiRadioButton_Frame(QWidget* parent)
    :Frame(parent) {}

  MultiRadioButton_Frame::~MultiRadioButton_Frame() {}

  void MultiRadioButton_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  void MultiRadioButton_Frame::addRadioButton() {
    RadioButton* radioBtn = new RadioButton;
    mMainLayout->addWidget(radioBtn);
    mBtns.append(radioBtn);
  }

  RadioButton* MultiRadioButton_Frame::button(int index) const {
    if ((-1 < index) && (mBtns.size() > index)) {
      return mBtns.at(index);
    }
    return nullptr;
  }

  // protected
  void MultiRadioButton_Frame::initWindow() {
  }

  void MultiRadioButton_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
  }

  void MultiRadioButton_Frame::init() {

  }

  /*
   * TwoLabelWidget_Frame
   */
  // cotr
  TwoLabelWidget_Frame::TwoLabelWidget_Frame(QWidget* parent)
    :Frame(parent) {}

  TwoLabelWidget_Frame::~TwoLabelWidget_Frame() {}

  void TwoLabelWidget_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* TwoLabelWidget_Frame::leftLabel() const {
    return mLeftLabel;
  }

  Label* TwoLabelWidget_Frame::rightLabel() const {
    return mRightLabel;
  }

  void TwoLabelWidget_Frame::addWidget(Widget* wgt) {
  }

  void TwoLabelWidget_Frame::addWidget(ComboBox* wgt) {
    mMainlayout->addWidget(wgt, 0, Qt::AlignLeft);
    mComboBox = wgt;
  }

  void TwoLabelWidget_Frame::addWidget(RadioButton* wgt) {
    mMainlayout->addWidget(wgt, 0, Qt::AlignLeft);
    mRadioBtn = wgt;
  }

  void TwoLabelWidget_Frame::addWidget(CheckBox* wgt) {
    mMainlayout->addWidget(wgt, 0, Qt::AlignLeft);
    mCheckBox = wgt;
  }

  void TwoLabelWidget_Frame::addWidget(DoubleSpinBox* wgt) {
    mMainlayout->addWidget(wgt, 0, Qt::AlignLeft);
    mDoubleSpinBox = wgt;
  }

  void TwoLabelWidget_Frame::addWidget(Frame* wgt) {
    mMainlayout->addWidget(wgt, 0, Qt::AlignLeft);
    mFrame = wgt;
  }

  // protected
  void TwoLabelWidget_Frame::initWindow() {
  }

  void TwoLabelWidget_Frame::initLayout() {
    mMainlayout = new QHBoxLayout(this);
  }

  void TwoLabelWidget_Frame::init() {
    mLeftLabel = new Label;
    mRightLabel = new Label;
    mMainlayout->addWidget(mLeftLabel, 0, Qt::AlignRight);
    mMainlayout->addWidget(mRightLabel, 0, Qt::AlignRight);
  }

  /*
   * SystemConfigurePreviewPlayback
   */
  // cotr
  SystemConfigurePreviewPlayback::SystemConfigurePreviewPlayback(QWidget* parent)
    :Frame(parent) {}

  SystemConfigurePreviewPlayback::~SystemConfigurePreviewPlayback() {}

  void SystemConfigurePreviewPlayback::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  StretchDisplay_Frame* SystemConfigurePreviewPlayback::title() const {
    return dynamic_cast<StretchDisplay_Frame*>(mTitle);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::pictureType() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mPictureType);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::downFile() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mDownFile);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::search() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mSearch);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::eventPlayback() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mEventPlayback);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::playback() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mPlayback);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::start() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mStart);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::close() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mClose);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::enable() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mEnable);
  }

  TwoLabelWidget_Frame* SystemConfigurePreviewPlayback::automatic() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mAutomatic);
  }

  HMenuBar_Frame* SystemConfigurePreviewPlayback::bottom() const {
    return dynamic_cast<HMenuBar_Frame*>(dynamic_cast<TwoLabelWidget_Frame*>(mBottom)->mFrame);
  }

  void SystemConfigurePreviewPlayback::addStretch() {
    mMainLayout->addStretch();
  }
  // protected
  void SystemConfigurePreviewPlayback::initWindow() {
  }

  void SystemConfigurePreviewPlayback::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void SystemConfigurePreviewPlayback::init() {
    mTitle = new StretchDisplay_Frame;
    mTitle->setupUi(QSharedPointer<const Protocol>());
    Label* icon = new Label;
    Label* text = new Label;
    dynamic_cast<StretchDisplay_Frame*>(mTitle)->addIcon(icon);
    dynamic_cast<StretchDisplay_Frame*>(mTitle)->addWidget(text);
    mPictureType = new TwoLabelWidget_Frame;
    mPictureType->setupUi(QSharedPointer<const Protocol>());
    ComboBox* logComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mPictureType)->addWidget(logComboBox);;
    mDownFile = new TwoLabelWidget_Frame;
    mDownFile->setupUi(QSharedPointer<const Protocol>());
    ComboBox* appMaxComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mDownFile)->addWidget(appMaxComboBox);
    mSearch = new TwoLabelWidget_Frame;
    mSearch->setupUi(QSharedPointer<const Protocol>());
    ComboBox* searchComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mSearch)->addWidget(searchComboBox);
    mEventPlayback = new TwoLabelWidget_Frame;
    mEventPlayback->setupUi(QSharedPointer<const Protocol>());
    ComboBox* eventComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mEventPlayback)->addWidget(eventComboBox);
    mPlayback = new TwoLabelWidget_Frame;
    mPlayback->setupUi(QSharedPointer<const Protocol>());
    mStart = new TwoLabelWidget_Frame;
    mStart->setupUi(QSharedPointer<const Protocol>());
    mClose = new TwoLabelWidget_Frame;
    mClose->setupUi(QSharedPointer<const Protocol>());
    mEnable = new TwoLabelWidget_Frame;
    mEnable->setupUi(QSharedPointer<const Protocol>());
    mAutomatic = new TwoLabelWidget_Frame;
    mAutomatic->setupUi(QSharedPointer<const Protocol>());
    mBottom = new TwoLabelWidget_Frame;
    mBottom->setupUi(QSharedPointer<const Protocol>());
    Frame* mBottomMenu = new HMenuBar_Frame;
    mBottomMenu->setupUi(QSharedPointer<const Protocol>());
    dynamic_cast<TwoLabelWidget_Frame*>(mBottom)->addWidget(mBottomMenu);
    mMainLayout->addWidget(mTitle);
    mMainLayout->addWidget(mPictureType);
    mMainLayout->addWidget(mDownFile);
    mMainLayout->addWidget(mSearch);
    mMainLayout->addWidget(mEventPlayback);
    mMainLayout->addWidget(mPlayback);
    mMainLayout->addWidget(mStart);
    mMainLayout->addWidget(mClose);
    mMainLayout->addWidget(mEnable);
    mMainLayout->addWidget(mAutomatic);
    mMainLayout->addWidget(mBottom);
  };

  /*
   * SystemConfigurePicture_Frame
   */
  // cotr
  SystemConfigurePicture_Frame::SystemConfigurePicture_Frame(QWidget* parent)
    :Frame(parent) {}

  SystemConfigurePicture_Frame::~SystemConfigurePicture_Frame() {}

  void SystemConfigurePicture_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  StretchDisplay_Frame* SystemConfigurePicture_Frame::title() const {
    return dynamic_cast<StretchDisplay_Frame*>(mTitle);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::zoom() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mZoom);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::performance() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mPerformance);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::streamType() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mStreamType);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::decoding() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mDecoding);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::highLight() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mHighLight);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::osd() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mOsd);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::rule() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mRule);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::doubleSpeed() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mDoubleSpeed);
  }

  TwoLabelWidget_Frame* SystemConfigurePicture_Frame::temperature() const {
    return dynamic_cast<TwoLabelWidget_Frame*>(mTemperature);
  }

  HMenuBar_Frame* SystemConfigurePicture_Frame::bottom() const {
    return dynamic_cast<HMenuBar_Frame*>(dynamic_cast<TwoLabelWidget_Frame*>(mBottom)->mFrame);
  }

  void SystemConfigurePicture_Frame::addStretch() {
    mMainLayout->addStretch();
  }
  // protected
  void SystemConfigurePicture_Frame::initWindow() {
  }

  void SystemConfigurePicture_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
  }

  void SystemConfigurePicture_Frame::init() {
    mTitle = new StretchDisplay_Frame;
    mTitle->setupUi(QSharedPointer<const Protocol>());
    Label* icon = new Label;
    Label* text = new Label;
    dynamic_cast<StretchDisplay_Frame*>(mTitle)->addIcon(icon);
    dynamic_cast<StretchDisplay_Frame*>(mTitle)->addWidget(text);
    mZoom = new TwoLabelWidget_Frame;
    mZoom->setupUi(QSharedPointer<const Protocol>());
    ComboBox* logComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mZoom)->addWidget(logComboBox);;
    mPerformance = new TwoLabelWidget_Frame;
    mPerformance->setupUi(QSharedPointer<const Protocol>());
    ComboBox* appMaxComboBox = new ComboBox;
    dynamic_cast<TwoLabelWidget_Frame*>(mPerformance)->addWidget(appMaxComboBox);
    mStreamType = new TwoLabelWidget_Frame;
    mStreamType->setupUi(QSharedPointer<const Protocol>());
    mDecoding = new TwoLabelWidget_Frame;
    mDecoding->setupUi(QSharedPointer<const Protocol>());
    mHighLight = new TwoLabelWidget_Frame;
    mHighLight->setupUi(QSharedPointer<const Protocol>());
    mOsd = new TwoLabelWidget_Frame;
    mOsd->setupUi(QSharedPointer<const Protocol>());
    mRule = new TwoLabelWidget_Frame;
    mRule->setupUi(QSharedPointer<const Protocol>());
    mDoubleSpeed = new TwoLabelWidget_Frame;
    mDoubleSpeed->setupUi(QSharedPointer<const Protocol>());
    mTemperature = new TwoLabelWidget_Frame;
    mTemperature->setupUi(QSharedPointer<const Protocol>());
    mBottom = new TwoLabelWidget_Frame;
    mBottom->setupUi(QSharedPointer<const Protocol>());
    Frame* mBottomMenu = new HMenuBar_Frame;
    mBottomMenu->setupUi(QSharedPointer<const Protocol>());
    dynamic_cast<TwoLabelWidget_Frame*>(mBottom)->addWidget(mBottomMenu);
    mMainLayout->addWidget(mTitle);
    mMainLayout->addWidget(mZoom);
    mMainLayout->addWidget(mPerformance);
    mMainLayout->addWidget(mStreamType);
    mMainLayout->addWidget(mDecoding);
    mMainLayout->addWidget(mHighLight);
    mMainLayout->addWidget(mOsd);
    mMainLayout->addWidget(mRule);
    mMainLayout->addWidget(mDoubleSpeed);
    mMainLayout->addWidget(mTemperature);
    mMainLayout->addWidget(mBottom);
  }

  /*
   * SystemConfigureAccessContorl_Frame
   */
  // cotr
  SystemConfigureAccessContorl_Frame::SystemConfigureAccessContorl_Frame(QWidget* parent)
    :Frame(parent) {}

  SystemConfigureAccessContorl_Frame::~SystemConfigureAccessContorl_Frame() {}

  void SystemConfigureAccessContorl_Frame::setupUi(QSharedPointer<const Protocol> protocol) {

  }

  /*
    * TwoLabelStretchWidget_Frame
    */
  // cotr
  TwoLabelStretchWidget_Frame::TwoLabelStretchWidget_Frame(QWidget* parent)
    :Frame(parent) {}

  TwoLabelStretchWidget_Frame::~TwoLabelStretchWidget_Frame() {}

  void TwoLabelStretchWidget_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Label* TwoLabelStretchWidget_Frame::icon() const {
    return mIcon;
  }

  Label* TwoLabelStretchWidget_Frame::content() const {
    return mText;
  }

  Frame* TwoLabelStretchWidget_Frame::widget() const {
    return mWidget;
  }

  void TwoLabelStretchWidget_Frame::addWidget(Frame* widget) {
    mWidget = widget;
    mWgtLayout->addWidget(mWidget);
  }

  // protected
  void TwoLabelStretchWidget_Frame::initWindow() {
  }

  void TwoLabelStretchWidget_Frame::initLayout() {
    mMainLayout = new QHBoxLayout(this);
    mIconLayout = new QHBoxLayout;
    mTextLayout = new QHBoxLayout;
    mWgtLayout = new QHBoxLayout;
    mMainLayout->addLayout(mIconLayout);
    mMainLayout->addLayout(mTextLayout);
    mMainLayout->addStretch();
    mMainLayout->addLayout(mWgtLayout);
  }

  void TwoLabelStretchWidget_Frame::init() {
    mIcon = new Label;
    mText = new Label;
    mIconLayout->addWidget(mIcon);
    mTextLayout->addWidget(mText);
  }

  /*
    * SearchTree_Frame
    */
  // cotr
  SearchTree_Frame::SearchTree_Frame(QWidget* parent)
    :Frame(parent) {}

  SearchTree_Frame::~SearchTree_Frame() {}

  void SearchTree_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Search_Frame* SearchTree_Frame::search() const {
    return dynamic_cast<Search_Frame*>(mSearch);
  }

  Tree *SearchTree_Frame::tree() const {
    return dynamic_cast<Tree*>(mTree);
  }

  // protected
  void SearchTree_Frame::initWindow() {
  }

  void SearchTree_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(2, 0, 0, 0);
  }

  void SearchTree_Frame::init() {
    mSearch = new Search_Frame;
    mSearch->setupUi(QSharedPointer<const Protocol>());
    mTree = new Tree;
    mTree->setupUi(QSharedPointer<const Protocol>());
    mMainLayout->addWidget(mSearch);
    mMainLayout->addWidget(mTree);
  }

  /*
    * SearchList_Frame
    */
  // cotr
  SearchList_Frame::SearchList_Frame(QWidget* parent)
    :Frame(parent) {}

  SearchList_Frame::~SearchList_Frame() {}

  void SearchList_Frame::setupUi(QSharedPointer<const Protocol> protocol) {
    initWindow();
    initLayout();
    init();
  }

  Search_Frame* SearchList_Frame::search() const {
    return dynamic_cast<Search_Frame*>(mSearch);
  }

  QListWidget* SearchList_Frame::list() const {
    return mList;
  }

  void SearchList_Frame::addItem(Frame* widget) {
    QListWidgetItem* item = new QListWidgetItem;
    mList->addItem(item);
    mList->setItemWidget(item, widget);
  }

  // protected
  void SearchList_Frame::initWindow() {
  }

  void SearchList_Frame::initLayout() {
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(2, 0, 0, 0);
  }

  void SearchList_Frame::init() {
    mSearch = new Search_Frame;
    mSearch->setupUi(QSharedPointer<const Protocol>());
    mList = new QListWidget;
    mMainLayout->addWidget(mSearch);
    mMainLayout->addWidget(mList);
  }
}
