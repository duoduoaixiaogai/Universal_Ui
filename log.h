#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QMutex>
#include <QCoreApplication>
#include <QDateTime>
#include <QSharedPointer>

namespace Jinhui {
  /*
   * Qt自家的日志处理系统
   */
  class Log :public QObject {
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
        QString("%1%2%3%4")
        .arg(qApp->applicationDirPath())
        .arg("/log/")
        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
    static void writeLog(LogLevel logLve, const QString& msg);

  private:
    static QMutex mMutex;

    static const QString mInfo, mWarn, mFatal;
  };
}

#endif // LOG_H
