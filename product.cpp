#include "product.h"
#include "exception.h"

#include <QXmlStreamReader>
#include <QFile>

namespace Jinhui {
  /*
   * Product
   */
  Product::Product(QObject *parent) : QObject(parent) {}

  /*
   * Parser
   */
  Parser::Parser(QObject *parent) : Product(parent) {}

  QSharedPointer<const Protocol> Parser::getProtocol() const {
    return QSharedPointer<const Protocol>();
  }

  void Parser::parse(const QString& filePath) {
    Q_UNUSED(filePath)
  }

  // protected
  void Parser::openFile(QFile &file) {
    try {
      if (!file.exists()) {
        throw FileExceptionNotExist();
      }
      if (!file.open(QIODevice::ReadOnly)) {
        throw FileExceptionOpenErr();
      }
    } catch (FileException& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
    }
  }

  /*
   * XMLParser
   */
  XMLParser::XMLParser(QObject* parent) : Parser(parent) {
    mProtocol = QSharedPointer<Protocol>(new Protocol);
  }

  QSharedPointer<const Protocol> XMLParser::getProtocol() const {
    return mProtocol;
  }

  void XMLParser::parse(const QString& filePath) {
    QFile file(filePath);
    openFile(file);

    QXmlStreamReader xml(&file);
    while (!xml.atEnd()) {
      QXmlStreamReader::TokenType type = xml.readNext();
      switch (type) {
        case QXmlStreamReader::NoToken:
          noToken(xml);
          break;
        case QXmlStreamReader::Invalid:
          invalid(xml);
          break;
        case QXmlStreamReader::StartDocument:
          startDocument(xml);
          break;
        case QXmlStreamReader::EndDocument:
          endDocument(xml);
          break;
        case QXmlStreamReader::StartElement:
          startElement(xml);
          break;
        case QXmlStreamReader::EndElement:
          endElement(xml);
          break;
        case QXmlStreamReader::Characters:
          characters(xml);
          break;
        case QXmlStreamReader::Comment:
          comment(xml);
          break;
        case QXmlStreamReader::DTD:
          dtd(xml);
          break;
        case QXmlStreamReader::EntityReference:
          entityReference(xml);
          break;
        case QXmlStreamReader::ProcessingInstruction:
          processingInstruction(xml);
          break;
      }
    }
    if (xml.hasError()) {
      switch (xml.error()) {
        case QXmlStreamReader::NoError:
          noError(xml);
          break;
        case QXmlStreamReader::CustomError:
          customError(xml);
          break;
        case QXmlStreamReader::NotWellFormedError:
          notWellFormedError(xml);
          break;
        case QXmlStreamReader::PrematureEndOfDocumentError:
          prematureEndofDocumentError(xml);
          break;
        case QXmlStreamReader::UnexpectedElementError:
          unexpectedElementError(xml);
          break;
      }
    }

    file.close();
  }

