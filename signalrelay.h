/*******************************************************************************
* Description: 信号中转类(单例类,这相当于是业务逻辑上多加的一层,小部件的信号发送到这个类中,
* 这个类把这个信号再发出去,让别的小部件接收并处理,相当于抽象了一层松耦合)
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#ifndef SIGNALRELAY_H
#define SIGNALRELAY_H

#include <QObject>
#include <QSharedPointer>

namespace Jinhui {
  /*
   * 基类 信号中转类
   */
  class SignalRelay : public QObject {
    Q_OBJECT
  public:
    virtual ~SignalRelay();
    static QSharedPointer<SignalRelay> getInstance();
  private:
    SignalRelay(QObject* parent = nullptr);
  private:
    static QSharedPointer<SignalRelay> mInstance;
  };

}
#endif // SIGNALRELAY_H
