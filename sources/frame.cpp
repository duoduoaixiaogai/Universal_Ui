/*******************************************************************************
* Description: 拥有框架的小部件的基类
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#include "include/product.h"

#include <QHBoxLayout>

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
}
