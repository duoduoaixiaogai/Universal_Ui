#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "global.h"

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
  class EXPORT Exception/* : public QObject*/ {
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
  class EXPORT FileException : public Exception {
  public:
    FileException(/*QObject *parent = nullptr*/);
    ~FileException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 字符编码格式错误异常类
   */
  class EXPORT CharactersEncodingFormatErr : public FileException {
  public:
    CharactersEncodingFormatErr() = default;
    ~CharactersEncodingFormatErr() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 解析器异常类
   */
  class EXPORT ParserException : public Exception {
  public:
    ParserException() = default;
    ~ParserException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 协议异常类
   */
  class EXPORT ProtocolException : public Exception {
  public:
    ProtocolException() = default;
    ~ProtocolException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 语言异常类
   */
  class EXPORT LanguageException : public Exception {
  public:
    LanguageException() = default;
    ~LanguageException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 参数异常类
   */
  class EXPORT ParameterException : public Exception {
  public:
    ParameterException() = default;
    ~ParameterException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 数据库异常类
   */
  class EXPORT DatabaseException : public Exception {
  public:
    DatabaseException() = default;
    ~DatabaseException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 基类 容器异常类
   */
  class EXPORT ContainerException : public Exception {
  public:
    ContainerException() = default;
    ~ContainerException() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*******************************************************************************
   * 子类
   ******************************************************************************/
  /*
   * 子类 文件打不开异常类
   */
  class EXPORT FileExceptionOpenErr : public FileException {
  public:
    FileExceptionOpenErr(/*QObject *parent = nullptr*/);
    ~FileExceptionOpenErr() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 文件不存在异常类
   */
  class EXPORT FileExceptionNotExist : public FileException {
  public:
    FileExceptionNotExist() = default;
    ~FileExceptionNotExist() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };


  /*
   * 子类 XML解析器异常类
   */
  class EXPORT ParserExceptionXml : public ParserException {
  public:
    ParserExceptionXml() = default;
    ~ParserExceptionXml() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * XML版本不正确异常类
   */
  class EXPORT IncorrectVersion : public ParserExceptionXml {
  public:
    IncorrectVersion() = default;
    ~IncorrectVersion() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 元素的标签不正确
   */
  class EXPORT LabelIsIncorrect : public ParserExceptionXml {
  public:
    LabelIsIncorrect() = default;
    ~LabelIsIncorrect() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 高铁线路缺陷系统XML解析器异常类
   */
  class EXPORT ParserExceptionGTXLQX : public ParserExceptionXml {
  public:
    ParserExceptionGTXLQX() = default;
    ~ParserExceptionGTXLQX() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * PrematureEndOfDocumentError异常类
   */
  class EXPORT PrematureEndOfDocumentError : public ParserExceptionGTXLQX {
  public:
    PrematureEndOfDocumentError() = default;
    ~PrematureEndOfDocumentError() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   *  NotWellFormedError异常类
   */
  class EXPORT NotWellFormedError : public ParserExceptionGTXLQX {
  public:
    NotWellFormedError() = default;
    ~NotWellFormedError() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };


  /*
   * 子类 向上协议转换异常类
   */
  class EXPORT UpcastProtocolConversion : public ProtocolException {
  public:
    UpcastProtocolConversion() = default;
    ~UpcastProtocolConversion() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 向下协议转换异常类
   */
  class EXPORT DowncastProtocolConversion : public ProtocolException {
  public:
    DowncastProtocolConversion() = default;
    ~DowncastProtocolConversion() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 加载翻译文件异常类
   */
  class EXPORT LoadTranslationFile : public LanguageException {
  public:
    LoadTranslationFile() = default;
    ~LoadTranslationFile() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 删除翻译文件异常类
   */
  class EXPORT delTranslationFile : public LanguageException {
  public:
    delTranslationFile() = default;
    ~delTranslationFile() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 添加翻译文件异常类
   */
  class EXPORT addTranslationFile : public LanguageException {
  public:
    addTranslationFile() = default;
    ~addTranslationFile() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 参数数量不正确
   */
  class EXPORT IncorrectNumberParameters : public ParameterException {
  public:
    IncorrectNumberParameters() = default;
    ~IncorrectNumberParameters() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 数据库连接失败异常
   */
  class EXPORT ConnectionFailed_Database : public DatabaseException {
  public:
    ConnectionFailed_Database() = default;
    ~ConnectionFailed_Database() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 QSqlQuery异常类
   */
  class EXPORT SqlQuery_Exception : public DatabaseException {
  public:
    SqlQuery_Exception() = default;
    ~SqlQuery_Exception() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

  /*
   * 子类 容器中的项目数量不正确异常类
   */
  class EXPORT ContainerItemsNumIncorrect : public ContainerException {
  public:
    ContainerItemsNumIncorrect() = default;
    ~ContainerItemsNumIncorrect() = default;
    const QString what() const Q_DECL_OVERRIDE;
  };

}

#endif // EXCEPTION_H
