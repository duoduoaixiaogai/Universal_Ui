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

#include "protocol.h"

#include <QString>
#include <QCoreApplication>
#include <QSize>

#if 1
#include <QDir>
#endif

namespace Jinhui {
  // 获取可执行文件所在的目录路径
  static QString getExeInDirPath() {
    return qApp->applicationDirPath();
  }

  // 获取配置文件路径
  static QString getConfigFilePath() {
#if 1
    return QDir::currentPath()
        .append("/xml/")
        .append("config.xml");
#else
    return getExeInDirPath()
        .append("/xml/")
        .append("config.xml");
#endif
  }

  // 获取Ui文件路径
  static QString getUiFilePath() {
#if 1
    return QDir::currentPath()
        .append("/xml/")
        .append("ui.xml");
#else
    return getExeInDirPath()
        .append("/xml/")
        .append("ui.xml");
#endif
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

  // 拼接指定目录与文件名，返回可执行文件目录下拼接后的文件的绝对路径
  static QString getAbsoluteFilename(const QString& dir, const QString& filename) {
    return getExeInDirPath()
        .append('/')
        .append(dir)
        .append('/')
        .append(filename);
  }

  /*
   * 字符串转对齐类型(字符串为: left, right, hCenter, top, bottom, vCenter)
   */
  static Qt::Alignment strToAlignment(const QString& str) {
    if (0 == str.compare(QLatin1String("left"), Qt::CaseInsensitive)) {
      return Qt::AlignLeft;
    } else if (0 == str.compare(QLatin1String("right"), Qt::CaseInsensitive)) {
      return Qt::AlignRight;
    } else if (0 == str.compare(QLatin1String("hCenter"), Qt::CaseInsensitive)) {
      return Qt::AlignHCenter;
    } else if (0 == str.compare(QLatin1String("top"), Qt::CaseInsensitive)) {
      return Qt::AlignTop;
    } else if (0 == str.compare(QLatin1String("bottom"), Qt::CaseInsensitive)) {
      return Qt::AlignBottom;
    } else if (0 == str.compare(QLatin1String("vCenter"), Qt::CaseInsensitive)) {
      return Qt::AlignVCenter;
    }
  }

  /*
   * 分辩率转尺寸
   */
  static QSize resolutionToSize(Resolution resolution) {
    QSize size;
    switch (resolution) {
      case P1080:
        size.setWidth(1920);
        size.setHeight(1080);
        break;
    }
    return size;
  }

  /*
   * 分屏转行列数(几行几列)
   */
  static RowsColumns splitScreenToSize(SplitScreen splitScreen) {
    RowsColumns rowsColumns;
    switch (splitScreen) {
      case THIRTYTWO:
        rowsColumns.rows = 8;
        rowsColumns.columns = 4;
        break;
    }
    return rowsColumns;
  }

}

#endif // COMMON_H
