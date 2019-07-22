#ifndef LOG_H
#define LOG_H

#include "global.h"

#include <QObject>
#include <QMutex>
#include <QCoreApplication>
#include <QDateTime>
#include <QSharedPointer>

namespace Jinhui {
  /*
   * Qt自家的日志处理系统
   */
  class EXPORT Log :public QObject {
  public:
    /*
     * 日志等级
     */
    typedef enum LogLevel {
      INVALID = 0x20,
      INFO,
      WARN,
      FATAL,
    } LogLevel;
  public:
    Log(QObject *parent = nullptr);
    ~Log() = default;
  private:
    // Message handle callback function
    static void logMessageHandler(QtMsgType msgType, const QMessageLogContext& msgLogContext, const QString& msg);
    // Create log file folder
    static const QString createFileFolder(const QString& fileFolder =
        QString("%1%2%3")
        .arg(qApp->applicationDirPath())
        .arg("/log/")
        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
    static void writeLog(LogLevel logLve, const QString& msg);

  private:
    static QMutex mMutex;

    static const QString mInfo;
    static const QString mWarn;
    static const QString mFatal;
  };
}

#endif // LOG_H
