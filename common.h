/*******************************************************************************
* Description: 共同使用的接口(不以单例模式实现)
* 1、类似于注册机制.
* 2、程序main函数运行之前会提前执行.
* Author: Niu yi qun
* Creation date: 2019/6/18
* Last modified date: 2019/6/18
******************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QCoreApplication>

namespace Jinhui {
  // 获取配置文件路径
  static QString getConfigFilePath() {
    return qApp->applicationDirPath()
        .append('/')
        .append("config.xml");
  }

  // 获取Ui文件路径
  static QString getUiFilePath() {
    return qApp->applicationDirPath()
        .append('/')
        .append("ui.xml");
  }
}

#endif // COMMON_H
