/*******************************************************************************
* Description: 标签类
* Author: Niu yi qun
* Creation date: 2019/6/25
* Last modified person: Niu yi qun
* Last modified date: 2019/6/25
******************************************************************************/
#include "include/product.h"
#include "include/common.h"
#include "include/exception.h"

#include <QMouseEvent>
#include <QPainter>
#include <QBitmap>

namespace Jinhui {
  /*
  * Label
  */
  // cotr
  Label::Label(const QString& text, QWidget* parent)
    :QLabel(text, parent) {}

  Label::Label(QWidget* parent)
    :QLabel(parent) {}

  void Label::setMainWindow(QSharedPointer<MainWindow> mainWindow) {
    mMainWindow = mainWindow;
  }

  void Label::setMainWindow_Widget(QSharedPointer<Widget> mainWindow_Widget) {
    mMainWindow_Widget = mainWindow_Widget;
  }

  void Label::setMousetrackingWidget() {}

  void Label::setMinSizeWidget() {}

  void Label::setDefPictureWidget() {}

  void Label::setMouseInWidgetPicture() {}

  // protected
  void Label::setPicture(int width, int height, const QString& fileName) {
    QPixmap originalPixmap(fileName);
    QPixmap scaledPixmap = originalPixmap.scaled(width, height);
    setPixmap(scaledPixmap);
  }

  //void Label::mouseMoveEvent(QMouseEvent *event) {
  //  event->accept();
  //  emit mouseMove(event);
  //  return;
  //}

  //void Label::mousePressEvent(QMouseEvent *event) {
  //  event->accept();
  //  emit mousePress(event);
  //  return;
  //}

  //void Label::mouseReleaseEvent(QMouseEvent *event) {
  //  event->accept();
  //  emit mouseRelease(event);
  //  return;
  //}


