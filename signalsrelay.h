/*******************************************************************************
* Description: 信号中转类(单例类,这相当于是业务逻辑上多加的一层,小部件的信号发送到这个类中,
* 这个类把这个信号再发出去,让别的小部件接收并处理,相当于抽象了一层松耦合)
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#ifndef SIGNALSRELAY_H
#define SIGNALSRELAY_H

#include <QObject>
#include <QSharedPointer>

namespace Jinhui {
  /*
   * 基类 信号中转类
   */
  class SignalsRelay : public QObject {
    Q_OBJECT
  public:
    virtual ~SignalsRelay();
    static QSharedPointer<SignalsRelay> getInstance();
  Q_SIGNALS:
    // 中继的哪个类的信号(下面注释中标注出了是中继的哪个类的信号)
    // 函数命名规则: 中继的类的名称_中继的类中的信号名
    /*
     * 主菜单按钮类
     */
    void menuPushButton_clicked();
  private:
    SignalsRelay(QObject* parent = nullptr);
  private:
    static QSharedPointer<SignalsRelay> mInstance;
  };

}
#endif // SIGNALSRELAY_H
