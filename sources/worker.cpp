/*******************************************************************************
* Description: 工作者基类(工作者--对象方法)
* Author: Niu yi qun
* Creation date: 2019/7/9
* Last modified person: Niu yi qun
* Last modified date: 2019/7/9
******************************************************************************/
#include "include/product.h"
#include "include/common.h"
#include "include/qttoopencv.h"

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
    :Worker(parent) {}

  Channel32_Worker::~Channel32_Worker() {}

  void Channel32_Worker::doWork() {
    const std::string videoStreamAddress = "rtsp://admin:ferret123@192.168.8.31:554/main/Channels/1";
    cv::VideoCapture vcap;
    vcap.open(videoStreamAddress);
    QtToOpencv::ImageConversion conv;
    RowsColumns rowsColumns = splitScreenToSize(THIRTYTWO);

    while (true) {
      cv::Mat frame;
      vcap >> frame;
      QVariantHash pixmaps;
      for (int i = 0; i < rowsColumns.rows * rowsColumns.columns; ++i) {
        QPixmap oriPixmap = conv.cvMatToQPixmap(frame);
        pixmaps[QString::number(i)] = oriPixmap;
      }
      emit resultReady(pixmaps);
      //cv::imshow("pic", frame);
      //cv::waitKey(30);
      QThread::msleep(40);
    }
  }

}
