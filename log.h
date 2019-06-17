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
        static QSharedPointer<Log> instance(QObject *parent = nullptr);
        ~Log() = default;
    private:
        Log(QObject *parent = nullptr);

        // Message handle callback function
        void logMessageHandler(QtMsgType msgType, const QMessageLogContext& msgLogContext, const QString& msg);
    private:
        // Create log file folder
        const QString createFileFolder(const QString& fileFolder =
                QString("%1%2%3%4")
                .arg(qApp->applicationDirPath())
                .arg("/log/")
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
        void writeLog(LogLevel logLve, const QString& msg);

    private:
        static QSharedPointer<Log> mInstance;

        QMutex mMutex;

        const QString mInfo, mWarn, mFatal;
    };
}

#endif // LOG_H
