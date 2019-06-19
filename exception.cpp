#include "exception.h"

#include <QMessageBox>

namespace Jinhui {

  /*
   * Exception
   */
  // ctor
  Exception::Exception()
  /*:QObject(parent)*/
    :mInfo(QObject::tr("INFO"))
    ,mWarn(QObject::tr("WARN"))
    ,mError(QObject::tr("ERROR")) {}

  const QString Exception::what() const {
    return QObject::tr("Something went wrong here!");
  }

  void Exception::writeLogError(const QString& log) {
    qFatal(log.toLocal8Bit());
  }

  void Exception::writeLogWarn(const QString& log) {
    qWarning(log.toLocal8Bit());
  }

  void Exception::writeLogInfo(const QString& log) {
    qInfo(log.toLocal8Bit());
  }

  void Exception::showMessage(QWidget *parent, MessageLevel msgLve, const QString& msg) {
    switch (msgLve) {
      case INFO:
        QMessageBox::information(parent, mInfo, msg);
        break;
      case WARN:
        QMessageBox::information(parent, mWarn, msg);
        break;
      case ERROR:
        QMessageBox::information(parent, mError, msg);
        break;
    }
  }


  /*
   * FileException
   */
  // ctor
  FileException::FileException(/*QObject *parent*/)
  /*:Exception(parent)*/ {}

  const QString FileException::what() const {
    return QObject::tr("Something wrong with file!");
  }

  /*
   * CharactersEncodingFormatErr
   */
  const QString CharactersEncodingFormatErr::what() const {
   return QObject::tr("Characters encoding format error!");
  }

  /*
   * FileExceptionOpenErr
   */
  // ctor
  FileExceptionOpenErr::FileExceptionOpenErr(/*QObject *parent*/)
  /*:FileException(parent)*/ {}

  const QString FileExceptionOpenErr::what() const {
    return QObject::tr("Fail to open file!");
  }

  /*
   * FileExceptionNotExist
   */
  const QString FileExceptionNotExist::what() const {
    return QObject::tr("File does not exist!");
  }

  /*
   * ParserException
   */
  const QString ParserException::what() const {
    return QObject::tr("Wrong with parsing!");
  }

  /*
   * ProtocolException
   */
  const QString ProtocolException::what() const {
    return QObject::tr("Protocol error!");
  }

  /*
   * LanguageException
   */
  const QString LanguageException::what() const {
    return QObject::tr("Language error!");
  }

  /*
   * ParserExceptionXml
   */
  const QString ParserExceptionXml::what() const {
    return QObject::tr("Wrong with parsing xml file!");
  }

  /*
   * IncorrectVersion
   */
  const QString IncorrectVersion::what() const {
   return QObject::tr("The XML version is incorrect!");
  }

  /*
   * LabelIsIncorrect
   */
  const QString LabelIsIncorrect::what() const {
   return QObject::tr("The label of the element is incorrect!");
  }

  /*
   * ParserExceptionGTXLQX
   */
  const QString ParserExceptionGTXLQX::what() const {
    return QObject::tr("Wrong with parsing GTXLQX system xml file!");
  }

  /*
   * PrematureEndOfDocumentError
   */
  const QString PrematureEndOfDocumentError::what() const {
    return QObject::tr("The input stream ended before a well-formed XML document was parsed!");
  }

 /*
  * NotWellFormedError
  */
  const QString NotWellFormedError::what() const {
    return QObject::tr("The parser internally raised an error due to the read XML not being well-formed!");
  }

  /*
   * UpcastProtocolConversion
   */
  const QString UpcastProtocolConversion::what() const {
    return QObject::tr("Sub-protocol failed to convert to parent protocol!");
  }

  /*
   * DowncastProtocolConversion
   */
  const QString DowncastProtocolConversion::what() const {
    return QObject::tr("Parent protocol failed to convert to sub-protocol!");
  }

  /*
   * LoadTranslationFile
   */
  const QString LoadTranslationFile::what() const {
    return QObject::tr("failed load translation file!");
  }

  /*
   * delTranslationFile
   */
  const QString delTranslationFile::what() const {
    return QObject::tr("failed delete translation file!");
  }

  /*
   * addTranslationFile
   */
  const QString addTranslationFile::what() const {
    return QObject::tr("failed add translation file!");
  }

}
