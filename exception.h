#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QObject>

namespace Jinhui {
  /*
   * 消息等级
   */
  typedef enum MessageLevel {
    INFO = 0x10,
    WARN,
    ERROR,
  } MessageLevel;

  /*******************************************************************************
   * 基类
   ******************************************************************************/
  /*
   * 异常基类
   */
  class Exception/* : public QObject*/ {
  public:
    Exception(/*QObject *parent = nullptr*/);
    virtual ~Exception() = default;
    virtual const QString what() const;
    virtual void writeLogError(const QString& log);
    virtual void writeLogWarn(const QString& log);
    virtual void writeLogInfo(const QString& log);
    virtual void showMessage(QWidget* parent = nullptr, MessageLevel msgLve = INFO, const QString& msg = QString(""));
  private:
    const QString mInfo, mWarn, mError;
  };

  /*
   * 基类 文件异常类(文件相关)
   */
  class FileException : public Exception {
  public:
    FileException(/*QObject *parent = nullptr*/);
    ~FileException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 字符编码格式错误异常类
   */
  class CharactersEncodingFormatErr : public FileException {
  public:
    CharactersEncodingFormatErr() = default;
    ~CharactersEncodingFormatErr() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 解析器异常类
   */
  class ParserException : public Exception {
  public:
    ParserException() = default;
    ~ParserException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 协议异常类
   */
  class ProtocolException : public Exception {
  public:
    ProtocolException() = default;
    ~ProtocolException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*******************************************************************************
   * 子类
   ******************************************************************************/
  /*
   * 子类 文件打不开异常类
   */
  class FileExceptionOpenErr : public FileException {
  public:
    FileExceptionOpenErr(/*QObject *parent = nullptr*/);
    ~FileExceptionOpenErr() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 文件不存在异常类
   */
  class FileExceptionNotExist : public FileException {
  public:
    FileExceptionNotExist() = default;
    ~FileExceptionNotExist() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };


  /*
   * 子类 XML解析器异常类
   */
  class ParserExceptionXml : public ParserException {
  public:
    ParserExceptionXml() = default;
    ~ParserExceptionXml() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * XML版本不正确异常类
   */
  class IncorrectVersion : public ParserExceptionXml {
  public:
    IncorrectVersion() = default;
    ~IncorrectVersion() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 元素的标签不正确
   */
  class LabelIsIncorrect : public ParserExceptionXml {
  public:
    LabelIsIncorrect() = default;
    ~LabelIsIncorrect() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 高铁线路缺陷系统XML解析器异常类
   */
  class ParserExceptionGTXLQX : public ParserExceptionXml {
  public:
    ParserExceptionGTXLQX() = default;
    ~ParserExceptionGTXLQX() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * PrematureEndOfDocumentError异常类
   */
  class PrematureEndOfDocumentError : public ParserExceptionGTXLQX {
  public:
    PrematureEndOfDocumentError() = default;
    ~PrematureEndOfDocumentError() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   *  NotWellFormedError异常类
   */
  class NotWellFormedError : public ParserExceptionGTXLQX {
  public:
    NotWellFormedError() = default;
    ~NotWellFormedError() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };


  /*
   * 子类 向上协议转换异常类
   */
  class UpcastProtocolConversion : public ProtocolException {
  public:
    UpcastProtocolConversion() = default;
    ~UpcastProtocolConversion() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 向下协议转换异常类
   */
  class DowncastProtocolConversion : public ProtocolException {
  public:
    DowncastProtocolConversion() = default;
    ~DowncastProtocolConversion() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };
}

#endif // EXCEPTION_H
