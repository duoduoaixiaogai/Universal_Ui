/*******************************************************************************
* Description: 产品类(工厂方法模式)
* Author: Niu yi qun
* Creation date: 2019/6/11
* Last modified person: Niu yi qun
* Last modified date: 2019/6/17
******************************************************************************/
#ifndef PRODUCT_H
#define PRODUCT_H

#include "global.h"
#include "protocol.h"
#include "ui_mainwindow.h"
#include "qttoopencv.h"

#include <QObject>
#include <QSharedPointer>
#include <QTranslator>
#include <QLabel>
#include <QPushButton>
//#include <QSqlTableModel>
#include <QTableView>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QThread>
#include <QHash>
#include <QPixmap>
#include <QStack>

// ui
#include <QComboBox>
#include <QProgressBar>

// database
#include <QSqlQuery>

// opencv4.1.0
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
class QFile;
class QXmlStreamReader;
class QHBoxLayout;
class QVBoxLayout;
class QStackedWidget;
class QDateTimeEdit;
class QSplitter;
class QSqlTableModel;
QT_END_NAMESPACE

namespace Jinhui {
  // Forward declaration
  class Titlebar;
  class Doorface_Label;
  class Menubar;
  class ContentArea;
  class Menu_Label;
  class SubMenu;
  class MenuItem_Label;
  class Mysql_Connection;
  class Model;
  class GTXLQX_Model;
  class DatabaseTable_View;
  class GraphicsItem;
  class GraphicsPixmapItem;
  class Channel32_Controller;
  class IVMS4200Menu_Widget;
  class IVMS4200TitleBar_Widget;
  class IVMS4200ContentArea_Widget;
  class IVMS4200StatusBar_Widget;
  class IVMS4200MenuBarMainBtn_Widget;
  class IVMS4200MenuBarSeparator_Widget;

  /*******************************************************************************
   * 基类
   ******************************************************************************/
  /*
   * 基类 产品类
   */
  class EXPORT Product {
  public:
    Product();
    virtual ~Product() = default;
    static void doDelete(Product* obj) {
      if (obj) {
        delete obj;
        obj = nullptr;
      }
    }
  };

  /*
   * 基类 解析器类
   */
  class EXPORT Parser : public Product {
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
  class EXPORT Language : public Product{
  protected:
    // 语言的枚举类型
    enum LanTypes {
      INVALID = 0x50,
      CHINESE,
    };
  public:
    Language(QSharedPointer<const Protocol> protocol);
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
    QSharedPointer<const Protocol> mProtocol;
  };

  /*
   * 基类 主窗口类
   */
  // 此类有问题 关闭程序时智能指针报错 后续查看下
  //class MainWindow : public Product {
  //public:
  //  MainWindow(QWidget* parent = nullptr);
  //  ~MainWindow() = default;
  //  // 设置主窗口中央小部件的背景色
  //  virtual void setBackgroundColor();
  //public:
  //  QSharedPointer<QMainWindow> mMainWindow;
  //protected:
  //  QSharedPointer<Ui::MainWindow> mUi;
  //  // 主窗口中央小部件(此处不能用智能指针，因为QMainWindow获取小部件指针的所有权并在适当的时候删除它)
  //  QWidget* mCentralWidget;
  //};

  /*
   * MainWindow类的重新实现
   */
  class EXPORT MainWindow : public Product, public QMainWindow {
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 设置主窗口中央小部件的背景色
    virtual void setBackgroundColor();
    static void doDeleteLater(Product* obj);
  protected:
    QWidget* mCentralWidget;
  private:
    Ui::MainWindow* mUi;
  };

  /*
   * 基类 标签类
   */
  class EXPORT Label : public Product, public QLabel {
  public:
    Label(const QString& text, QWidget* parent = nullptr);
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
  class EXPORT Widget : public Product, public QWidget {
  public:
    Widget(QWidget* parent = nullptr);
    ~Widget() = default;
    // 设置主窗口
    virtual void setMainWindow(QSharedPointer<MainWindow> mainWindow);
    // 设置自定义界面
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    virtual void setupUi();
  protected:
    QSharedPointer<MainWindow> mMainWindow;
  };