  /*
   * MinWindow_Label
   */
  // cotr
  MinWindow_Label::MinWindow_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent) {
    // 为什么不能在成员初始化列表中初始化mProtocol
    mProtocol = protocol;

    setMousetrackingWidget();
    setMinSizeWidget();
    setDefPictureWidget();
  }

  void MinWindow_Label::setMousetrackingWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool mousetracking = strToBool(pro->mousetracking);
    setMouseTracking(mousetracking);
  }

  void MinWindow_Label::setMinSizeWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->minWidgetMinWidth.toInt();
    int minHeight = pro->minWidgetMinHeight.toInt();
    setMinimumSize(minWidth, minHeight);
  }

  void MinWindow_Label::setDefPictureWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->minPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void MinWindow_Label::setMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureMoved = getAbsoluteFilename(pro->picDirPath, pro->minPicMoved);
    setPicture(minWidth, minHeight, pictureMoved);
  }

  void MinWindow_Label::mouseMoveEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);

    setMouseInWidgetPicture();
    //if (frameRect().contains(ev->pos())) {

    //}
  }

  void MinWindow_Label::mouseReleaseEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);

    mMainWindow->showMinimized();
  }


  /*
   * MaxWindow_Label
   */
  // cotr
  MaxWindow_Label::MaxWindow_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent) {
    mProtocol = protocol;

    setMousetrackingWidget();
    setMinSizeWidget();
    setDefPictureWidget();
  }

  void MaxWindow_Label::setMousetrackingWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool mousetracking = strToBool(pro->mousetracking);
    setMouseTracking(mousetracking);
  }

  void MaxWindow_Label::setMinSizeWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->maxWidgetMinWidth.toInt();
    int minHeight = pro->maxWidgetMinHeight.toInt();
    setMinimumSize(minWidth, minHeight);
  }

  void MaxWindow_Label::setDefPictureWidget() {
    setNormalWindowDefPicture();
  }

  void MaxWindow_Label::setMouseInWidgetPicture() {
    if (mMainWindow->isMaximized()) {
      setMaxWindowMouseInWidgetPicture();
    } else {
      setNormalWindowMouseInWidgetPicture();
    }
  }

  void MaxWindow_Label::mouseMoveEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);

    setMouseInWidgetPicture();
  }

  void MaxWindow_Label::mouseReleaseEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);

    if (mMainWindow->isMaximized()) {
      mMainWindow->showNormal();

      setNormalWindowDefPicture();
    } else {
      mMainWindow->showMaximized();

      setMaxWindowDefPicture();
    }
  }

  // private
  void MaxWindow_Label::setNormalWindowDefPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->normalPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void MaxWindow_Label::setNormalWindowMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureMoved = getAbsoluteFilename(pro->picDirPath, pro->normalPicMoved);
    setPicture(minWidth, minHeight, pictureMoved);
  }

  void MaxWindow_Label::setMaxWindowDefPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->maxPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void MaxWindow_Label::setMaxWindowMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureMoved = getAbsoluteFilename(pro->picDirPath, pro->maxPicMoved);
    setPicture(minWidth, minHeight, pictureMoved);
  }

  /*
   * ShutdownWindow_Label
   */
  // cotr
  ShutdownWindow_Label::ShutdownWindow_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent) {
    mProtocol = protocol;

    setMousetrackingWidget();
    setMinSizeWidget();
    setDefPictureWidget();
  }

  void ShutdownWindow_Label::setMousetrackingWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool mousetracking = strToBool(pro->mousetracking);
    setMouseTracking(mousetracking);
  }

  void ShutdownWindow_Label::setMinSizeWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->shutWidgetMinWidth.toInt();
    int minHeight = pro->shutWidgetMinHeight.toInt();
    setMinimumSize(minWidth, minHeight);
  }

  void ShutdownWindow_Label::setDefPictureWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->shutPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void ShutdownWindow_Label::setMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = width();
    QString pictureMoved = getAbsoluteFilename(pro->picDirPath, pro->shutPicMoved);
    setPicture(minWidth, minHeight, pictureMoved);
  }

  // protected
  void ShutdownWindow_Label::mouseMoveEvent(QMouseEvent *ev) {
    setMouseInWidgetPicture();

    //ev->accept();
  }

  void ShutdownWindow_Label::mouseReleaseEvent(QMouseEvent *ev) {
    mMainWindow->close();

    ev->accept();
  }

  /*
   * Titlebar_Label
   */
  // cotr
  Titlebar_Label::Titlebar_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent) {
    mProtocol = protocol;

    //setMinSizeWidget();
    //setDefPictureWidget();
  }

  void Titlebar_Label::setMinSizeWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->titleMinWidgetWidth.toInt();
    int minHeight = pro->titleMinWidgetHeight.toInt();
    setMinimumSize(minWidth, minHeight);
  }

  void Titlebar_Label::setDefPictureWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = width();
    int minHeight = height();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->titlePicName);
    setPixmap(pictureDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  // protected
  void Titlebar_Label::mouseMoveEvent(QMouseEvent *ev) {
    mMainWindow->move(ev->globalPos());
  }

  /*
   * TitlebarMinMaxShut_Label
   */
  // cotr
  TitlebarMinMaxShut_Label::TitlebarMinMaxShut_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent)
    ,mButtonWidth(30)
    ,mButtonDisTop(10)
    ,mSpacing(5)
    ,mLeftButtonPressed(false)
    ,mMainWinMaxDisplayCurrent(false) {
    mProtocol = protocol;
    setMousetrackingWidget();
  }

  TitlebarMinMaxShut_Label::~TitlebarMinMaxShut_Label() {}

  void TitlebarMinMaxShut_Label::setMousetrackingWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool mousetracking = strToBool(pro->mousetracking);
    setMouseTracking(mousetracking);

  }

  void TitlebarMinMaxShut_Label::mouseMoveEvent(QMouseEvent *ev) {
    const QPoint pos = ev->pos();
    if (mLeftButtonPressed && !getMinButtonRegion().contains(pos) && !getMaxButtonRegion().contains(pos)
        && !getShutButtonRegion().contains(pos) && !mMainWinMaxDisplayCurrent) {
      mMainWindow->move(ev->globalPos() - mOldCursorPoint + mMainWindow->pos());
      // 实时更新鼠标上一次的位置
      mOldCursorPoint = ev->globalPos();
      ev->accept();
    }

    if (getMinButtonRegion().contains(pos)) {
      mCurrentTitleButton = MIN;
      update();
      ev->accept();
    } else if (getMaxButtonRegion().contains(pos)) {
      mCurrentTitleButton = MAX;
      update();
      ev->accept();
    } else if (getShutButtonRegion().contains(pos)) {
      mCurrentTitleButton = SHUT;
      update();
      ev->accept();
    } else {
      mCurrentTitleButton = INVALID;
      update();
    }

    ev->ignore();
  }

  void TitlebarMinMaxShut_Label::mousePressEvent(QMouseEvent *ev) {
    if (Qt::LeftButton == ev->button()) {
      mLeftButtonPressed = true;
      mOldCursorPoint = ev->globalPos();
      ev->accept();
    }
    ev->ignore();
  }

  void TitlebarMinMaxShut_Label::mouseReleaseEvent(QMouseEvent *ev) {
    if (Qt::LeftButton == ev->button()) {
      mLeftButtonPressed = false;

      const QPoint pos = ev->pos();
      if (getMinButtonRegion().contains(pos)) {
        mMainWindow->showMinimized();
        ev->accept();
      } else if (getMaxButtonRegion().contains(pos)) {
        if (mMainWindow->isMaximized()) {
          mMainWindow->showNormal();
          mMainWinMaxDisplayCurrent = false;
        } else {
          mMainWindow->showMaximized();
          mMainWinMaxDisplayCurrent = true;
        }
        ev->accept();
      } else if (getShutButtonRegion().contains(pos)) {
        mMainWindow->close();
        ev->accept();
      }

      mCurrentTitleButton = INVALID;
      update();
    }
    ev->ignore();
  }

  void TitlebarMinMaxShut_Label::paintEvent(QPaintEvent* ev) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    QPainter painter(this);
    if (mMainWinMaxDisplayCurrent) {
      // 标题栏背景
      QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, pro->titlePicName));
      QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
      painter.drawPixmap(rect(), scaPixmap);
      // 最小化按钮
      QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicDefault));
      QPixmap scaMinPixmap = minPixmap.scaled(getMinButtonRegion().width(), getMinButtonRegion().height());
      painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);
      // 最大化按钮
      QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->maxPicDefault));
      QPixmap scaMaxPixmap = maxPixmap.scaled(getMaxButtonRegion().width(), getMaxButtonRegion().height());
      painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);
      // 关闭按钮
      QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicDefault));
      QPixmap scaShutPixmap = shutPixmap.scaled(getShutButtonRegion().width(), getShutButtonRegion().height());
      painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);

      if (MIN == mCurrentTitleButton) {
        QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicMoved));
        QPixmap scaMinPixmap = minPixmap.scaled(getMinButtonRegion().width(), getMinButtonRegion().height());
        painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);

      } else if (MAX == mCurrentTitleButton) {
        QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->maxPicMoved));
        QPixmap scaMaxPixmap = maxPixmap.scaled(getMaxButtonRegion().width(), getMaxButtonRegion().height());
        painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);

      } else if (SHUT == mCurrentTitleButton) {
        QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicMoved));
        QPixmap scaShutPixmap = shutPixmap.scaled(getShutButtonRegion().width(), getShutButtonRegion().height());
        painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);
      }
    } else {
      // 标题栏背景
      QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, pro->titlePicName));
      QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
      painter.drawPixmap(rect(), scaPixmap);
      // 最小化按钮
      QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicDefault));
      QPixmap scaMinPixmap = minPixmap.scaled(getMinButtonRegion().width(), getMinButtonRegion().height());
      painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);
      // 最大化按钮
      QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->normalPicDefault));
      QPixmap scaMaxPixmap = maxPixmap.scaled(getMaxButtonRegion().width(), getMaxButtonRegion().height());
      painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);
      // 关闭按钮
      QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicDefault));
      QPixmap scaShutPixmap = shutPixmap.scaled(getShutButtonRegion().width(), getShutButtonRegion().height());
      painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);

      if (MIN == mCurrentTitleButton) {
        QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicMoved));
        QPixmap scaMinPixmap = minPixmap.scaled(getMinButtonRegion().width(), getMinButtonRegion().height());
        painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);

      } else if (MAX == mCurrentTitleButton) {
        QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->normalPicMoved));
        QPixmap scaMaxPixmap = maxPixmap.scaled(getMaxButtonRegion().width(), getMaxButtonRegion().height());
        painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);

      } else if (SHUT == mCurrentTitleButton) {
        QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicMoved));
        QPixmap scaShutPixmap = shutPixmap.scaled(getShutButtonRegion().width(), getShutButtonRegion().height());
        painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);

      }
    }

    ev->accept();
  }

  void TitlebarMinMaxShut_Label::mouseDoubleClickEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      if (mMainWindow->isMaximized()) {
        mMainWindow->showNormal();
        mMainWinMaxDisplayCurrent = false;
      } else {
        mMainWindow->showMaximized();
        mMainWinMaxDisplayCurrent = true;
      }
      event->accept();
    }
    event->ignore();
  }

  QRect TitlebarMinMaxShut_Label::getMinButtonRegion() {
    return QRect(rect().width() - mButtonWidth * 3, rect().y() + mButtonDisTop
                 ,mButtonWidth, rect().height() - mButtonDisTop);
  }

  QRect TitlebarMinMaxShut_Label::getMaxButtonRegion() {
    return QRect(rect().width() - mButtonWidth * 2, rect().y() + mButtonDisTop
                 ,mButtonWidth, rect().height() - mButtonDisTop);

  }

  QRect TitlebarMinMaxShut_Label::getShutButtonRegion() {
    return QRect(rect().width() - mButtonWidth, rect().y() + mButtonDisTop
                 ,mButtonWidth, rect().height() - mButtonDisTop);

  }

  /*
   * Doorface_Label
   */
  // cotr
  Doorface_Label::Doorface_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent) {
    mProtocol = protocol;
  }

  void Doorface_Label::paintEvent(QPaintEvent* ev) {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    QPainter painter(this);
    QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, pro->doorPicName));
    QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
    painter.drawPixmap(rect(), scaPixmap);
  }

  /*
   * Menu_Label
   */
  // cotr
  Menu_Label::Menu_Label(QSharedPointer<const Protocol> protocol, const QString &fileName, QWidget* parent)
    :Label(parent)
    ,mFileName(fileName) {
    mProtocol = protocol;
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    QPixmap pixmap(getAbsoluteFilename(pro->picDirPath, mFileName));
    setPixmap(pixmap);
    setMask(pixmap.mask());
  }

  void Menu_Label::mouseReleaseEvent(QMouseEvent *ev) {
    if (Qt::LeftButton == ev->button()) {
      emit clicked();
      ev->accept();
    }

    ev->ignore();
  }

  /*
   * MenuItem_Label
   */
  // cotr
  MenuItem_Label::MenuItem_Label(QSharedPointer<const Protocol> protocol, const QString& itemDefaultPicture
                                 ,const QString& itemClickedPicture, QWidget* parent)
    :Label(parent)
    ,mItemDefaultPicture(itemDefaultPicture)
    ,mItemClickedPicture(itemClickedPicture) {
    mProtocol = protocol;
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    QPixmap pixmap(getAbsoluteFilename(pro->picDirPath, mItemDefaultPicture));
    setPixmap(pixmap);
    setMask(pixmap.mask());
  }

  QSize MenuItem_Label::sizeHint() const {
    return minimumSizeHint();
  }

  QSize MenuItem_Label::minimumSizeHint() const {
    return QSize(140, 30);
  }

  //void MenuItem_Label::paintEvent(QPaintEvent *event) {
  //  Q_UNUSED(event);

  //  QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

  //  QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, mFileName));
  //  QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
  //  setPixmap(scaPixmap);
  //  setMask(scaPixmap.mask());
  //}

  void MenuItem_Label::mousePressEvent(QMouseEvent *ev) {
    if (Qt::LeftButton == ev->button()) {
      QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

      QPixmap pixmap(getAbsoluteFilename(pro->picDirPath, mItemClickedPicture));
      setPixmap(pixmap);
      setMask(pixmap.mask());

      ev->accept();
    }
    ev->ignore();
  }

  void MenuItem_Label::mouseReleaseEvent(QMouseEvent *ev) {
    if (Qt::LeftButton == ev->button()) {
      QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

      QPixmap pixmap(getAbsoluteFilename(pro->picDirPath, mItemDefaultPicture));
      setPixmap(pixmap);
      setMask(pixmap.mask());

      emit clicked();
      ev->accept();
    }

    ev->ignore();
  }

  /*
   * MinimizeMainWindow_Label
   */
  // cotr
  MinimizeMainWindow_Label::MinimizeMainWindow_Label(QWidget* parent)
    :Label(parent) {}

  MinimizeMainWindow_Label::~MinimizeMainWindow_Label() {}
  // protected
  void MinimizeMainWindow_Label::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      event->accept();
      mMainWindow_Widget->showMinimized();
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * MaximizeMainWindow_Label
   */
  // cotr
  MaximizeMainWindow_Label::MaximizeMainWindow_Label(QWidget* parent)
    :Label(parent) {}

  MaximizeMainWindow_Label::~MaximizeMainWindow_Label() {}

  // protected
  void MaximizeMainWindow_Label::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      event->accept();
      if (mMainWindow) {
        if (mMainWindow->isMaximized()) {
          mMainWindow->showNormal();
        } else {
          mMainWindow->showMaximized();
        }
      } else if (mMainWindow_Widget) {
        if (mMainWindow_Widget->isMaximized()) {
          mMainWindow_Widget->showNormal();
        } else {
          mMainWindow_Widget->showMaximized();
        }
      }
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * ShutDownMainWindow_Label
   */
  // cotr
  ShutDownMainWindow_Label::ShutDownMainWindow_Label(QWidget* parent)
    :Label(parent) {}

  ShutDownMainWindow_Label::~ShutDownMainWindow_Label() {}

  // protected
  void ShutDownMainWindow_Label::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      event->accept();
      mMainWindow_Widget->close();
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * DealWithMouseEvent_Label
   */
  // cotr
  DealWithMouseEvent_Label::DealWithMouseEvent_Label(QWidget* parent)
    :Label(parent) {
    setMouseTracking(true);
  }

  DealWithMouseEvent_Label::~DealWithMouseEvent_Label() {}

  void DealWithMouseEvent_Label::setDefPicture(const QString& picturePath) {
    mDefPicture.load(picturePath);
  }

  void DealWithMouseEvent_Label::setMovePicture(const QString& picturePath) {
    mMovePicture.load(picturePath);
  }

  void DealWithMouseEvent_Label::setClickPicture(const QString& picturePath) {
    mClickPicture.load(picturePath);
  }

  // protected
  void DealWithMouseEvent_Label::leaveEvent(QEvent *event) {
    event->accept();
    setPixmap(mDefPicture);
    return;
  }

  void DealWithMouseEvent_Label::mouseMoveEvent(QMouseEvent *event) {
    event->accept();
    setPixmap(mMovePicture);
    return;
  }

  void DealWithMouseEvent_Label::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    return;
  }

  void DealWithMouseEvent_Label::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton ==event->button()) {
      event->accept();
      setPixmap(mClickPicture);
      emit leftButtonReleased();
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * DealWithMouseEventEx_Label
   */
  // cotr
  DealWithMouseEventEx_Label::DealWithMouseEventEx_Label(QWidget* parent)
    :Label(parent) {}

  DealWithMouseEventEx_Label::~DealWithMouseEventEx_Label() {}

  void DealWithMouseEventEx_Label::setUserData(Product* data) {
    mData = data;
  }

  Product* DealWithMouseEventEx_Label::data() const {
    return mData;
  }

  // protected
  //void DealWithMouseEventEx_Label::leaveEvent(QEvent *event) {
  //}

  //void DealWithMouseEventEx_Label::mouseMoveEvent(QMouseEvent *event) {
  //}

  //void DealWithMouseEventEx_Label::mousePressEvent(QMouseEvent *event) {
  //}

  void DealWithMouseEventEx_Label::mouseReleaseEvent(QMouseEvent *event) {
    if (Qt::LeftButton ==event->button()) {
      event->accept();
      emit leftButtonReleased();
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * IVMS4200ExpandStatusBar_Label
   */
  // cotr
  IVMS4200ExpandStatusBar_Label::IVMS4200ExpandStatusBar_Label(QWidget* parent)
    :DealWithMouseEvent_Label(parent) {}

  IVMS4200ExpandStatusBar_Label::~IVMS4200ExpandStatusBar_Label() {}

  // protected
  void IVMS4200ExpandStatusBar_Label::mouseReleaseEvent(QMouseEvent *event) {
    DealWithMouseEvent_Label::mouseReleaseEvent(event);
    if (Qt::LeftButton == event->button()) {
      QRect mainWindowRect = mMainWindow_Widget->frameGeometry();
      Widget* expandStatusBar = dynamic_cast<IntrusionDetection_MainWindow*>(mMainWindow_Widget.data())
                                ->expandStatusBar();
      expandStatusBar->setGeometry(mMainWindow_Widget->mapFromGlobal(mMainWindow_Widget->pos()).x()
                                   ,mainWindowRect.height() - expandStatusBar->height()
                                   ,mainWindowRect.width(), expandStatusBar->height());
      expandStatusBar->show();
      event->accept();
      return;
    } else {
      event->ignore();
      return;
    }
  }

  /*
   * ClearContentLineEdit_Label
   */
  // cotr
  ClearContentWidget_Label::ClearContentWidget_Label(Product *widget, QWidget* parent)
    :DealWithMouseEvent_Label(parent)
    ,mWidget(widget) {}

  ClearContentWidget_Label::~ClearContentWidget_Label() {}

  //protected
  void ClearContentWidget_Label::mousePressEvent(QMouseEvent *event) {
    try {
      if (!mWidget) {
        throw PointerIsNull_Exception();
      }
    } catch (ParameterException& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
      return;
    }

    try {
      LineEdit* wgt = dynamic_cast<LineEdit*>(mWidget);
      if (!wgt) {
        throw Dynamic_cast_Down_Exception();
      }
      wgt->clear();
      emit clearCompleted();
    } catch (Dynamic_cast_Exception& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
      return;
    }
  }

  /*
   * Search_Label
   */
  // cotr
  Search_Label::Search_Label(QWidget* parent)
    :DealWithMouseEvent_Label(parent) {}

  Search_Label::~Search_Label() {}

  // protected
  void Search_Label::mousePressEvent(QMouseEvent *event) {

  }
}
