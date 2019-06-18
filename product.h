/*******************************************************************************
* Description: 产品类(工厂方法模式)
* Author: Niu yi qun
* Creation date: 2019/6/11
* Last modified date: 2019/6/17
******************************************************************************/
#ifndef PRODUCT_H
#define PRODUCT_H

#include "protocol.h"

#include <QObject>
#include <QSharedPointer>
#include <QTranslator>

QT_BEGIN_NAMESPACE
class QFile;
class QXmlStreamReader;
QT_END_NAMESPACE

namespace Jinhui {
  // Forward declaration
  // do nothing

  /*******************************************************************************
   * 基类
   ******************************************************************************/
  /*
   * 基类 产品类
   */
  class Product : public QObject {
  public:
    Product(QObject *parent = nullptr);
    ~Product() = default;
  };

  /*
   * 基类 解析器类
   */
  class Parser : public Product {
  public:
    Parser(QObject *parent = nullptr);
    ~Parser() = default;
    virtual QSharedPointer<const Protocol> getProtocol() const;
    virtual void parse(const QString& filePath);
  protected:
    // Open file
    void openFile(QFile& file);

  };

  /*
   * 基类 语言类
   */
  class Language : public QObject {
  protected:
    // 语言的枚举类型
    enum LanTypes {
      INVALID = 0x50,
      CHINESE,
    };
  public:
    Language(QObject* parent = nullptr);
    ~Language() = default;
  protected:
    // 加载翻译文件
    void loadTranslationFiles();
    // 转换函数 语言的名称字符串转换为语言的枚举类型
    LanTypes lanNameStrToLanNameEnum(const QString& name);
    // 转换函数 语言的枚举类型转换为语言的名称字符串
    const QString lanNameEnumToLanNameStr(LanTypes lanType) const;
  protected:
    // variable
    QTranslator mTranslator;
    // 所有的语言
    QHash<QString, ConfigPro::Lan> mLanguages;
    // 当前语言
    LanTypes mCurrentLan;
    const QLatin1String mChinese;
    // 根目录路径
    QString mRootDirPath;
    // 翻译文件目录路径
    QString mTraDirPath;
  };

  /*
   * 子类 中文(简体)
   */
  class SimplifiedChinese : public Language {
  public:
    SimplifiedChinese(QObject* parent = nullptr);
    ~SimplifiedChinese() = default;
  };

  /*******************************************************************************
   * 子类
   ******************************************************************************/
  /*
   * 子类 XML解析器类
   */
  class XMLParser : public Parser {
  public:
    XMLParser(QObject *parent = nullptr);
    ~XMLParser() = default;
    QSharedPointer<const Protocol> getProtocol() const Q_DECL_OVERRIDE;
    void parse(const QString& filePath) Q_DECL_OVERRIDE;
  protected:
    // QXmlStreamReader 令牌类型处理函数
    void noToken(const QXmlStreamReader& reader);
    void invalid(const QXmlStreamReader& reader);
    void startDocument(const QXmlStreamReader& reader);
    void endDocument(const QXmlStreamReader& reader);
    void startElement(const QXmlStreamReader& reader);
    void endElement(const QXmlStreamReader& reader);
    void characters(const QXmlStreamReader& reader);
    void comment(const QXmlStreamReader& reader);
    void dtd(const QXmlStreamReader& reader);
    void entityReference(const QXmlStreamReader& reader);
    void processingInstruction(const QXmlStreamReader& reader);
    // QXmlStreamReader 错误处理函数
    void noError(const QXmlStreamReader& reader);
    void customError(const QXmlStreamReader& reader);
    void notWellFormedError(const QXmlStreamReader& reader);
    void prematureEndofDocumentError(const QXmlStreamReader& reader);
    void unexpectedElementError(const QXmlStreamReader& reader);
  protected:
    QSharedPointer<Protocol> mProtocol;
  };

  /*
   * 子类 高铁线路缺陷UI系统XML解析器类
   */
  class XMLParserGTXLQX : public XMLParser {
  private:
    typedef enum Label_Type {
      INVALID = 0x30,
      UNIVERSAL,
      TITLE,
      DOORFACE,
      MENUS,
    } Label_Type;
  public:
    XMLParserGTXLQX(QObject *parent = nullptr);
    ~XMLParserGTXLQX() = default;
  protected:
    // 函数的覆盖
    // 令牌类型处理函数
    //void startDocument(const QXmlStreamReader& reader);
    void startElement(const QXmlStreamReader& reader);

    // 错误处理函数
    //void notWellFormedError(const QXmlStreamReader& reader);
    //void prematureEndofDocumentError(const QXmlStreamReader& reader);
  private:
    // 读取模块中元素的内容
    void readUniversalModule(const QXmlStreamReader& reader);
    void readTitleModule(const QXmlStreamReader& reader);
    void readDoorfaceModule(const QXmlStreamReader& reader);
    void readMenusModule(const QXmlStreamReader& reader);
    // 转换函数 元素标签的名称转换为元素标签的枚举类型
    Label_Type labelNameTolabelType(const QString& name);
  private:
    // 模块的名称
    const QLatin1String mUniversalModule, mTitleModule, mDoorfaceModule, mMenusModule;
    // 菜单的数量
    const int mMenusCount;
  };

  /*
   * 子类 配置文件解析类
   */
  class ConfigParser : public XMLParser {
  private:
    typedef enum Label_Type {
      INVALID = 0x40,
      UNIVERSAL,
      LANGUAGES,
    } Label_Type;
  public:
    ConfigParser(QObject* parent = nullptr);
    ~ConfigParser() = default;
  protected:
    // 函数的覆盖
    // 令牌类型处理函数
    void startElement(const QXmlStreamReader& reader);

  private:
    // 读取模块中元素的内容
    void readUniversalModule(const QXmlStreamReader& reader);
    void readLanguagesModule(const QXmlStreamReader& reader);
    // 转换函数 元素标签的名称转换为元素标签的枚举类型
    Label_Type labelNameTolabelType(const QString& name);


  private:
    // 模块的名称
    const QLatin1String mUniversalModule, mLanguagesModule;
    // 语言的数量
    const int mLansCount;
  };

}

#endif // PARSER_H