  /*
   * 基类 按钮类
   */
  class EXPORT PushButton : public Product, public QPushButton {
  public:
    PushButton(QWidget* parent = nullptr);
    PushButton(const QString& text, QWidget* parent = nullptr);
    PushButton(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~PushButton() = default;
  protected:
    QSharedPointer<const Protocol> mProtocol;
  };

  /*
   * 基类 框架类
   */
  class EXPORT Frame : public Product, public QFrame {
  public:
    Frame(QWidget* parent = nullptr);
    ~Frame() = default;
    // 设置自定义界面
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
  };

  /*
   * 基类 数据库类
   */
  class EXPORT Database : public Product {
  public:
    Database(QSharedPointer<const Protocol> protocol, const QString& connectionName);
    ~Database() = default;
    // 增
    virtual void insert(const QString& sql);
    // 删
    virtual void deleteEx(const QString& sql);
    // 改
    virtual void update(const QString& sql);
    // 查
    virtual void selectEx(const QString& sql);
    // commit
    virtual void commit();
    // 获取数据
    virtual QVector<Record> getData(const ColumnsName& columnsName);
  protected:
    // 执行sql语句
    void sqlExec(const QString& sql);
  protected:
    QSharedPointer<const Protocol> mProtocol;
    QSqlQuery mQuery;
  };

  /*
   * 基类 连接类
   */
  class EXPORT Connection : public Product {
  public:
    Connection(const QString& connectionName);
    ~Connection() = default;
    // 获取连接名字
    const QString getConnectionName() const;
  protected:
    const QString mConnectionName;
  };

  /*
   * 基类 组合框类
   */
  class EXPORT ComboBox : public Product, public QComboBox {
  public:
    ComboBox(QWidget* parent = nullptr);
    ~ComboBox();
  };

  /*
   * 基类 进度条类
   */
  class EXPORT ProgressBar : public Product, public QProgressBar {
  public:
    ProgressBar(QWidget* parent = nullptr);
    ~ProgressBar();
  };

  /*
   * 子类 数据库连接类
   */
  class EXPORT Database_Connection : public Connection {
  public:
    Database_Connection(const QString& driver, const QString& connectionName);
    ~Database_Connection();
    // 打开连接
    virtual void openConnection();
  protected:
    const QString mDriver;
  };

  /*
   * 基类 视图类
   */
  class EXPORT View : public Product {
  public:
    View() = default;
    ~View() = default;
  };

  /*
   * 基类 表视图类
   */
  class EXPORT TableView : public View, public QTableView {
  public:
    TableView(QWidget* parent = nullptr);
    ~TableView();
  };

  /*
   * 基类 图形视图类
   */
  class EXPORT GraphicsView : public View, public QGraphicsView {
  public:
    GraphicsView(QWidget* parent = nullptr);
    ~GraphicsView();
    void setItem(GraphicsPixmapItem* item);
    GraphicsPixmapItem* getItem() const;
  protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
  protected:
    GraphicsPixmapItem* mItem;
  };

  /*
   * 基类 模型类
   */
  class EXPORT Model : public Product, public QAbstractItemModel {
  public:
    Model(QObject* parent = nullptr);
    ~Model();
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    // 添加列名
    //void addColumnName(const QString& );
    // 更新表头
    void updateHeader(ColumnsName& columnsName);
    // 获取表头
    const ColumnsName getHeader() const;
  protected:
    ColumnsName mColumnsName;
    // 所有记录
    QList<Record> mRecords;
  };

  /*
   * 基类 图形项目基类
   */
  class EXPORT GraphicsItem : public Product, public QGraphicsItem {
  public:
    GraphicsItem();
    ~GraphicsItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
  };

  /*
   * 基类 图形场景基类
   */
  class EXPORT GraphicsScene : public Product, public QGraphicsScene {
  public:
    GraphicsScene(QObject* parent = nullptr);
    ~GraphicsScene();
  };

  /*
   * 基类 像素图项目类
   */
  class EXPORT GraphicsPixmapItem : public Product, public QGraphicsPixmapItem {
  public:
    GraphicsPixmapItem(const QPixmap& pixmap);
    ~GraphicsPixmapItem();
  };

  /*
   * 基类 工作者基类
   */
  class EXPORT Worker : public QObject, public Product {
    Q_OBJECT
  public:
    Worker(QObject* parent = nullptr);
    ~Worker();
  };

