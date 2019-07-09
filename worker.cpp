/*******************************************************************************
* Description: 工作者基类(工作者--对象方法)
* Author: Niu yi qun
* Creation date: 2019/7/9
* Last modified person: Niu yi qun
* Last modified date: 2019/7/9
******************************************************************************/
#include "product.h"
#include "common.h"
#include "qttoopencv.h"

namespace Jinhui {
  /*
   * Worker
   */
  // cotr
  Worker::Worker(QObject* parent)
    :QObject(parent) {}

  Worker::~Worker() {}

  /*
   * Channel32_Worker
   */
  // cotr
  Channel32_Worker::Channel32_Worker(QObject* parent)
    :Worker(parent)
    ,mScene(new Channel32_Scene) {}

  Channel32_Worker::~Channel32_Worker() {}

  void Channel32_Worker::doWork(QVector<Channel_Frame*> channels) {
    populateScene();
    const std::string videoStreamAddress = "rtsp://admin:ferret123@192.168.8.31:554/main/Channels/1";
    cv::VideoCapture vcap;
    vcap.open(videoStreamAddress);
    QtToOpencv::ImageConversion conv;
    RowsColumns rowsColumns = splitScreenToSize(THIRTYTWO);

    for (int i = 0; i < rowsColumns.rows * rowsColumns.columns; ++i) {
      Channel_Frame* channel = channels.at(i);
      channel->view()->setScene(mScene.data());
      channel->view()->setItem(mItems[i]);
    }

    while (true) {
      cv::Mat frame;
      vcap >> frame;
      QPixmap oriPixmap = conv.cvMatToQPixmap(frame);
      for(int i = 0; i < rowsColumns.rows * rowsColumns.columns; ++i) {
        QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(mItems.value(i));
        if (pixmapItem) {
          pixmapItem->setPixmap(oriPixmap);
        }
      }

      QThread::msleep(40);
    }
  }

  //void Channel32_Worker::doWork() {
  //  int i = 10;
  //}

  void Channel32_Worker::populateScene() {
    RowsColumns rowsColumns = splitScreenToSize(THIRTYTWO);
    for(int i = 0; i < rowsColumns.rows * rowsColumns.columns; ++i) {
      mItems[i] = static_cast<GraphicsPixmapItem*>(mScene->addPixmap(QPixmap(resolutionToSize(P1080))));
    }
  }
}
