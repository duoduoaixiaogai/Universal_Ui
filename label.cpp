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

    int minWidth = pro->minWidgetMinWidth.toInt();
    int minHeight = pro->minWidgetMinHeight.toInt();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->minPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void MinWindow_Label::setMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->minWidgetMinWidth.toInt();
    int minHeight = pro->minWidgetMinHeight.toInt();
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

    int minWidth = pro->normalWidgetMinWidth.toInt();
    int minHeight = pro->normalWidgetMinHeight.toInt();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->normalPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void MaxWindow_Label::setNormalWindowMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->normalWidgetMinWidth.toInt();
    int minHeight = pro->normalWidgetMinHeight.toInt();
    QString pictureMoved = getAbsoluteFilename(pro->picDirPath, pro->normalPicMoved);
    setPicture(minWidth, minHeight, pictureMoved);
  }

  void MaxWindow_Label::setMaxWindowDefPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->maxWidgetMinWidth.toInt();
    int minHeight = pro->maxWidgetMinHeight.toInt();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->maxPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void MaxWindow_Label::setMaxWindowMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->maxWidgetMinWidth.toInt();
    int minHeight = pro->maxWidgetMinHeight.toInt();
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

    int minWidth = pro->shutWidgetMinWidth.toInt();
    int minHeight = pro->shutWidgetMinHeight.toInt();
    QString pictureDefault = getAbsoluteFilename(pro->picDirPath, pro->shutPicDefault);
    setPicture(minWidth, minHeight, pictureDefault);
  }

  void ShutdownWindow_Label::setMouseInWidgetPicture() {
    QSharedPointer<const GTXLQXPro> pro = qSharedPointerCast<const GTXLQXPro, const Protocol>(mProtocol);

    int minWidth = pro->shutWidgetMinWidth.toInt();
    int minHeight = pro->shutWidgetMinHeight.toInt();
    QString pictureMoved = getAbsoluteFilename(pro->picDirPath, pro->shutPicMoved);
    setPicture(minWidth, minHeight, pictureMoved);
  }

  // protected
  void ShutdownWindow_Label::mouseMoveEvent(QMouseEvent *ev) {
    setMouseInWidgetPicture();

    ev->accept();
  }

  void ShutdownWindow_Label::mouseReleaseEvent(QMouseEvent *ev) {
    mMainWindow->mMainWindow->close();
  }

  /*
   * Titlebar_Label
   */
  // cotr
  Titlebar_Label::Titlebar_Label(QSharedPointer<const Protocol> protocol, QWidget* parent)
    :Label(parent) {
    mProtocol = protocol;
  }

  // protected
  void Titlebar_Label::mouseMoveEvent(QMouseEvent *ev) {
    mMainWindow->mMainWindow->move(ev->globalPos());
  }

}