  /*
   * 基类 控制者基类
   */
  class EXPORT Controller : public QObject, public Product {
    Q_OBJECT
  public:
    Controller(Worker* worker, QObject* parent = nullptr);
    ~Controller();
  protected:
    QThread mWorkerThread;
    Worker* mWorker;
  };

  /*******************************************************************************
   * 子类
   ******************************************************************************/
  /*
   * 子类 中文(简体)
   */
  class EXPORT SimplifiedChinese : public Language {
  public:
    SimplifiedChinese(QSharedPointer<const Protocol> protocol);
    ~SimplifiedChinese() = default;
  };

  /*
   * 子类 XML解析器类
   */
  class EXPORT XMLParser : public Parser {
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
  class EXPORT GTXLQX_XMLParser : public XMLParser {
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
      LAYOUT,
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
    void readLayout(const QXmlStreamReader& reader);
    // 转换函数 元素标签的名称转换为元素标签的枚举类型
    Label_Type labelNameTolabelType(const QString& name);
  private:
    // 模块的名称
    const QLatin1String mUniversalModule, mMainWindowModule, mTitleModule
    ,mTitleLabelModule, mDoorfaceModule, mMenusModule
    ,mMenu, mSubmenu, mLayout;
    // 菜单的数量
    const int mMenusCount;
  };

  /*
   * 子类 配置文件解析类
   */
  class EXPORT ConfigParser : public XMLParser {
  private:
    typedef enum Label_Type {
      INVALID = 0x40,
      UNIVERSAL,
      LANGUAGES,
      DATABASE,
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
    void readDatabaseModule(const QXmlStreamReader& reader);
    // 转换函数 元素标签的名称转换为元素标签的枚举类型
    Label_Type labelNameTolabelType(const QString& name);


  private:
    // 模块的名称
    const QLatin1String mUniversalModule, mLanguagesModule, mDatabaseModule;
    // 语言的数量
    const int mLansCount;
  };

  /*
   * 子类 高铁线路缺陷主窗口类
   */
  class EXPORT GTXLQX_MainWindow : public MainWindow {
    Q_OBJECT
  public:
    GTXLQX_MainWindow(QSharedPointer<const Protocol> uiPro,
                      QSharedPointer<const Protocol> configPro, QWidget* parent = nullptr);
    ~GTXLQX_MainWindow();
    void setBackgroundColor() Q_DECL_OVERRIDE;
  public:
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
    // 设置布局
    void setLayout();
    // 添加标题栏
    void addTitlebar();
    // 添加门脸
    void addDoorface();
    // 添加菜单栏
    void addMenubar();
    // 添加内容窗口
    void addContentWindow();
    // 连接信号和槽
    void createConnect();
  public slots:
    void menu1Clicked();
    void menu2Clicked();
    void menu3Clicked();
    void menu1Submenu1Item1Clicked();
    void menu2Submenu1Item2Clicked();
    void menu3Submenu1Item1Clicked();
  protected:
    QSharedPointer<const Protocol> mUiPro, mConfigPro;
    QVBoxLayout* mVLayout;
    QHBoxLayout* mTitleLayout, *mDoorfaceLayout, *mMenu_Content;
    // 标题栏
    Titlebar* mTitlebar;
    // 门脸
    Doorface_Label* mDoorfaceLabel;
    // 菜单栏
    Menubar* mMenubar;
    // 内容区
    ContentArea* mContentArea;


  };

  /*
   * 子类 最小化窗口标签类
   */
  class EXPORT MinWindow_Label : public Label {
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
  class EXPORT MaxWindow_Label : public Label {
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
  class EXPORT ShutdownWindow_Label : public Label {
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
  class EXPORT Titlebar_Label : public Label {
  public:
    Titlebar_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~Titlebar_Label() = default;
    void setMinSizeWidget() Q_DECL_OVERRIDE;
    void setDefPictureWidget() Q_DECL_OVERRIDE;
  protected:
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;

  };

