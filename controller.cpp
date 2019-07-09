/*******************************************************************************
* Description: 控制者基类(工作者--对象方法)
* Author: Niu yi qun
* Creation date: 2019/7/9
* Last modified person: Niu yi qun
* Last modified date: 2019/7/9
******************************************************************************/
#include "product.h"

namespace Jinhui {
  /*
   * Controller
   */
  // cotr
  Controller::Controller(Worker *worker, QObject* parent)
    :QObject(parent)
    ,mWorker(worker) {
    Q_ASSERT(mWorker);
    mWorker->moveToThread(&mWorkerThread);
    connect(&mWorkerThread, SIGNAL(finished()), mWorker, SLOT(deleteLater()));
  }

  Controller::~Controller() {
    mWorkerThread.quit();
    mWorkerThread.wait();
  }

  /*
   * Channel32_Controller
   */
  // cotr
  Channel32_Controller::Channel32_Controller(QObject* parent)
    :Controller(new Channel32_Worker, parent) {
    //qRegisterMetaType<Channel_Frame>();
    qRegisterMetaType<Jinhui::Product>();
    connect(this, SIGNAL(operate(QVector<Channel_Frame*>))
            ,dynamic_cast<Channel32_Worker*>(mWorker), SLOT(doWork(QVector<Channel_Frame*>)));
    //connect(this, SIGNAL(operate())
    //        ,dynamic_cast<Channel32_Worker*>(mWorker), SLOT(doWork()));
    mWorkerThread.start();
    //QVector<Channel_Frame*> test;
    //emit this->operate();
  }

  Channel32_Controller::~Channel32_Controller() {}

}
