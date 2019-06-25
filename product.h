/*******************************************************************************
* Description: 产品类(工厂方法模式)
* Author: Niu yi qun
* Creation date: 2019/6/11
* Last modified person: Niu yi qun
* Last modified date: 2019/6/17
******************************************************************************/
#ifndef PRODUCT_H
#define PRODUCT_H

#include "protocol.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QSharedPointer>
#include <QTranslator>
#include <QLabel>

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
  class Product {
  public:
    Product();
    virtual ~Product() = default;
  };

  /*
   * 基类 解析器类
   */
  class Parser : public Product {
  public:
    Parser();
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
  class Language : public Product{
  protected:
    // 语言的枚举类型
    enum LanTypes {
      INVALID = 0x50,
      CHINESE,
    };
  public:
    Language();
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
    // 每种语言的计数器(加载语言加1，卸载语言减1)
    static char mCnCount;
  };

  /*
   * 基类 主窗口类
   */
  class MainWindow : public Product {
  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;
  public:
    QSharedPointer<QMainWindow> mMainWindow;
  protected:
    QSharedPointer<Ui::MainWindow> mUi;
    // 主窗口中央小部件(此处不能用智能指针，因为QMainWindow获取小部件指针的所有权并在适当的时候删除它)
    QWidget* mCentralWidget;
  };

  /*
   * 基类 标签类
   */
  class Label : public Product, public QLabel {
  public:
    Label(QWidget* parent = nullptr);
    ~Label() = default;
    // 设置主窗口
    virtual void setMainWindow(QSharedPointer<MainWindow> mainWindow);
    // 设置小部件鼠标跟踪
    virtual void setMousetrackingWidget();
    // 设置小部件最小尺寸
    virtual void setMinSizeWidget();
    // 设置小部件默认图片
    virtual void setDefPictureWidget();
    // 设置鼠标移动进入小部件时的图片
    virtual void setMouseInWidgetPicture();
  protected:
    // 设置图片
    void setPicture(int width, int height, const QString& fileName);
  protected:
    QSharedPointer<const Protocol> mProtocol;
    QSharedPointer<MainWindow> mMainWindow;
  };

  /*
   * 基类 小部件类
   */
  class Widget : public Product, public QWidget {
  public:
    Widget(QWidget* parent = nullptr);
    ~Widget() = default;
    // 设置自定义界面
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
  };

  /*
   * 子类 中文(简体)
   */
  class SimplifiedChinese : public Language {
  public:
    SimplifiedChinese();
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
    XMLParser();
    ~XMLParser() = default;
    QSharedPointer<const Protocol> getProtocol() const Q_DECL_OVERRIDE;
    void parse(const QString& filePath) Q_DECL_OVERRIDE;
  protected:
    // QXmlStreamReader 令牌类型处理函数
    virtual void noToken(const QXmlStreamReader& reader);
    virtual void invalid(const QXmlStreamReader& reader);
    virtual void startDocument(const QXmlStreamReader& reader);
    virtual void endDocument(const QXmlStreamReader& reader);
    virtual void startElement(const QXmlStreamReader& reader);
    virtual void endElement(const QXmlStreamReader& reader);
    virtual void characters(const QXmlStreamReader& reader);
    virtual void comment(const QXmlStreamReader& reader);
    virtual void dtd(const QXmlStreamReader& reader);
    virtual void entityReference(const QXmlStreamReader& reader);
    virtual void processingInstruction(const QXmlStreamReader& reader);
    // QXmlStreamReader 错误处理函数
    virtual void noError(const QXmlStreamReader& reader);
    virtual void customError(const QXmlStreamReader& reader);
    virtual void notWellFormedError(const QXmlStreamReader& reader);
    virtual void prematureEndofDocumentError(const QXmlStreamReader& reader);
    virtual void unexpectedElementError(const QXmlStreamReader& reader);
  protected:
    QSharedPointer<Protocol> mProtocol;
  };

  /*
   * 子类 高铁线路缺陷UI系统XML解析器类
   */
  class GTXLQX_XMLParser : public XMLParser {
  private:
    typedef enum Label_Type {
      INVALID = 0x30,
      UNIVERSAL,
      MAINWINDOW,
      TITLE,
      TITLELABEL,
      DOORFACE,
      MENUS,
      MENU,
      SUBMENU,
    } Label_Type;
  public:
    GTXLQX_XMLParser();
    ~GTXLQX_XMLParser() = default;
  protected:
    // 函数的覆盖
    // 令牌类型处理函数
    //void startDocument(const QXmlStreamReader& reader);
    void startElement(const QXmlStreamReader& reader) Q_DECL_OVERRIDE;

    // 错误处理函数
    //void notWellFormedError(const QXmlStreamReader& reader);
    //void prematureEndofDocumentError(const QXmlStreamReader& reader);
  private:
    // 读取模块中元素的内容
    void readUniversalModule(const QXmlStreamReader& reader);
    void readMainWindowModule(const QXmlStreamReader& reader);
    void readTitleModule(const QXmlStreamReader& reader);
    void readTitleLabelModule(const QXmlStreamReader& reader);
    void readDoorfaceModule(const QXmlStreamReader& reader);
    void readMenusModule(const QXmlStreamReader& reader);
    void readMenu(const QXmlStreamReader& reader);
    void readSubmenu(const QXmlStreamReader& reader);
    // 转换函数 元素标签的名称转换为元素标签的枚举类型
    Label_Type labelNameTolabelType(const QString& name);
  private:
    // 模块的名称
    const QLatin1String mUniversalModule, mMainWindowModule, mTitleModule
    ,mTitleLabelModule, mDoorfaceModule, mMenusModule
    ,mMenu, mSubmenu;
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
    ConfigParser();
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

  /*
   * 子类 高铁线路缺陷主窗口类
   */
  class GTXLQX_MainWindow : public MainWindow {
  public:
    GTXLQX_MainWindow(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~GTXLQX_MainWindow();
  protected:
    // 自动创建主窗口
    void autoCreateMainWindow();
    // 设置主窗口标志
    void setMainWindowFlags();
    // 设置菜单栏
    void setMenubar();
    // 设置状态栏
    void setStatusbar();
    // 设置主窗口最小尺寸
    void setMainWinMinSize();
    // 设置中央小部件
    void setCentralWidget();
    // 设置中央小部件布局
    void setLayoutCentralWidget();
    // 添加标题栏
    void addTitlebar();
    // 添加门脸
    void addDoorface();
    // 添加菜单栏
    void addMenubar();
    // 添加内容窗口
    void addContentWindow();
  protected:
    QSharedPointer<const Protocol> mProtocol;
  };

  /*
   * 子类 最小化窗口标签类
   */
  class MinWindow_Label : public Label {
  public:
    MinWindow_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~MinWindow_Label() = default;
    void setMousetrackingWidget() Q_DECL_OVERRIDE;
    void setMinSizeWidget() Q_DECL_OVERRIDE;
    void setDefPictureWidget() Q_DECL_OVERRIDE;
    void setMouseInWidgetPicture() Q_DECL_OVERRIDE;
  protected:
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
  private:
    // 设置默认图片
  };

  /*
   * 子类 最大化窗口标签类
   */
  class MaxWindow_Label : public Label {
  public:
    MaxWindow_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~MaxWindow_Label() = default;
    void setMousetrackingWidget() Q_DECL_OVERRIDE;
    void setMinSizeWidget() Q_DECL_OVERRIDE;
    void setDefPictureWidget() Q_DECL_OVERRIDE;
    void setMouseInWidgetPicture() Q_DECL_OVERRIDE;
  protected:
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
  private:
    // 设置窗口正常大小显示时的默认图片
    void setNormalWindowDefPicture();
    // 设置窗口正常大小显示时鼠标移动到小部件中显示的图片
    void setNormalWindowMouseInWidgetPicture();
    // 设置窗口最大化显示时的默认图片
    void setMaxWindowDefPicture();
    // 设置窗口最大化显示时鼠标移动到小部件中显示的图片
    void setMaxWindowMouseInWidgetPicture();
  };

  /*
   * 子类 关闭窗口标签类
   */
  class ShutdownWindow_Label : public Label {
  public:
    ShutdownWindow_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~ShutdownWindow_Label() = default;
    void setMousetrackingWidget() Q_DECL_OVERRIDE;
    void setMinSizeWidget() Q_DECL_OVERRIDE;
    void setDefPictureWidget() Q_DECL_OVERRIDE;
    void setMouseInWidgetPicture() Q_DECL_OVERRIDE;
  protected:
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;

  };

  /*
   * 子类 标题栏标签类
   */
  class Titlebar_Label : public Label {
  public:
    Titlebar_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~Titlebar_Label() = default;
    void setMinSizeWidget() Q_DECL_OVERRIDE;
    void setDefPictureWidget() Q_DECL_OVERRIDE;
  protected:
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;

  };

  /*
   * 子类 标题栏类
   */
  class Titlebar : public Widget {
  public:
    Titlebar(QWidget* parent = nullptr);
    ~Titlebar() = default;
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  };

}

#endif // PARSER_H