  /*
   * 子类 标题栏标签类(包含最小化、最大化、关闭按钮)
   */
  class EXPORT TitlebarMinMaxShut_Label : public Label {
  protected:
    enum TitleButton {
      INVALID = 0x60,
      MIN,
      MAX,
      SHUT,
    };
  public:
    TitlebarMinMaxShut_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~TitlebarMinMaxShut_Label();
    void setMousetrackingWidget() Q_DECL_OVERRIDE;
  protected:
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    // 获取最小化按钮的区域
    QRect getMinButtonRegion();
    // 获取最大化按钮的区域
    QRect getMaxButtonRegion();
    // 获取关闭按钮的区域
    QRect getShutButtonRegion();
  protected:
    QPoint mOldCursorPoint;
    // 按钮的宽度、按钮与标题栏顶部的距离
    int mButtonWidth;
    int mButtonDisTop;
    // 填充的空白区域大小
    int mSpacing;
    // 当前鼠标点击或移动到的按钮类型
    TitleButton mCurrentTitleButton;
    // 鼠标左键是否按下
    bool mLeftButtonPressed;
    // 主窗口当前是否为最大化显示
    bool mMainWinMaxDisplayCurrent;
  };

  /*
   * 子类 门脸标签类
   */
  class EXPORT Doorface_Label : public Label {
  public:
    Doorface_Label(QSharedPointer<const Protocol> protocol, QWidget* parent = nullptr);
    ~Doorface_Label() = default;
  protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

  };

  /*
   * 子类 标题栏类
   */
  class EXPORT Titlebar final : public Widget {
  public:
    Titlebar(QWidget* parent = nullptr);
    ~Titlebar() = default;
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  private:
    TitlebarMinMaxShut_Label* mTitlebarMinMaxShut;
    friend class GTXLQX_MainWindow;
  };

  /*
   * 子类 菜单栏类
   */
  class EXPORT Menubar final : public Widget {
    Q_OBJECT
  public:
    Menubar(QWidget* parent = nullptr);
    ~Menubar() = default;
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    // 隐藏所有子菜单
    void hideAllSubmenus();
  private:
    // 所有主菜单
    QHash<const QString, Menu_Label*> mMenus;
    // 所有子菜单
    QHash<const QString, SubMenu*> mSubmenus;
    friend class GTXLQX_MainWindow;
  };

  /*
   * 子类 子菜单栏类
   */
  class EXPORT SubMenu : public Widget {
    Q_OBJECT
  public:
    SubMenu(const GTXLQXPro::Submenu& subMenu, QWidget* parent = nullptr);
    ~SubMenu() = default;
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    // 子菜单
    const GTXLQXPro::Submenu mSubmenu;
    // 所有菜单项
    QHash<const QString, MenuItem_Label*> mMenuItems;
    friend class GTXLQX_MainWindow;
  };

  /*
   * 子类 内容区类
   */
  class EXPORT ContentArea :public Widget {
  public:
    ContentArea(QSharedPointer<const Protocol> configPro, QWidget* parent = nullptr);
    ~ContentArea() = default;
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    // 向容器中添加小部件
    void addWidgetInContentArea(Widget* widget);
    // 从容器中删除小部件
    void removeWidgetInContentArea(const QString& name);
    // 显示指定小部件
    void showSpecifiedWidget(Widget* widget);
  protected:
    // 内容区中所有小部件的容器(容器中存储的每一个小部件是一个整体，这个整体中添加自定义的界面)
    QStackedWidget* mWidgets;
    // 存储所有小部件的名称与小部件
    QHash<const QString, Widget*> mWidgetsIndex;
    QSharedPointer<const Protocol> mConfigPro;
    friend class GTXLQX_MainWindow;
  };

  /*
  * 子类 主菜单按钮类
  */
  class EXPORT Menu_PushButton : public PushButton {
    Q_OBJECT
  public:
    Menu_PushButton(QSharedPointer<const Protocol> protocol, const QString& fileName, QWidget* parent = nullptr);
    ~Menu_PushButton() = default;
  protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
  protected:
    const QString mFileName;
  };

  /*
   * 子类 主菜单标签类
   */
  class EXPORT Menu_Label : public Label {
    Q_OBJECT
  public:
    Menu_Label(QSharedPointer<const Protocol> protocol, const QString& fileName, QWidget* parent = nullptr);
    ~Menu_Label() = default;
  Q_SIGNALS:
    void clicked();
  protected:
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
  protected:
    const QString mFileName;
  };

  /*
   * 子类 菜单项按钮类
   */
  class EXPORT MenuItem_PushButton : public PushButton {
  public:
    MenuItem_PushButton(QSharedPointer<const Protocol> protocol, const QString& fileName, QWidget* parent = nullptr);
    ~MenuItem_PushButton() = default;
  protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
  protected:
    const QString mFileName;
  };

