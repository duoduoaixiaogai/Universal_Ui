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
  // 获取可执行文件所在的目录路径
  static QString getExeInDirPath() {
    return qApp->applicationDirPath();
  }

  // 获取配置文件路径
  static QString getConfigFilePath() {
    return getExeInDirPath()
        .append("/xml/")
        .append("config.xml");
  }

  // 获取Ui文件路径
  static QString getUiFilePath() {
    return getExeInDirPath()
        .append("/xml/")
        .append("ui.xml");
  }

  // 字符串转布尔类型(字符串为: yes no; true false;)
  static bool strToBool(const QString& str) {
    if (0 == str.compare(QLatin1String("yes"), Qt::CaseInsensitive)) {
      return true;
    } else if (0 == str.compare(QLatin1String("true"), Qt::CaseInsensitive)) {
      return true;
    } else if (0 == str.compare(QLatin1String("no"), Qt::CaseInsensitive)) {
      return false;
    } else if (0 == str.compare(QLatin1String("false"), Qt::CaseInsensitive)) {
      return false;
    }

    // 默认值为 true
    return true;
  }

}

#endif // COMMON_H