  void XMLParser::noToken(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::invalid(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::startDocument(const QXmlStreamReader& reader) {
    try {
      if (QLatin1String("1.0") != reader.documentVersion().toString()) {
        throw IncorrectVersion();
      }
      if (QLatin1String("UTF-8") != reader.documentEncoding().toString()) {
        throw CharactersEncodingFormatErr();
      }
    } catch (ParserExceptionXml& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }
  }

  void XMLParser::endDocument(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::startElement(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::endElement(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::characters(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::comment(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::dtd(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::entityReference(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::processingInstruction(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::noError(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::customError(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  void XMLParser::notWellFormedError(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
    try {
      throw NotWellFormedError();
    } catch (ParserExceptionXml& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
    }
  }

  void XMLParser::prematureEndofDocumentError(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
    try {
      throw PrematureEndOfDocumentError();
    } catch (ParserExceptionXml& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
    }
  }

  void XMLParser::unexpectedElementError(const QXmlStreamReader& reader) {
    Q_UNUSED(reader)
  }

  /*
   * XMLParserGTXLQX
   */
  // ctor
  XMLParserGTXLQX::XMLParserGTXLQX(QObject* parent)
    :XMLParser(parent)
    ,mUniversalModule("Universal_Module")
    ,mTitleModule("Title_Module")
    ,mDoorfaceModule("Doorface_Module")
    ,mMenusModule("Menus_Module")
    ,mMenu("Menu")
    ,mSubmenu("Submenu")
    ,mMenusCount(3) {
    mProtocol = QSharedPointer<Protocol>(new GTXLQXPro);
  }

  // protected
  // handle token type function
  //void XMLParserGTXLQX::startDocument(const QXmlStreamReader& reader) {
  //  try {
  //    if (QLatin1String("1.0") != reader.documentVersion().toString()) {
  //      throw IncorrectVersion();
  //    }
  //    if (QLatin1String("UTF-8") != reader.documentEncoding().toString()) {
  //      throw CharactersEncodingFormatErr();
  //    }
  //  } catch (ParserExceptionXml& ex) {
  //    const QString msg = ex.what();
  //    ex.writeLogError(msg);
  //    ex.showMessage(nullptr, MessageLevel::ERROR, msg);
  //    return;
  //  }
  //}

  void XMLParserGTXLQX::startElement(const QXmlStreamReader& reader) {
    QString startLabel = reader.name().toString();

    Label_Type type = labelNameTolabelType(startLabel);
    switch (type) {
      case INVALID:
        // do nothing
        break;
      case UNIVERSAL:
        readUniversalModule(reader);
        break;
      case TITLE:
        readTitleModule(reader);
        break;
      case DOORFACE:
        readDoorfaceModule(reader);
        break;
      case MENUS:
        readMenusModule(reader);
        break;
      case MENU:
        readMenu(reader);
        break;
      case SUBMENU:
        readSubmenu(reader);
        break;
    }
  }

  // handle error function
  //void XMLParserGTXLQX::notWellFormedError(const QXmlStreamReader& reader) {
  //  Q_UNUSED(reader)
  //  try {
  //    throw NotWellFormedError();
  //  } catch (ParserExceptionXml& ex) {
  //    const QString msg = ex.what();
  //    ex.writeLogError(msg);
  //    ex.showMessage(nullptr, MessageLevel::ERROR, msg);
  //  }
  //}

  //void XMLParserGTXLQX::prematureEndofDocumentError(const QXmlStreamReader& reader) {
  //  Q_UNUSED(reader)
  //  try {
  //    throw PrematureEndOfDocumentError();
  //  } catch (ParserExceptionXml& ex) {
  //    const QString msg = ex.what();
  //    ex.writeLogWarn(msg);
  //    ex.showMessage(nullptr, MessageLevel::WARN, msg);
  //  }
  //}

  // private
  // read the contents of the elements in the module
  void XMLParserGTXLQX::readUniversalModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mUniversalModule == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    // qSharedPointerDynamicCast必须保证基类为多态类型,协议类暂时不打算写成多态类型。
    // qSharedPointerCast 也可以进行向下转型,并且避免运行时检查的开销,但必须保证转换为子类时才是安全的。
    QSharedPointer<GTXLQXPro> protocol = qSharedPointerCast<GTXLQXPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = GTXLQX;
    while (xml.readNextStartElement()) {
      QStringRef name = reader.name();
      if (QLatin1String("Root_Dir_Path") == name) {
        protocol->rootDirPath = xml.readElementText();
      } else if (QLatin1String("Pictures_Dir_Path") == name) {
        protocol->picDirPath = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void XMLParserGTXLQX::readTitleModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mTitleModule == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    QSharedPointer<GTXLQXPro> protocol = qSharedPointerCast<GTXLQXPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = GTXLQX;
    while (xml.readNextStartElement()) {
      QStringRef name = reader.name();
      if (QLatin1String("Picture_name") == name) {
        protocol->picNameTitle = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        protocol->picWidthTitle = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        protocol->picHeightTitle = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void XMLParserGTXLQX::readDoorfaceModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mDoorfaceModule == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    QSharedPointer<GTXLQXPro> protocol = qSharedPointerCast<GTXLQXPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = GTXLQX;
    while (xml.readNextStartElement()) {
      QStringRef name = reader.name();
      if (QLatin1String("Picture_name") == name) {
        protocol->picNameDoor = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        protocol->picWidthDoor = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        protocol->picHeightDoor = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void XMLParserGTXLQX::readMenusModule(const QXmlStreamReader& reader) {
    Q_UNUSED(reader);
    //Q_ASSERT(reader.isStartElement() && mMenusModule == reader.name());

    //QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    //QSharedPointer<GTXLQXPro> protocol = qSharedPointerCast<GTXLQXPro, Protocol>(mProtocol);
    //try {
    //  if (!protocol) {
    //    throw DowncastProtocolConversion();
    //  }
    //} catch (ProtocolException& ex) {
    //  const QString msg = ex.what();
    //  ex.writeLogError(msg);
    //  ex.showMessage(nullptr, MessageLevel::ERROR, msg);
    //  return;
    //}

    //protocol->proType = GTXLQX;
    //// 菜单
    //for (int i = 0; i < mMenusCount; ++i) {
    //  GTXLQXPro::Menu menu;
    //  // 父菜单
    //  while (xml.readNextStartElement()) {
    //    QStringRef name = reader.name();
    //    if (QLatin1String("Picture_name") == name) {
    //      menu.picNameMenu = xml.readElementText();
    //    } else if (QLatin1String("Picture_Width") == name) {
    //      menu.picWidthMenu = xml.readElementText();
    //    } else if (QLatin1String("Picture_Height") == name) {
    //      menu.picHeightMenu = xml.readElementText();
    //      // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
    //      break;
    //    }
    //  } // 父菜单

    //  // 子菜单
    //  while (xml.readNextStartElement()) {
    //    QStringRef name = reader.name();
    //    if (QLatin1String("Picture_name") == name) {
    //      menu.picNameSub = xml.readElementText();
    //    } else if (QLatin1String("Picture_Width") == name) {
    //      menu.picWidthSub = xml.readElementText();
    //    } else if (QLatin1String("Picture_Height") == name) {
    //      menu.picHeightSub = xml.readElementText();
    //      // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
    //      break;
    //    }
    //  } // 子菜单
    //  protocol->menus.append(menu);
    //} // 菜单
  }

  void XMLParserGTXLQX::readMenu(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mMenu == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    QSharedPointer<GTXLQXPro> protocol = qSharedPointerCast<GTXLQXPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = GTXLQX;
    GTXLQXPro::Menu menu;
    while (xml.readNextStartElement()) {
      QStringRef name = reader.name();
      if (QLatin1String("Picture_name") == name) {
        menu.picNameMenu = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        menu.picWidthMenu = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        menu.picHeightMenu = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
    protocol->menus.append(menu);
  }

  void XMLParserGTXLQX::readSubmenu(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mSubmenu == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    QSharedPointer<GTXLQXPro> protocol = qSharedPointerCast<GTXLQXPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = GTXLQX;
    GTXLQXPro::Menu& menu = protocol->menus.last();
    while (xml.readNextStartElement()) {
      QStringRef name = reader.name();
      if (QLatin1String("Picture_name") == name) {
        menu.picNameSub = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        menu.picWidthSub = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        menu.picHeightSub = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  // private
  // label name to label type
  XMLParserGTXLQX::Label_Type XMLParserGTXLQX::labelNameTolabelType(const QString& name) {
    Label_Type labelType = INVALID;

    if (mUniversalModule == name) {
      labelType = UNIVERSAL;
    } else if (mTitleModule == name) {
      labelType = TITLE;
    } else if (mDoorfaceModule == name) {
      labelType = DOORFACE;
    } else if (mMenusModule == name) {
      labelType = MENUS;
    } else if (mMenu == name) {
      labelType = MENU;
    } else if (mSubmenu == name) {
      labelType = SUBMENU;
    } else {
      labelType = INVALID;
    }

    return labelType;
  }

  /*
   * ConfigParser
   */
  // ctor
  ConfigParser::ConfigParser(QObject* parent)
    :XMLParser(parent)
    ,mUniversalModule("Universal_Module")
    ,mLanguagesModule("Languages_Module")
    ,mLansCount(1) {
    mProtocol = QSharedPointer<Protocol>(new ConfigPro);
  }

  // protected
  // handle token type function
  void ConfigParser::startElement(const QXmlStreamReader& reader) {
    QString startLabel = reader.name().toString();

    Label_Type type = labelNameTolabelType(startLabel);
    switch (type) {
      case INVALID:
        // do nothing
        break;
      case UNIVERSAL:
        readUniversalModule(reader);
        break;
      case LANGUAGES:
        readLanguagesModule(reader);
        break;
    }
  }

  // private
  // read the contents of the elements in the module
  void ConfigParser::readUniversalModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mUniversalModule == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    QSharedPointer<ConfigPro> protocol = qSharedPointerCast<ConfigPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = CONFIG;
    while (xml.readNextStartElement()) {
      if (QLatin1String("Root_Dir_Path") == reader.name()) {
        protocol->rootDirPath = xml.readElementText();
      } else if (QLatin1String("Translations_Dir_Path") == reader.name()) {
        protocol->traDirPath = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  // read the contents of the language module
  void ConfigParser::readLanguagesModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mLanguagesModule == reader.name());

    QXmlStreamReader& xml = const_cast<QXmlStreamReader&>(reader);
    QSharedPointer<ConfigPro> protocol = qSharedPointerCast<ConfigPro, Protocol>(mProtocol);
    try {
      if (!protocol) {
        throw DowncastProtocolConversion();
      }
    } catch (ProtocolException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      return;
    }

    protocol->proType = CONFIG;
    // 循环获取子项信息
    for (int i = 0; i < mLansCount; ++i) {
      ConfigPro::Lan lan;
      QString selectLan;
      // 子项 语言信息
      while (xml.readNextStartElement()) {
        if (QLatin1String("Select") == reader.name()) {
          selectLan = xml.readElementText();
          protocol->languages.insert(selectLan, lan);
        } else if (QLatin1String("Prefix") == reader.name()) {
          protocol->languages[selectLan].prefix = xml.readElementText();
        } else if (QLatin1String("Filename") == reader.name()) {
          protocol->languages[selectLan].filename = xml.readElementText();
        } else if (QLatin1String("Suffix") == reader.name()) {
          protocol->languages[selectLan].suffix = xml.readElementText();
          // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
          break;
        }
      }
    }
  }

  // label name to label type
  ConfigParser::Label_Type ConfigParser::labelNameTolabelType(const QString& name) {
    Label_Type labelType = INVALID;

    if (mUniversalModule == name) {
      labelType = UNIVERSAL;
    } else if (mLanguagesModule == name) {
      labelType = LANGUAGES;
    }

    return labelType;
  }

}