  /*
   * 子类 菜单项标签类
   */
  class EXPORT MenuItem_Label : public Label {
    Q_OBJECT
  public:
    MenuItem_Label(QSharedPointer<const Protocol> protocol, const QString& itemDefaultPicture
                   ,const QString& itemClickedPicture, QWidget* parent = nullptr);
    ~MenuItem_Label() = default;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
  Q_SIGNALS:
    void clicked();
  protected:
    //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
  protected:
    const QString mItemDefaultPicture, mItemClickedPicture;
  };

  /*
   * 四分屏类
   */
  class EXPORT QuadScreen : public Widget {
  public:
    QuadScreen(QWidget* parent = nullptr);
    ~QuadScreen() = default;
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  };

  /*
   * 子类  Mysql数据库类
   */
  //class Mysql_Database : public Database, public QSqlTableModel {
  //public:
  //  Mysql_Database(QSqlDatabase connection, QSharedPointer<const Protocol> protocol, QObject* parent = nullptr);
  //  ~Mysql_Database();
  //  // 增
  //  virtual void append_Into(const RecordType& record) Q_DECL_OVERRIDE;
  //  // 删
  //  virtual void delete_From(const int row) Q_DECL_OVERRIDE;
  //  // 改
  //  virtual void update() Q_DECL_OVERRIDE;
  //  // 查
  //  virtual void selectEx() Q_DECL_OVERRIDE;
  //  virtual void commit() Q_DECL_OVERRIDE;
  //  //QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  //protected:
  //  // 初始化
  //  void init();
  //  // 设置表头
  //  void setTableHeader();
  //  // 附加高铁线路缺陷记录
  //  void appendGTXLQXRecord(const RecordType& record);
  //protected:
  //  static int mRow;
  //};

  /*
   * 子类  Mysql数据库类
   */
  class EXPORT MySQL_Database : public Database {
  public:
    MySQL_Database(QSharedPointer<const Protocol> protocol, const QString& connectionName);
    ~MySQL_Database();
    void selectAll();
  };

  /*
   * 子类 Mysql数据库连接类
   */
  class EXPORT Mysql_Connection final : public Database_Connection {
  public:
    Mysql_Connection(QSharedPointer<const Protocol> protocol);
    ~Mysql_Connection() = default;
    virtual void openConnection();
  private:
    QSharedPointer<const Protocol> mProtocol;
  };

  /*
   * 子类 测试视图
   */
  class EXPORT Test_View : public View, public QTableView {
  public:
    Test_View(QSqlTableModel* model, QWidget* parent = nullptr);
    ~Test_View() = default;
  };

  /*
   * 子类 测试视图
   */
  //class Test_Widget : public Widget {
  //public:
  //  Test_Widget(QWidget* parent = nullptr);
  //  ~Test_Widget() = default;
  //  virtual void setupUi(QSharedPointer<const Protocol> protocol);
  //};

  /*
   * 子类 审查结果查询小部件类
   */
  class EXPORT ReviewResultQuery_Widget : public Widget {
    Q_OBJECT
  public:
    ReviewResultQuery_Widget(QWidget* parent = nullptr);
    ~ReviewResultQuery_Widget();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
  protected:
    // 创建信号和槽
    void createConnection();
  public Q_SLOTS:
    void queryBtnClicked();
  protected:
    Label* mLineName_Label;
    ComboBox* mLineName_Combobox;
    Label* mLineDirection_Label;
    ComboBox* mLineDirection_Combobox;
    Label* mExportState_Label;
    ComboBox* mExportState_Combobox;
    Label* mDefectName_Label;
    ComboBox* mDefectName_Combobox;
    Label* mAuditType_Label;
    ComboBox* mAuditType_Combobox;
    Label* mStartTime_Label;
    QDateTimeEdit* mStartTime_TimeEdit;
    Label* mEndTime;
    QDateTimeEdit* mEndTime_TimeEdit;
    PushButton* mQuery_Btn;
    Label* mCount_Label;
    Label* mTotal_Label;
    Label* mPicture_Label;
    TableView* mView;
    QSharedPointer<Database> mDatabase;
    Model* mModel;
    //private:
    //  friend class GTXLQX_MainWindow;
  };

