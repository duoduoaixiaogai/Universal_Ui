#include "include/product.h"
#include "include/exception.h"

#include <QXmlStreamReader>
#include <QFile>

namespace Jinhui {
  /*
   * Product
   */
  // cotr
  Product::Product() {}

  void Product::setProductName(QString name) {
    mName = name;
  }

  QString Product::productName() const {
    return mName;
  }

  /*
   * Parser
   */
  Parser::Parser() {}

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
  XMLParser::XMLParser()
    : Parser() {
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
   * GTXLQX_XMLParser
   */
  // ctor
  GTXLQX_XMLParser::GTXLQX_XMLParser()
    :XMLParser()
    ,mUniversalModule("Universal_Module")
    ,mMainWindowModule("MainWindow_Module")
    ,mTitleModule("Title_Module")
    ,mTitleLabelModule("TitleLabel_Module")
    ,mDoorfaceModule("Doorface_Module")
    ,mMenusModule("Menus_Module")
    ,mMenu("Menu")
    ,mSubmenu("Submenu")
    ,mLayout("Layout")
    ,mMenusCount(3) {
    mProtocol = QSharedPointer<Protocol>(new GTXLQXPro);
  }

  // protected
  // handle token type function
  //void GTXLQX_XMLParser::startDocument(const QXmlStreamReader& reader) {
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

  void GTXLQX_XMLParser::startElement(const QXmlStreamReader& reader) {
    QString startLabel = reader.name().toString();

    Label_Type type = labelNameTolabelType(startLabel);
    switch (type) {
      case INVALID:
        // do nothing
        break;
      case UNIVERSAL:
        readUniversalModule(reader);
        break;
      case MAINWINDOW:
        readMainWindowModule(reader);
        break;
      case TITLE:
        readTitleModule(reader);
        break;
      case TITLELABEL:
        readTitleLabelModule(reader);
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
      case LAYOUT:
        readLayout(reader);
        break;
    }
  }

  // handle error function
  //void GTXLQX_XMLParser::notWellFormedError(const QXmlStreamReader& reader) {
  //  Q_UNUSED(reader)
  //  try {
  //    throw NotWellFormedError();
  //  } catch (ParserExceptionXml& ex) {
  //    const QString msg = ex.what();
  //    ex.writeLogError(msg);
  //    ex.showMessage(nullptr, MessageLevel::ERROR, msg);
  //  }
  //}

  //void GTXLQX_XMLParser::prematureEndofDocumentError(const QXmlStreamReader& reader) {
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
  void GTXLQX_XMLParser::readUniversalModule(const QXmlStreamReader& reader) {
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

  void GTXLQX_XMLParser::readMainWindowModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mMainWindowModule == reader.name());

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
      if (QLatin1String("Rimless") == name) {
        protocol->rimless = xml.readElementText();
      } else if (QLatin1String("Menubar") == name) {
        protocol->menubar = xml.readElementText();
      } else if (QLatin1String("Statusbar") == name) {
        protocol->statusbar = xml.readElementText();
      } else if (QLatin1String("MinWidth") == name) {
        protocol->mainMinWidth = xml.readElementText();
      } else if (QLatin1String("MinHeight") == name) {
        protocol->mainMinHeight = xml.readElementText();
      } else if (QLatin1String("Background_Color") == name) {
        protocol->mainBackgroundCol = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void GTXLQX_XMLParser::readTitleModule(const QXmlStreamReader& reader) {
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
        protocol->titlePicName = xml.readElementText();
      } else if (QLatin1String("Min_WidgetWidth") == name) {
        protocol->titleMinWidgetWidth = xml.readElementText();
      } else if (QLatin1String("Min_WidgetHeight") == name) {
        protocol->titleMinWidgetHeight = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void GTXLQX_XMLParser::readTitleLabelModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mTitleLabelModule == reader.name());

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
      if (QLatin1String("MouseTracking") == name) {
        protocol->mousetracking = xml.readElementText();
      } else if (QLatin1String("Min_PictureDefault") == name) { // 最小化
        protocol->minPicDefault = xml.readElementText();
      } else if (QLatin1String("Min_PictureMoved") == name) {
        protocol->minPicMoved = xml.readElementText();
      } else if (QLatin1String("Min_WidgetMinWidth") == name) {
        protocol->minWidgetMinWidth = xml.readElementText();
      } else if (QLatin1String("Min_WidgetMinHeight") == name) {
        protocol->minWidgetMinHeight = xml.readElementText();
      } else if (QLatin1String("Normal_PictureDefault") == name) { // 最大化 窗口正常显示时
        protocol->normalPicDefault = xml.readElementText();
      } else if (QLatin1String("Normal_PictureMoved") == name) {
        protocol->normalPicMoved = xml.readElementText();
      } else if (QLatin1String("Normal_WidgetMinWidth") == name) {
        protocol->normalWidgetMinWidth = xml.readElementText();
      } else if (QLatin1String("Normal_WidgetMinHeight") == name) {
        protocol->normalWidgetMinHeight = xml.readElementText();
      } else if (QLatin1String("Max_PictureDefault") == name) { // 最大化 窗口最大化显示时
        protocol->maxPicDefault = xml.readElementText();
      } else if (QLatin1String("Max_PictureMoved") == name) {
        protocol->maxPicMoved = xml.readElementText();
      } else if (QLatin1String("Max_WidgetMinWidth") == name) {
        protocol->maxWidgetMinWidth = xml.readElementText();
      } else if (QLatin1String("Max_WidgetMinHeight") == name) {
        protocol->maxWidgetMinHeight = xml.readElementText();
      } else if (QLatin1String("Shut_PictureDefault") == name) { // 关闭
        protocol->shutPicDefault = xml.readElementText();
      } else if (QLatin1String("Shut_PictureMoved") == name) {
        protocol->shutPicMoved = xml.readElementText();
      } else if (QLatin1String("Shut_WidgetMinWidth") == name) {
        protocol->shutWidgetMinWidth = xml.readElementText();
      } else if (QLatin1String("Shut_WidgetMinHeight") == name) {
        protocol->shutWidgetMinHeight = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void GTXLQX_XMLParser::readDoorfaceModule(const QXmlStreamReader& reader) {
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
        protocol->doorPicName = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        protocol->doorPicWidth = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        protocol->doorPicHeight = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void GTXLQX_XMLParser::readMenusModule(const QXmlStreamReader& reader) {
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
    //      menu.menuPicName = xml.readElementText();
    //    } else if (QLatin1String("Picture_Width") == name) {
    //      menu.menuPicWidth = xml.readElementText();
    //    } else if (QLatin1String("Picture_Height") == name) {
    //      menu.menuPicHeight = xml.readElementText();
    //      // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
    //      break;
    //    }
    //  } // 父菜单

    //  // 子菜单
    //  while (xml.readNextStartElement()) {
    //    QStringRef name = reader.name();
    //    if (QLatin1String("Picture_name") == name) {
    //      menu.subPicName = xml.readElementText();
    //    } else if (QLatin1String("Picture_Width") == name) {
    //      menu.subPicWidth = xml.readElementText();
    //    } else if (QLatin1String("Picture_Height") == name) {
    //      menu.subPicHeight = xml.readElementText();
    //      // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
    //      break;
    //    }
    //  } // 子菜单
    //  protocol->menus.append(menu);
    //} // 菜单
  }

  void GTXLQX_XMLParser::readMenu(const QXmlStreamReader& reader) {
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
      if (QLatin1String("Object_Name") == name) {
        menu.objectName = xml.readElementText();
      } else if (QLatin1String("Picture_name") == name) {
        menu.menuPicName = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        menu.menuPicWidth = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        menu.menuPicHeight = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
    protocol->menus.append(menu);
  }

  void GTXLQX_XMLParser::readSubmenu(const QXmlStreamReader& reader) {
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
      /*
      if (QLatin1String("Picture_name") == name) {
        menu.subPicName = xml.readElementText();
      } else if (QLatin1String("Picture_Width") == name) {
        menu.subPicWidth = xml.readElementText();
      } else if (QLatin1String("Picture_Height") == name) {
        menu.subPicHeight = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
      */
      if (QLatin1String("End") == name) {
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      } else if (QLatin1String("Object_Name") == name) {
        menu.subMenu.objectName = xml.readElementText();
      } else if (QLatin1String("Hide") == name) {
        menu.subMenu.hide = xml.readElementText();
      } else {
        GTXLQXPro::MenuItem menuItem;
        menuItem.objectName = reader.attributes().value(QLatin1String("objectName")).toString();
        menuItem.itemClickedPicture = reader.attributes().value(QLatin1String("clickedPicture")).toString();
        menuItem.itemDefaultPicture = xml.readElementText();
        menu.subMenu.itemsName.append(menuItem);
      }
    }
  }

  void GTXLQX_XMLParser::readLayout(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mLayout == reader.name());

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
      if (QLatin1String("Separator") == name) {
        protocol->separator = xml.readElementText();
      } else if (QLatin1String("MainWindow_ContentsMargins") == name) {
        protocol->mainwindowContentsMargins = xml.readElementText();
      } else if (QLatin1String("MainWindow_Spacing") == name) {
        protocol->mainwindowSpacing = xml.readElementText();
      } else if (QLatin1String("Titlebar_ContentsMargins") == name) {
        protocol->titlebarContentsMargins = xml.readElementText();
      } else if (QLatin1String("Titlebar_Spacing") == name) {
        protocol->titlebarSpacing = xml.readElementText();
      } else if (QLatin1String("Titlebar_Stretch") == name) {
        protocol->titlebarStretch = xml.readElementText();
      } else if (QLatin1String("Doorface_ContentsMargins") == name) {
        protocol->doorfaceContentsMargins = xml.readElementText();
      } else if (QLatin1String("Doorface_Spacing") == name) {
        protocol->doorfaceSpacing = xml.readElementText();
      } else if (QLatin1String("Doorface_Stretch") == name) {
        protocol->doorfaceStretch = xml.readElementText();
      } else if (QLatin1String("MenuContent_ContentsMargins") == name) {
        protocol->menuContentsMargins = xml.readElementText();
      } else if (QLatin1String("MenuContent_Spacing") == name) {
        protocol->menuContentSpacing = xml.readElementText();
      } else if (QLatin1String("MenuContent_Stretch") == name) {
        protocol->menuContentStretch = xml.readElementText();
      } else if (QLatin1String("Menubar_Stretch") == name) {
        protocol->menubarStretch = xml.readElementText();
      } else if (QLatin1String("Menubar_Alignment") == name) {
        protocol->menubarAlignment = xml.readElementText();
      } else if (QLatin1String("Content_Stretch") == name) {
        protocol->contentStretch = xml.readElementText();
      } else if (QLatin1String("Content_Alignment") == name) {
        protocol->contentAlignment = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  // private
  // label name to label type
  GTXLQX_XMLParser::Label_Type GTXLQX_XMLParser::labelNameTolabelType(const QString& name) {
    Label_Type labelType = INVALID;

    if (mUniversalModule == name) {
      labelType = UNIVERSAL;
    } else if (mMainWindowModule == name) {
      labelType = MAINWINDOW;
    } else if (mTitleModule == name) {
      labelType = TITLE;
    } else if (mTitleLabelModule == name) {
      labelType = TITLELABEL;
    } else if (mDoorfaceModule == name) {
      labelType = DOORFACE;
    } else if (mMenusModule == name) {
      labelType = MENUS;
    } else if (mMenu == name) {
      labelType = MENU;
    } else if (mSubmenu == name) {
      labelType = SUBMENU;
    } else if (mLayout == name) {
      labelType = LAYOUT;
    }else {
      labelType = INVALID;
    }

    return labelType;
  }

  /*
   * ConfigParser
   */
  // ctor
  ConfigParser::ConfigParser()
    :XMLParser()
    ,mUniversalModule("Universal_Module")
    ,mLanguagesModule("Languages_Module")
    ,mDatabaseModule("Database_Module")
    ,mQssModule("Qss_Module")
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
      case DATABASE:
        readDatabaseModule(reader);
        break;
      case QSS:
        readQssModule(reader);
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

  void ConfigParser::readDatabaseModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mDatabaseModule == reader.name());

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
      QStringRef name = reader.name();
      if (QLatin1String("Host_Name") == name) {
        protocol->hostName = xml.readElementText();
      } else if (QLatin1String("Database_Name") == name) {
        protocol->databaseName = xml.readElementText();
      } else if (QLatin1String("Table_Name") == name) {
        protocol->tableName = xml.readElementText();
      } else if (QLatin1String("User_Name") == name) {
        protocol->userName = xml.readElementText();
      } else if (QLatin1String("User_Password") == name) {
        protocol->userPassword = xml.readElementText();
        // 人工干预强制退出循环 模块元素中的子元素的内容已经获取完毕
        break;
      }
    }
  }

  void ConfigParser::readQssModule(const QXmlStreamReader& reader) {
    Q_ASSERT(reader.isStartElement() && mQssModule == reader.name());

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
      QStringRef name = reader.name();
      if (QLatin1String("Qss_FileName") == name) {
        protocol->qssFileName = xml.readElementText();
        break;
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
    } else if (mDatabaseModule == name) {
      labelType = DATABASE;
    } else if (mQssModule == name) {
      labelType = QSS;
    }

    return labelType;
  }

}
