#include "log.h"
#include "exception.h"

#include <QMutexLocker>
#include <QDir>
#include <QFile>
#include <QTextStream>

namespace Jinhui {
  // Static variable initalize out of class
  const QString Log::mInfo = tr("INFO");
  const QString Log::mWarn = tr("WARN");
  const QString Log::mFatal = tr("FATAL");
  QMutex Log::mMutex;

  /*
   * Log
   */
  Log::Log(QObject *parent)
    :QObject(parent) {
    qInstallMessageHandler(Log::logMessageHandler);
  }

  void Log::logMessageHandler(QtMsgType msgType, const QMessageLogContext& msgLogContext, const QString& msg) {
    QString specificMsg;

    QMutexLocker locker(&mMutex);

    LogLevel logLevel = INVALID;
    switch (msgType) {
      case QtDebugMsg:
        // 暂时不处理Debug类型的消息
        break;
      case QtInfoMsg:
        specificMsg = QString("Info: %1 (%2:%3 %4)\n")
                      .arg(msg)
                      .arg(msgLogContext.file)
                      .arg(QString::number(msgLogContext.line))
                      .arg(msgLogContext.function);
        logLevel = INFO;
        break;
      case QtWarningMsg:
        specificMsg = QString("Warning: %1 (%2:%3 %4)\n")
                      .arg(msg)
                      .arg(msgLogContext.file)
                      .arg(QString::number(msgLogContext.line))
                      .arg(msgLogContext.function);
        logLevel = WARN;
        break;
      case QtCriticalMsg:
        // 暂时不处理Critical类型的消息
        break;
      case QtFatalMsg:
        specificMsg = QString("Fatal: %1 (%2:%3 %4)\n")
                      .arg(msg)
                      .arg(msgLogContext.file)
                      .arg(QString::number(msgLogContext.line))
                      .arg(msgLogContext.function);
        logLevel = FATAL;
        break;
    }
    writeLog(logLevel, specificMsg);
  }

  void Log::writeLog(LogLevel logLve, const QString& msg) {
    // 创建日志文件夹
    const QString fileFolder = createFileFolder();

    QString filePath, specificMsg;

    switch (logLve) {
      case INFO:
        filePath = QString("%1/%2.log")
                   .arg(fileFolder)
                   .arg(mInfo);
        break;
      case WARN:
        filePath = QString("%1/%2.log")
                   .arg(fileFolder)
                   .arg(mWarn);
        break;
      case FATAL:
        filePath = QString("%1/%2.log")
                   .arg(fileFolder)
                   .arg(mFatal);
        break;
    }

    specificMsg = QString("%1%2%3%4%5")
                  .arg(tr("Log generation time"))
                  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                  .arg("\r\n日志消息: ")
                  .arg(msg)
                  .arg("\r\n--------------------------------------------------------");

    QFile file(filePath);
    try {
      if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        throw FileExceptionOpenErr();
      }

    } catch (FileException& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
      return;
    }

    QTextStream textStream(&file);
    textStream << specificMsg << QString("\r\n");
    file.flush();
    file.close();
  }

  // private

  const QString Log::createFileFolder(const QString &fileFolder) {
    QDir dir(fileFolder);
    if (!dir.exists()) {
      dir.mkpath(fileFolder);
    }

    return fileFolder;
  }
}