  /*
   * 子类 数据库表视图类
   */
  class EXPORT DatabaseTable_View : public TableView {
  public:
    DatabaseTable_View(QWidget* parent = nullptr);
    ~DatabaseTable_View();
  };

  /*
   * 子类 高铁线路缺陷模型类
   */
  class EXPORT GTXLQX_Model : public Model {
  public:
    GTXLQX_Model(QObject* parent = nullptr);
    ~GTXLQX_Model();
    // 显示审查结果
    void showReviewResult(QList<Record>& records);
  };

  /*
   * 子类 单路显示类
   */
  class EXPORT Channel_Frame: public Frame {
  public:
    Channel_Frame(QWidget* parent = nullptr);
    ~Channel_Frame();
    Channel_Frame(const Channel_Frame& other);
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    GraphicsView* view() const;
    void setItem(GraphicsPixmapItem* item);
  protected:
    GraphicsView* mView;
  };

  /*
   * 子类 32路分屏显示类
   */
  class EXPORT SplitScreenDisplay32Channel : public Widget {
    Q_OBJECT
  public:
    SplitScreenDisplay32Channel(QWidget* parent = nullptr);
    ~SplitScreenDisplay32Channel();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void populateScene();
  public Q_SLOTS:
    void handleResults(QVariantHash pixmaps);
  protected Q_SLOTS:
    void timeouted();
  protected:
    //QVector<QSplitter*> mHSplitters;
    //    QSplitter* mH1Splitter;
    //    QSplitter* mH2Splitter;
    //    QSplitter* mH3Splitter;
    //    QSplitter* mH4Splitter;
    //    QSplitter* mH5Splitter;
    //    QSplitter* mH6Splitter;
    //    QSplitter* mH7Splitter;
    //    QSplitter* mH8Splitter;
    QVector<Channel_Frame*> mChannels;
    GraphicsScene* mScene;
    QTimer mTimer;
    cv::VideoCapture vcap;
    QtToOpencv::ImageConversion mConv;
    QGraphicsItem* mItem;
    QHash<const int, GraphicsPixmapItem*> mItems;
    QScopedPointer<Controller, QScopedPointerDeleteLater> mController;
  };

  /*
   * 子类 单路视图类
   */
  class EXPORT Channel_View : public GraphicsView {
  public:
    Channel_View(QWidget* parent = nullptr);
    ~Channel_View();
  };

  /*
   * 子类 32路场景类
   */
  class EXPORT Channel32_Scene : public GraphicsScene {
  public:
    Channel32_Scene(QObject* parent = nullptr);
    ~Channel32_Scene();
  };

  /*
   * 子类 32路显示工作者类
   */
  class EXPORT Channel32_Worker : public Worker {
    Q_OBJECT
  public:
    Channel32_Worker(QObject* parent = nullptr);
    ~Channel32_Worker();
  public Q_SLOTS:
    void doWork();
  Q_SIGNALS:
    void resultReady(QVariantHash pixmaps);
  protected:
  };

  /*
   * 子类 32路显示控制者类
   */
  class EXPORT Channel32_Controller : public Controller {
    Q_OBJECT
  public:
    Channel32_Controller(QObject* parent = nullptr);
    ~Channel32_Controller();
  Q_SIGNALS:
    void operate();
  protected:
    friend class SplitScreenDisplay32Channel;
  };

  /*
   * 子类 菜单栏类(模仿海康IVMS-4200菜单栏样式)
   */
  class EXPORT IVMS4200Menubar_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200Menubar_Widget(QWidget* parent = nullptr);
    ~IVMS4200Menubar_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    // 前序添加菜单
    void addMenuFront(IVMS4200Menu_Widget* menu);
    // 设置菜单栏主按钮
    void setMenuBarMainButton(IVMS4200MenuBarMainBtn_Widget* mainBtn);
    // 取消菜单栏主按钮
    void cancelMenuBarMainButton(IVMS4200MenuBarMainBtn_Widget* mainBtn);
    void cancelMenuBarMainButton(const int index = 0);
  Q_SIGNALS:
    void addMenuFront_Signal();
  public Q_SLOTS:
    void addMenuFront_Slot();
  protected:
    // 添加菜单
    void addMenuStack(IVMS4200Menu_Widget* menu);
    void initWindow();
    void initLayout();
  protected:
    // variable
    QStack<IVMS4200Menu_Widget*> mMenusStack;
    QHBoxLayout* mMainLayout;
  };

