/*******************************************************************************
* Description: 标签类
* Author: Niu yi qun
* Creation date: 2019/6/25
* Last modified person: Niu yi qun
* Last modified date: 2019/6/25
******************************************************************************/
#include "product.h"
#include "common.h"

#include <QMouseEvent>
#include <QPainter>

namespace Jinhui {
  /*
  * Label
  */
  // cotr
  Label::Label(QWidget* parent)
    :QLabel(parent) {}

  void Label::setMainWindow(QSharedPointer<MainWindow> mainWindow) {
    mMainWindow = mainWindow;
  }

  void Label::setMousetrackingWidget() {}

  void Label::setMinSizeWidget() {}

  void Label::setDefPictureWidget() {}

  void Label::setMouseInWidgetPicture() {}

  void Label::setPicture(int width, int height, const QString& fileName) {
    QPixmap originalPixmap(fileName);
    QPixmap scaledPixmap = originalPixmap.scaled(width, height);
    setPixmap(scaledPixmap);
  }

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

    mMainWindow->mMainWindow->showMinimized();
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
    if (mMainWindow->mMainWindow->isMaximized()) {
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

    if (mMainWindow->mMainWindow->isMaximized()) {
      mMainWindow->mMainWindow->showNormal();

      setNormalWindowDefPicture();
    } else {
      mMainWindow->mMainWindow->showMaximized();

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
    mMainWindow->mMainWindow->close();

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
    mMainWindow->mMainWindow->move(ev->globalPos());
  }

  /*
   * TitlebarMinMaxShut_Label
   */
  // cotr
  TitlebarMinMaxShut_Label::TitlebarMinMaxShut_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent)
    ,mButtonWidth(30)
    ,mButtonHeight(10)
    ,mSpacing(5)
    ,mLeftButtonPressed(false)
    ,mMainWinMaxDisplayCurrent(false) {
    mProtocol = protocol;
    setMousetrackingWidget();
  }

  void TitlebarMinMaxShut_Label::setMousetrackingWidget() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    bool mousetracking = strToBool(pro->mousetracking);
    setMouseTracking(mousetracking);

  }

  void TitlebarMinMaxShut_Label::mouseMoveEvent(QMouseEvent *ev) {
    const QPoint pos = ev->pos();
    if (mLeftButtonPressed && !getMinButtonRegion().contains(pos) && !getMaxButtonRegion().contains(pos)
        && !getShutButtonRegion().contains(pos) && !mMainWinMaxDisplayCurrent) {
      mMainWindow->mMainWindow->move(ev->globalPos() - mOldCursorPoint + mMainWindow->mMainWindow->pos());
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
        mMainWindow->mMainWindow->showMinimized();
        ev->accept();
      } else if (getMaxButtonRegion().contains(pos)) {
        if (mMainWindow->mMainWindow->isMaximized()) {
          mMainWindow->mMainWindow->showNormal();
          mMainWinMaxDisplayCurrent = false;
        } else {
          mMainWindow->mMainWindow->showMaximized();
          mMainWinMaxDisplayCurrent = true;
        }
        ev->accept();
      } else if (getShutButtonRegion().contains(pos)) {
        mMainWindow->mMainWindow->close();
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
      QPixmap scaMinPixmap = minPixmap.scaled(mButtonWidth, mButtonHeight);
      painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);
      // 最大化按钮
      QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->maxPicDefault));
      QPixmap scaMaxPixmap = maxPixmap.scaled(mButtonWidth, mButtonHeight);
      painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);
      // 关闭按钮
      QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicDefault));
      QPixmap scaShutPixmap = shutPixmap.scaled(mButtonWidth, mButtonHeight);
      painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);

      if (MIN == mCurrentTitleButton) {
        QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicMoved));
        QPixmap scaMinPixmap = minPixmap.scaled(mButtonWidth, mButtonHeight);
        painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);

      } else if (MAX == mCurrentTitleButton) {
        QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->maxPicMoved));
        QPixmap scaMaxPixmap = maxPixmap.scaled(mButtonWidth, mButtonHeight);
        painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);

      } else if (SHUT == mCurrentTitleButton) {
        QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicMoved));
        QPixmap scaShutPixmap = shutPixmap.scaled(mButtonWidth, mButtonHeight);
        painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);
      }
    } else {
      // 标题栏背景
      QPixmap oriPixmap(getAbsoluteFilename(pro->picDirPath, pro->titlePicName));
      QPixmap scaPixmap = oriPixmap.scaled(rect().width(), rect().height());
      painter.drawPixmap(rect(), scaPixmap);
      // 最小化按钮
      QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicDefault));
      QPixmap scaMinPixmap = minPixmap.scaled(mButtonWidth, mButtonHeight);
      painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);
      // 最大化按钮
      QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->normalPicDefault));
      QPixmap scaMaxPixmap = maxPixmap.scaled(mButtonWidth, mButtonHeight);
      painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);
      // 关闭按钮
      QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicDefault));
      QPixmap scaShutPixmap = shutPixmap.scaled(mButtonWidth, mButtonHeight);
      painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);

      if (MIN == mCurrentTitleButton) {
        QPixmap minPixmap(getAbsoluteFilename(pro->picDirPath, pro->minPicMoved));
        QPixmap scaMinPixmap = minPixmap.scaled(mButtonWidth, mButtonHeight);
        painter.drawPixmap(getMinButtonRegion(), scaMinPixmap);

      } else if (MAX == mCurrentTitleButton) {
        QPixmap maxPixmap(getAbsoluteFilename(pro->picDirPath, pro->normalPicMoved));
        QPixmap scaMaxPixmap = maxPixmap.scaled(mButtonWidth, mButtonHeight);
        painter.drawPixmap(getMaxButtonRegion(), scaMaxPixmap);

      } else if (SHUT == mCurrentTitleButton) {
        QPixmap shutPixmap(getAbsoluteFilename(pro->picDirPath, pro->shutPicMoved));
        QPixmap scaShutPixmap = shutPixmap.scaled(mButtonWidth, mButtonHeight);
        painter.drawPixmap(getShutButtonRegion(), scaShutPixmap);

      }
    }

    ev->accept();
  }

  void TitlebarMinMaxShut_Label::mouseDoubleClickEvent(QMouseEvent *event) {
    if (Qt::LeftButton == event->button()) {
      if (mMainWindow->mMainWindow->isMaximized()) {
        mMainWindow->mMainWindow->showNormal();
        mMainWinMaxDisplayCurrent = false;
      } else {
        mMainWindow->mMainWindow->showMaximized();
        mMainWinMaxDisplayCurrent = true;
      }
      event->accept();
    }
    event->ignore();
  }

  QRect TitlebarMinMaxShut_Label::getMinButtonRegion() {
    return QRect(rect().width() - mButtonWidth * 3, rect().y() + mButtonHeight
                 ,mButtonWidth, mButtonHeight);
  }

  QRect TitlebarMinMaxShut_Label::getMaxButtonRegion() {
    return QRect(rect().width() - mButtonWidth * 2, rect().y() + mButtonHeight
                 ,mButtonWidth, mButtonHeight);

  }

  QRect TitlebarMinMaxShut_Label::getShutButtonRegion() {
    return QRect(rect().width() - mButtonWidth, rect().y() + mButtonHeight
                 ,mButtonWidth, mButtonHeight);

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

}