  /*
   * 子类 菜单类(模仿海康IVMS-4200菜单样式)
   */
  class EXPORT IVMS4200Menu_Widget : public Widget {
  public:
    IVMS4200Menu_Widget(QWidget* parent = nullptr);
    ~IVMS4200Menu_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* iconLabel() const;
    Label* contentLabel() const;
    Label* closeLabel() const;
    Label* colorBarLabel() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    IVMS4200Menu_Widget* mPreItem;
    IVMS4200Menu_Widget* mNextItem;
    IVMS4200MenuBarSeparator_Widget* mPreSeparator;
    IVMS4200MenuBarSeparator_Widget* mNextSeparator;
    QVBoxLayout* mMainLayout;
    QHBoxLayout* mContentLayout;
    QHBoxLayout* mColorBarLayout;
    Label* mIcon;
    Label* mContent;
    Label* mClose;
    Label* mColorBar;
  private:
    friend class IVMS4200Menubar_Widget;
  };

  /*
   * 子类 入侵检测主窗口类
   */
  class EXPORT IntrusionDetection_MainWindow : public Widget {
  public:
    IntrusionDetection_MainWindow(QWidget* parent = nullptr);
    ~IntrusionDetection_MainWindow();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    IVMS4200TitleBar_Widget* titleBar() const;
    IVMS4200Menubar_Widget* menuBar() const;
    IVMS4200ContentArea_Widget* contentArea() const;
    IVMS4200StatusBar_Widget* statusBar() const;
    void addMenuFront(IVMS4200Menu_Widget* menu);
    void insertMenu(const int index, IVMS4200Menu_Widget* menu);
  protected:
    void initWindow();
    void initLayout();
    void init();
    void setMenuBar(Widget* menuBar);
    void setTitleBar(Widget* titleBar);
    void setContentArea(Widget* contentArea);
    void setStatusBar(Widget* statusBar);
  protected:
    // variable
    QVBoxLayout* mMainLayout;
    QHBoxLayout* mTitleLayout;
    QHBoxLayout* mMenuLayout;
    QHBoxLayout* mContentLayout;
    QHBoxLayout* mStatusBarLayout;

    Widget* mTitleBar;
    Widget* mMenuBar;
    Widget* mContentArea;
    Widget* mStatusBar;
  };

  /*
   * 子类 标题栏类(模仿海康IVMS-4200标题栏样式)
   */
  class EXPORT IVMS4200TitleBar_Widget : public Widget {
  public:
    IVMS4200TitleBar_Widget(QWidget* parent = nullptr);
    ~IVMS4200TitleBar_Widget();
  protected:
    void initWindow();
  };

  /*
   * 子类 内容区类(模仿海康IVMS-4200内容区)
   */
  class IVMS4200ContentArea_Widget : public Widget {
  public:
    IVMS4200ContentArea_Widget(QWidget* parent = nullptr);
    ~IVMS4200ContentArea_Widget();
  };

  /*
   * 子类 状态栏类(模仿海康IVMS-4200状态栏样式)
   */
  class IVMS4200StatusBar_Widget : public Widget {
  public:
    IVMS4200StatusBar_Widget(QWidget* parent = nullptr);
    ~IVMS4200StatusBar_Widget();
  protected:
    void initWindow();
  };

  /*
   * 子类 菜单栏主按钮(模仿海康IVMS-4200菜单栏主按钮)
   */
  class IVMS4200MenuBarMainBtn_Widget : public Widget {
  public:
    IVMS4200MenuBarMainBtn_Widget(QWidget* parent = nullptr);
    ~IVMS4200MenuBarMainBtn_Widget();
  };

  /*
   * 子类 菜单栏菜单项分隔符类(模仿海康IVMS-4200菜单栏菜单项分隔符)
   */
  class IVMS4200MenuBarSeparator_Widget : public Widget {
  public:
    IVMS4200MenuBarSeparator_Widget(QWidget* parent = nullptr);
    ~IVMS4200MenuBarSeparator_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QVBoxLayout* mMainLayout;
    Label* mLabel;
  };

}

Q_DECLARE_METATYPE(QVector<Jinhui::Channel_Frame*>)

#endif // PARSER_H
