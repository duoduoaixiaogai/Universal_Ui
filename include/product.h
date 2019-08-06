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
#include <QFile>

// ui
#include <QComboBox>
#include <QProgressBar>
#include <QLineEdit>

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
class QBoxLayout;
QT_END_NAMESPACE

namespace Jinhui {
  // Forward declaration
  class Widget;
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
  class IVMS4200MenuEx_Frame;
  class IVMS4200TitleBar_Widget;
  class IVMS4200ContentArea_Widget;
  class IVMS4200StatusBar_Widget;
  class IVMS4200MenuBarMainBtn_Widget;
  class IVMS4200MenuBarSeparator_Widget;
  class IVMS4200DefShowMenu_Widget;
  class IVMS4200ClickShowMenu_Widget;
  class IVMS4200MoveShowMenu_Widget;
  class IVMS4200ExpandStatusBar_Widget;
  class DealWithMouseEvent_Label;
  class IVMS4200ContentAreaHomeLeft_Widget;
  class IVMS4200ContentAreaHomeRight_Widget;
  class IVMS4200ContentAreaHomeLeftWgt_Widget;
  class IVMS4200ContentAreaHomeRightWgt_Widget;
  class TreeTopLevelItem_Label;
  class TreeChildLevelItem_Label;
  class IVMS4200MainPreviewLeftWgt_Frame;
  class IVMS4200MainPreviewMidWgt_Frame;
  class IVMS4200MainPreviewRightWgt_Frame;
  class IVMS4200TitleWgt_Frame;
  class SingleLabel_Frame;

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
    void setProductName(QString name);
    QString productName() const;
  protected:
    QString mName;
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
  class EXPORT MainWindow : public QMainWindow, public Product {
    Q_OBJECT
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
  class EXPORT Label : public QLabel, public Product {
    Q_OBJECT
  public:
    Label(const QString& text, QWidget* parent = nullptr);
    Label(QWidget* parent = nullptr);
    ~Label() = default;
    // 设置主窗口
    virtual void setMainWindow(QSharedPointer<MainWindow> mainWindow);
    virtual void setMainWindow_Widget(QSharedPointer<Widget> mainWindow_Widget);
    // 设置小部件鼠标跟踪
    virtual void setMousetrackingWidget();
    // 设置小部件最小尺寸
    virtual void setMinSizeWidget();
    // 设置小部件默认图片
    virtual void setDefPictureWidget();
    // 设置鼠标移动进入小部件时的图片
    virtual void setMouseInWidgetPicture();
  Q_SIGNALS:
    //void mouseMove(QMouseEvent* event);
    //void mousePress(QMouseEvent* event);
    //void mouseRelease(QMouseEvent* event);
  protected:
    // 设置图片
    void setPicture(int width, int height, const QString& fileName);
    //void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    QSharedPointer<const Protocol> mProtocol;
    QSharedPointer<MainWindow> mMainWindow;
    QSharedPointer<Widget> mMainWindow_Widget;
  };

  /*
   * 基类 小部件类
   */
  class EXPORT Widget : public QWidget, public Product {
    Q_OBJECT
  public:
    Widget(QWidget* parent = nullptr);
    ~Widget() = default;
    // 设置主窗口
    virtual void setMainWindow(QSharedPointer<MainWindow> mainWindow);
    virtual void setMainWindow_Widget(QSharedPointer<Widget> mainWindow_Widget);
    // 设置自定义界面
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    virtual void setupUi();
  protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  protected:
    QSharedPointer<MainWindow> mMainWindow;
    QSharedPointer<Widget> mMainWindow_Widget;
  };

  /*
   * 基类 按钮类
   */
  class EXPORT PushButton : public QPushButton, public Product {
    Q_OBJECT
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
  class EXPORT Frame : public QFrame, public Product {
    Q_OBJECT
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
  class EXPORT ComboBox : public QComboBox, public Product {
    Q_OBJECT
  public:
    ComboBox(QWidget* parent = nullptr);
    ~ComboBox();
  };

  /*
   * 基类 进度条类
   */
  class EXPORT ProgressBar : public QProgressBar, public Product {
    Q_OBJECT
  public:
    ProgressBar(QWidget* parent = nullptr);
    ~ProgressBar();
  };

  /*
   * 基类 编译框类
   */
  class LineEdit : public QLineEdit, public Product {
  public:
    LineEdit(QWidget* parent = nullptr);
    ~LineEdit();
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
  class EXPORT TableView : public QTableView, public View {
  public:
    TableView(QWidget* parent = nullptr);
    ~TableView();
  };

  /*
   * 基类 图形视图类
   */
  class EXPORT GraphicsView : public QGraphicsView, public View {
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
  class EXPORT Model : public QAbstractItemModel, public Product {
    Q_OBJECT
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
  class EXPORT GraphicsItem : public QGraphicsItem, public Product {
  public:
    GraphicsItem();
    ~GraphicsItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
  };

  /*
   * 基类 图形场景基类
   */
  class EXPORT GraphicsScene : public QGraphicsScene, public Product {
  public:
    GraphicsScene(QObject* parent = nullptr);
    ~GraphicsScene();
  };

  /*
   * 基类 像素图项目类
   */
  class EXPORT GraphicsPixmapItem : public QGraphicsPixmapItem, public Product {
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

  /*
   * 基类 文件类
   */
  class EXPORT File : public QFile, public Product {
  public:
    File(QObject* parent = nullptr);
    File(const QString& name);
    ~File();
  };

  /*
   * 基类 树控件类
   */
  class EXPORT Tree : public Frame {
    Q_OBJECT
  public:
    Tree(QWidget* parent = nullptr);
    ~Tree();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    void addTopLevelItem(Frame* topLevelItem);
    void addChildLevelItem(const QString topLevelItem, Frame* childLevelItem);
    void delTopLevelItem(const QString topLevelItem);
    void delChildLevelItem(const QString topLevelItem, const QString childLevelItem);
    QVBoxLayout* mainLayout() const;
  public Q_SLOTS:
    void addTopLevelItem_Slot(const QString name);
    void addChildLevelItem_Slot(const QString topName, const QString childName);
    void delTopLevelItem_Slot(const QString name);
    void delChildLevelItem_Slot(const QString topName, const QString childName);
  Q_SIGNALS:
    void addTopLevelItem_Signal(const QString name);
    void addChildLevelItem_Signal(const QString topName, const QString childName);
    void delTopLevelItem_Signal(const QString name);
    void delChildLevelItem_Signal(const QString topName, const QString name);
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    typedef QHash<const QString, QVector<Frame*> > ChildItems;
    QHash<const QString, ChildItems> mTopLevelItems;
    QBoxLayout* mMainLayout;
    QVector<Frame*> mChildItems;
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
      QSS,
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
    void readQssModule(const QXmlStreamReader& reader);
    // 转换函数 元素标签的名称转换为元素标签的枚举类型
    Label_Type labelNameTolabelType(const QString& name);


  private:
    // 模块的名称
    const QLatin1String mUniversalModule, mLanguagesModule, mDatabaseModule
    ,mQssModule;
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    Q_OBJECT
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
    void addMenuExFront(IVMS4200MenuEx_Frame* menu);
    // 设置菜单栏主按钮
    void setMenuBarMainButton(IVMS4200MenuBarMainBtn_Widget* mainBtn);
    // 取消菜单栏主按钮
    void cancelMenuBarMainButton(IVMS4200MenuBarMainBtn_Widget* mainBtn);
    void cancelMenuBarMainButton(const int index = 0);
  Q_SIGNALS:
    void addMenuFront_Signal();
    void addMenuExFront_Signal();
    void restoreLastMenuDefShow();
    void currentMenuExChanged(const QString);
    void menuBarMainBtnClicked(const QString);
  public Q_SLOTS:
    void addMenuFront_Slot();
    void addMenuExFront_Slot();
    void changeCurrentMenu(Widget* menu);
    void changeCurrentMenuEx(Frame* menu);
  protected:
    // 添加菜单
    void addMenuStack(IVMS4200Menu_Widget* menu);
    void addMenuExStack(IVMS4200MenuEx_Frame* menu);
    void initWindow();
    void initLayout();
  protected:
    // variable
    QStack<IVMS4200MenuEx_Frame*> mMenuExsStack;
    QStack<IVMS4200Menu_Widget*> mMenusStack;
    QHBoxLayout* mMainLayout;
    Widget* mCurrentMenu;
    Frame* mCurrentMenuEx;
    QPoint mActiveMenuPos;
  };

  /*
   * 子类 菜单类(模仿海康IVMS-4200菜单样式)
   */
  class EXPORT IVMS4200Menu_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200Menu_Widget(QWidget* parent = nullptr);
    ~IVMS4200Menu_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    IVMS4200DefShowMenu_Widget* defShowMenu() const;
    IVMS4200MoveShowMenu_Widget* moveShowMenu() const;
    IVMS4200ClickShowMenu_Widget* clickShowMenu() const;
    void setMenuBar(Widget* menuBar);
    //Label* iconLabel() const;
    //Label* contentLabel() const;
    //Label* closeLabel() const;
    //Label* colorBarLabel() const;
  public Q_SLOTS:
    //void showCloseColorBar();
    //void hideCloseColorBar();
    void restoreDefShowMenu();
    void switchMoveShowMenu();
  Q_SIGNALS:
    void currentMenuChanged(Widget* menu);
  protected:
    void initWindow();
    void initLayout();
    void init();
    // Qt events
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    bool mouseInMenuBar(QPoint currentMousePos);
  protected:
    IVMS4200Menu_Widget* mPreItem;
    IVMS4200Menu_Widget* mNextItem;
    IVMS4200MenuBarSeparator_Widget* mPreSeparator;
    IVMS4200MenuBarSeparator_Widget* mNextSeparator;
    QVBoxLayout* mMainLayout;
    //QHBoxLayout* mContentLayout;
    //QHBoxLayout* mColorBarLayout;
    //Label* mIcon;
    //Label* mContent;
    //Label* mClose;
    //Label* mColorBar;
    Widget* mMenuBar;
    Widget* mDefShowMenu;
    Widget* mMoveShowMenu;
    Widget* mClickShowMenu;
    QStackedWidget* mWidgets;
    Qt::MouseButton mCurrentBtn;
    QPoint mPreviousMousePos;
  private:
    //void showClose();
    //void hideClose();
    //void showColorBar();
    //void hideColorBar();
  private:
    friend class IVMS4200Menubar_Widget;
  };

  /*
   * 子类 菜单类(模仿海康IVMS-4200菜单样式)是上一个菜单类的扩展(上一个菜单类实现的不够好)
   */
  // 问题： 用PushButton Qss 必须设置一个最小的宽度，才能显示，用Frame和Widget不用设置最小宽度，
  // 会自动适应大小(这为后期留了一个坑，如果后期中没有字或者图标什么的会造成空间的浪费，显示的也不好看)。
  class EXPORT IVMS4200MenuEx_Frame : public Frame {
    //class EXPORT IVMS4200MenuEx_Frame : public Widget {
    Q_OBJECT
  public:
    IVMS4200MenuEx_Frame(QWidget* parent = nullptr);
    ~IVMS4200MenuEx_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    void setMenuBar(Widget* menuBar);
    void setTextAlignment(Qt::Alignment alignment);
    Label* iconLabel() const;
    Label* contentLabel() const;
    Label* closeLabel() const;
    Label* colorBarLabel() const;
  public Q_SLOTS:
    void restoreDefShowMenu();
  Q_SIGNALS:
    //void currentMenuChanged(Widget* menu);
    void currentMenuExChanged(Frame* menu);
    void currentMenuExChanged(const QString);
  protected:
    void initWindow();
    void initLayout();
    void init();
    // Qt events
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    bool mouseInMenuBar(QPoint currentMousePos);
  protected:
    IVMS4200MenuEx_Frame* mPreItem;
    IVMS4200MenuEx_Frame* mNextItem;
    IVMS4200MenuBarSeparator_Widget* mPreSeparator;
    IVMS4200MenuBarSeparator_Widget* mNextSeparator;
    QBoxLayout* mMainLayout;
    QHBoxLayout* mContentLayout;
    QHBoxLayout* mIconLayout;
    QHBoxLayout* mTextLayout;
    QHBoxLayout* mCloseLayout;
    QHBoxLayout* mColorBarLayout;
    Label* mIcon;
    Label* mContent;
    Label* mClose;
    Label* mColorBar;
    Widget* mMenuBar;
    Qt::MouseButton mCurrentBtn;
    QPoint mPreviousMousePos;
  private:
    void showClose();
    void hideClose();
    void showColorBar();
    void hideColorBar();
  private:
    friend class IVMS4200Menubar_Widget;
  };

  /*
   * 子类 入侵检测主窗口类
   */
  class EXPORT IntrusionDetection_MainWindow : public Widget {
    Q_OBJECT
  public:
    IntrusionDetection_MainWindow(QWidget* parent = nullptr);
    ~IntrusionDetection_MainWindow();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    IVMS4200TitleBar_Widget* titleBar() const;
    IVMS4200Menubar_Widget* menuBar() const;
    IVMS4200ContentArea_Widget* contentArea() const;
    IVMS4200StatusBar_Widget* statusBar() const;
    IVMS4200ExpandStatusBar_Widget* expandStatusBar() const;
    void addMenuFront(IVMS4200Menu_Widget* menu);
    void addMenuExFront(IVMS4200MenuEx_Frame* menu);
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
    Widget* mExpandStatusBar;
  };

  /*
   * 子类 标题栏类(模仿海康IVMS-4200标题栏样式)
   */
  class EXPORT IVMS4200TitleBar_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200TitleBar_Widget(QWidget* parent = nullptr);
    ~IVMS4200TitleBar_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* icon() const;
    Label* login() const;
    Label* menu() const;
    Label* resource() const;
    Label* permission() const;
    Label* convenience() const;
    Label* seprator() const;
    Label* lock() const;
    Label* minimize() const;
    Label* maximize() const;
    Label* shutDown() const;
  public Q_SLOTS:
    //void minimizeMainWindow(QMouseEvent* event);
    //void maximizeMainWindow(QMouseEvent* event);
    //void shutDownMainWindow(QMouseEvent* event);
  protected:
    void initWindow();
    void initLayout();
    void init();
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    QHBoxLayout* mMainLayout;
    QHBoxLayout* mIconLayout;
    QHBoxLayout* mLoginLayout;
    QHBoxLayout* mMenuLayout;
    QHBoxLayout* mResourceLayout;
    QHBoxLayout* mPermissionLayout;
    QHBoxLayout* mConvenienceLayout;
    QHBoxLayout* mSepratorLayout;
    QHBoxLayout* mLockLayout;
    QHBoxLayout* mMinimizeLayout;
    QHBoxLayout* mMaximizeLayout;
    QHBoxLayout* mShutDownLayout;

    Label* mIcon;
    Label* mLogin;
    Label* mMenu;
    Label* mResource;
    Label* mPermission;
    Label* mConvenience;
    Label* mSeprator;
    Label* mLock;
    Label* mMinimize;
    Label* mMaximize;
    Label* mShutDown;

    Qt::MouseButton mCurrentBtn;
    QPoint mPreviousMousePos;
  };

  /*
   * 子类 内容区类(模仿海康IVMS-4200内容区)
   */
  class EXPORT IVMS4200ContentArea_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ContentArea_Widget(QWidget* parent = nullptr);
    ~IVMS4200ContentArea_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    QStackedWidget* widgetsContainer() const;
    void addWidget(Frame* widget);
  public Q_SLOTS:
    void changeCurrentContentArea(const QString name);
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QStackedWidget* mWidgets;
    QHBoxLayout* mMainLayout;
    QHash<const QString, Frame*> mWgtsHash;
  };

  /*
   * 子类 状态栏类(模仿海康IVMS-4200状态栏样式)
   */
  class EXPORT IVMS4200StatusBar_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200StatusBar_Widget(QWidget* parent = nullptr);
    ~IVMS4200StatusBar_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    DealWithMouseEvent_Label* label0() const;
    DealWithMouseEvent_Label* label1() const;
    DealWithMouseEvent_Label* label2() const;
    DealWithMouseEvent_Label* label3() const;
    DealWithMouseEvent_Label* label4() const;
    DealWithMouseEvent_Label* label5() const;
    DealWithMouseEvent_Label* label6() const;
    DealWithMouseEvent_Label* label7() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QHBoxLayout* mMainLayout;
    QHBoxLayout* mHLayout0;
    QHBoxLayout* mHLayout1;
    QHBoxLayout* mHLayout2;
    QHBoxLayout* mHLayout3;
    QHBoxLayout* mHLayout4;
    QHBoxLayout* mHLayout5;
    QHBoxLayout* mHLayout6;
    QHBoxLayout* mHLayout7;

    Label* mLabel0;
    Label* mLabel1;
    Label* mLabel2;
    Label* mLabel3;
    Label* mLabel4;
    Label* mLabel5;
    Label* mLabel6;
    Label* mLabel7;
  };

  /*
   * 子类 菜单栏主按钮(模仿海康IVMS-4200菜单栏主按钮)
   */
  class EXPORT IVMS4200MenuBarMainBtn_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200MenuBarMainBtn_Widget(QWidget* parent = nullptr);
    ~IVMS4200MenuBarMainBtn_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* mainBtn() const;
    void setDefPixmap(const QString& pixmapPath);
    void setMovePixmap(const QString& pixmapPath);
  Q_SIGNALS:
    void menuBarMainBtnClicked(const QString);
  protected:
    void initWindow();
    void initLayout();
    void init();
    // 疑问：为什么明明是子小部件要接受事件的，但是写到父小部件中也能实现相同的效果？
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    // variable
    QVBoxLayout* mMainLayout;
    Label* mMainBtn;
    QPixmap mMovePixmap;
    QPixmap mDefPixmap;
  };

  /*
   * 子类 菜单栏菜单项分隔符类(模仿海康IVMS-4200菜单栏菜单项分隔符)
   */
  class IVMS4200MenuBarSeparator_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200MenuBarSeparator_Widget(QWidget* parent = nullptr);
    ~IVMS4200MenuBarSeparator_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  public Q_SLOTS:
    void defShow();
    void moveShow();
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QVBoxLayout* mMainLayout;
    QVBoxLayout* mMoveWgtLayout;
    Label* mDefShow;
    Label* mMoveShow;
    Widget* mMoveWgt;
    QStackedWidget* mWidgets;
  };

  /*
   * 子类 默认展示菜单项小部件类
   */
  class EXPORT IVMS4200DefShowMenu_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200DefShowMenu_Widget(QWidget* parent = nullptr);
    ~IVMS4200DefShowMenu_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* iconLabel() const;
    Label* contentLabel() const;
  Q_SIGNALS:
    void mouseMove();
  protected:
    void initWindow();
    void initLayout();
    void init();
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    QVBoxLayout* mMainLayout;
    QHBoxLayout* mContentLayout;
    QHBoxLayout* mColorBarLayout;
    Label* mIcon;
    Label* mContent;
  };

  /*
   * 子类 鼠标移动默认展示菜单项小部件类
   */
  class EXPORT IVMS4200MoveShowMenu_Widget : public IVMS4200DefShowMenu_Widget {
    Q_OBJECT
  public:
    IVMS4200MoveShowMenu_Widget(QWidget* parent = nullptr);
    ~IVMS4200MoveShowMenu_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
  };

  /*
   * 子类 鼠标点击展示菜单项小部件类
   */
  class EXPORT IVMS4200ClickShowMenu_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ClickShowMenu_Widget(QWidget* parent = nullptr);
    ~IVMS4200ClickShowMenu_Widget();
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
    QVBoxLayout* mMainLayout;
    QHBoxLayout* mContentLayout;
    QHBoxLayout* mColorBarLayout;
    Label* mIcon;
    Label* mContent;
    Label* mClose;
    Label* mColorBar;
  };

  /*
   * 子类 最小化主窗口标签类
   */
  class MinimizeMainWindow_Label : public Label {
    Q_OBJECT
  public:
    MinimizeMainWindow_Label(QWidget* parent = nullptr);
    ~MinimizeMainWindow_Label();
  protected:
    //void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  };

  /*
   * 子类 最大化主窗口标签类
   */
  class MaximizeMainWindow_Label : public Label {
    Q_OBJECT
  public:
    MaximizeMainWindow_Label(QWidget* parent = nullptr);
    ~MaximizeMainWindow_Label();
  protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  };

  /*
   * 子类 关闭主窗口标签类
   */
  class ShutDownMainWindow_Label : public Label {
    Q_OBJECT
  public:
    ShutDownMainWindow_Label(QWidget* parent = nullptr);
    ~ShutDownMainWindow_Label();
  protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  };

  /*
   * 子类 带有处理鼠标事件的标签类
   */
  class EXPORT DealWithMouseEvent_Label : public Label {
    Q_OBJECT
  public:
    DealWithMouseEvent_Label(QWidget* parent = nullptr);
    ~DealWithMouseEvent_Label();
    void setDefPicture(const QString& picturePath);
    void setMovePicture(const QString& picturePath);
    void setClickPicture(const QString& picturePath);
  Q_SIGNALS:
    void leftButtonReleased();
  protected:
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    // variable
    QPixmap mDefPicture;
    QPixmap mMovePicture;
    QPixmap mClickPicture;
  };

  /*
   * 子类 带有处理鼠标事件的标签类(不自动更改图片)
   */
  class EXPORT DealWithMouseEventEx_Label : public Label {
    Q_OBJECT
  public:
    DealWithMouseEventEx_Label(QWidget* parent = nullptr);
    ~DealWithMouseEventEx_Label();
  Q_SIGNALS:
    void leftButtonReleased();
  protected:
    //void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    //void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    // variable
  };

  /*
   * 子类 展开的状态栏(模仿IVMS4200展开的状态栏样式)类
   */
  class EXPORT IVMS4200ExpandStatusBar_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ExpandStatusBar_Widget(QWidget* parent = nullptr);
    ~IVMS4200ExpandStatusBar_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    IVMS4200StatusBar_Widget* statusBar() const;
    Widget* contentArea() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QVBoxLayout* mMainLayout;
    QHBoxLayout* mHLayout0;
    QHBoxLayout* mHLayout1;
    Widget* mStatusBar;
    Widget* mContentArea;
  };

  /*
   * 子类 展开状态栏标签类
   */
  class EXPORT IVMS4200ExpandStatusBar_Label : public DealWithMouseEvent_Label {
    Q_OBJECT
  public:
    IVMS4200ExpandStatusBar_Label(QWidget* parent = nullptr);
    ~IVMS4200ExpandStatusBar_Label();

  protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  };

  /*
   * 子类 内容区首页
   */
  class EXPORT IVMS4200ContentAreaHome_Frame : public Frame {
  //class EXPORT IVMS4200ContentAreaHome_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ContentAreaHome_Frame(QWidget* parent = nullptr);
    ~IVMS4200ContentAreaHome_Frame();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    //QSplitter* splitter() const;
    IVMS4200ContentAreaHomeLeft_Widget* leftContentArea() const;
    IVMS4200ContentAreaHomeRight_Widget* rightContentArea() const;
    Label* separate() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QHBoxLayout* mMainLayout;
    QHBoxLayout* mLeftContentAreaLayout;
    QHBoxLayout* mSeparateLayout;
    QHBoxLayout* mRightContentAreaLayout;
    //QSplitter* mSplitter;
    Widget* mLeftContentArea;
    Label* mSeparate;
    Widget* mRightContentArea;
  };

  /*
   * 子类 内容区首页左边区域
   */
  class EXPORT IVMS4200ContentAreaHomeLeft_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ContentAreaHomeLeft_Widget(QWidget* parent = nullptr);
    ~IVMS4200ContentAreaHomeLeft_Widget();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    QVBoxLayout* mainLayout() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QVBoxLayout* mMainLayout;
  };

  /*
   * 子类 内容区首页左边区域小部件(每一行为一个小部件)
   */
  class EXPORT IVMS4200ContentAreaHomeLeftWgt_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ContentAreaHomeLeftWgt_Widget(QWidget* parent = nullptr);
    ~IVMS4200ContentAreaHomeLeftWgt_Widget();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    QHBoxLayout* bottomLayout() const;
    Label* titleLabel() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QVBoxLayout* mMainLayout;
    QHBoxLayout* mTopLayout;
    QHBoxLayout* mBottomLayout;
    Label* mTitle;
  };

  /*
   * 子类 内容区首页右边区域
   */
  class EXPORT IVMS4200ContentAreaHomeRight_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ContentAreaHomeRight_Widget(QWidget* parent = nullptr);
    ~IVMS4200ContentAreaHomeRight_Widget();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    QVBoxLayout* mainLayout() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    // variable
    QVBoxLayout* mMainLayout;
  };

  /*
   * 子类 内容区首页右边区域小部件(每一行为一个小部件)
   */
  class EXPORT IVMS4200ContentAreaHomeRightWgt_Widget : public Widget {
    Q_OBJECT
  public:
    IVMS4200ContentAreaHomeRightWgt_Widget(QWidget* parent = nullptr);
    ~IVMS4200ContentAreaHomeRightWgt_Widget();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    Label* titleLabel() const;
    QVBoxLayout* bottomLayout() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QVBoxLayout* mMainLayout;
    QVBoxLayout* mTopLayout;
    QVBoxLayout* mBottomLayout;
    Label* mTitle;
  };

  /*
   * 子类 IVMS4200图标类(模仿海康IVMS4200客户端标签样式，带有文字和图片，可以调整图片的摆放位置(左、上、右、下)，显示/隐藏图片，
   * 显示/隐藏文本内容。
   */
  // 上下摆放位置
  class EXPORT IVMS4200UpDownIcon_Widget : public Widget {
  public:
    enum Direction {
      UP = 0xA0,
      DOWN,
      LEFT,
      RIGHT,
    };
  public:
    IVMS4200UpDownIcon_Widget(QWidget* parent = nullptr);
    IVMS4200UpDownIcon_Widget(Direction direction, QWidget* parent = nullptr);
    ~IVMS4200UpDownIcon_Widget();
    void setDirection(Direction direction);
    void setTextAlignment(Qt::Alignment alignment);
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* picture() const;
    Label* text() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    QBoxLayout* mMainLayout;
    QHBoxLayout* mPictureLayout;
    QHBoxLayout* mTextLayout;
    Label* mPicture;
    Label* mText;
  };

  /*
   * 子类 IVMS4200图标类
   */
  // 左右摆放位置
  class EXPORT IVMS4200LeftRightIcon_Widget : public IVMS4200UpDownIcon_Widget {
  public:
    IVMS4200LeftRightIcon_Widget(Direction direction = LEFT, QWidget* parent = nullptr);
    ~IVMS4200LeftRightIcon_Widget();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    void setDirection(Direction direction);
  protected:
    void initWindow();
    void initLayout();
    void init();
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  };

  /*
   * 子类 通用标签类(组合的形式，把需要的小部件组合成一个新的展示类，抽象为标签类)
   */
  class EXPORT UniversalLabel_Frame : public Frame {
  public:
    UniversalLabel_Frame(QWidget* parent = nullptr);
    ~UniversalLabel_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    QHBoxLayout* layout() const;
  Q_SIGNALS:
    void leftButtonReleased(const QString productName);
  protected:
    void initWindow();
    void initLayout();
    void init();
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    QBoxLayout* mMainLayout;
  };

  /*
   * 子类 单一标签类(IVMS4200主预览窗口左边小部件标题栏中显示的单一标签类)
   */
  class EXPORT SingleLabel_Frame : public UniversalLabel_Frame {
  public:
    SingleLabel_Frame(QWidget* parent = nullptr);
    ~SingleLabel_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    DealWithMouseEventEx_Label* label() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    Label* mLabel;
  };

  /*
   * 子类 清除输入控件内容类
   */
  class ClearContentWidget_Label : public DealWithMouseEvent_Label {
  public:
    ClearContentWidget_Label(Product* widget, QWidget* parent = nullptr);
    ~ClearContentWidget_Label();
  protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  protected:
    Product* mWidget;
  };

  /*
   * 子类 搜索按钮类
   */
  class Search_Label : public DealWithMouseEvent_Label {
  public:
    Search_Label(QWidget* parent = nullptr);
    ~Search_Label();
  protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  };

  /*
   * 子类 搜索框
   */
  class Search_Frame : public Frame {
    Q_OBJECT
  public:
    Search_Frame(QWidget* parent = nullptr);
    ~Search_Frame();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    QLineEdit* content() const;
    DealWithMouseEvent_Label* close() const;
    DealWithMouseEvent_Label* search() const;
  public Q_SLOTS:
    void contentEdited(const QString& text);
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    LineEdit* mContent;
    DealWithMouseEvent_Label* mClose;
    DealWithMouseEvent_Label* mSearch;
  };

  /*
   * 子类 响应鼠标事件的标签的集合展示小部件类
   */
  class OperatorsHorizontal_Frame : public Frame {
  public:
    OperatorsHorizontal_Frame(QWidget* parent = nullptr);
    ~OperatorsHorizontal_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    QHBoxLayout* mainLayout() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
  };

  /*
   * 子类 树控件顶级项目标签类(树控件顶级项目标签类把顶级项目的展示抽象为标签表达)
   */
  class TreeTopLevelItem_Label : public UniversalLabel_Frame {
  public:
    TreeTopLevelItem_Label(QWidget* parent = nullptr);
    ~TreeTopLevelItem_Label();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
    DealWithMouseEvent_Label* collapseExpand() const;
    Label* icon() const;
    Label* content() const;
    OperatorsHorizontal_Frame* operating() const;
    QHBoxLayout* mainLayout() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    Label* mCollapseExpand;
    Label* mIcon;
    Label* mContent;
    Frame* mOperating;
  };

  /*
   * 子类 树控件子项目标签类
   */
  class TreeChildLevelItem_Label : public TreeTopLevelItem_Label {
  public:
    TreeChildLevelItem_Label(QWidget* parent = nullptr);
    ~TreeChildLevelItem_Label();
    virtual void setupUi(QSharedPointer<const Protocol> protocol);
  protected:
    void initWindow();
    void initLayout();
    void init();
  };

  /*
   * 子类 内容区样式模板1
   */
  class EXPORT IVMS4200ContentAreaStyleModel_Frame : public Frame {
    Q_OBJECT
  public:
    IVMS4200ContentAreaStyleModel_Frame(QWidget* parent = nullptr);
    ~IVMS4200ContentAreaStyleModel_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    IVMS4200MainPreviewLeftWgt_Frame* leftWgt() const;
    IVMS4200MainPreviewMidWgt_Frame* midWgt() const;
    IVMS4200MainPreviewRightWgt_Frame* rightWgt() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    Frame* mLeftWgt;
    Frame* mMidWgt;
    Frame* mRightWgt;
  };

  /*
   * 子类 主预览窗口左边小部件类
   */
  class EXPORT IVMS4200MainPreviewLeftWgt_Frame : public Frame {
    Q_OBJECT
  public:
    IVMS4200MainPreviewLeftWgt_Frame(QWidget* parent = nullptr);
    ~IVMS4200MainPreviewLeftWgt_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    IVMS4200TitleWgt_Frame* title() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    Frame* mTitle;
    QStackedWidget* mContentArea;
  };

  /*
   * 子类 IVMS4200主预览窗口中左边小部件中的标题类
   */
  class EXPORT IVMS4200TitleWgt_Frame : public Frame {
    Q_OBJECT
  public:
    IVMS4200TitleWgt_Frame(QWidget* parent = nullptr);
    ~IVMS4200TitleWgt_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    QHBoxLayout* mainLayout() const;
    SingleLabel_Frame* title1() const;
    SingleLabel_Frame* title2() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    UniversalLabel_Frame* mTitle1;
    UniversalLabel_Frame* mTitle2;
  };

  /*
   * 子类 格子视图
   */
  class EXPORT LatticeView_Frame : public Frame {
    Q_OBJECT
  public:
    LatticeView_Frame(QWidget* parent = nullptr);
    ~LatticeView_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    QStackedWidget* widgets() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    QStackedWidget* mWgts;
  };

  /*
   * 子类 IVMS4200主预览窗口右边窗口底边的状态栏
   */
  class EXPORT IVMS4200MainPreviewStatusBar_Frame : public Frame {
    Q_OBJECT
  public:
    IVMS4200MainPreviewStatusBar_Frame(QWidget* parent = nullptr);
    ~IVMS4200MainPreviewStatusBar_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* label1() const;
    Label* label2() const;
    Label* label3() const;
    Label* label4() const;
    Label* label5() const;
    Label* label6() const;
    Label* label7() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    Label* mLabel1;
    Label* mLabel2;
    Label* mLabel3;
    Label* mLabel4;
    Label* mLabel5;
    Label* mLabel6;
    Label* mLabel7;
  };

  /*
   * 子类 IVMS4200主预览窗口中间小部件类(那个可以隐藏左这显示区域的按钮)
   */
  class EXPORT IVMS4200MainPreviewMidWgt_Frame : public Frame {
    Q_OBJECT
  public:
    IVMS4200MainPreviewMidWgt_Frame(QWidget* parent = nullptr);
    ~IVMS4200MainPreviewMidWgt_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    Label* label() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    Label* mLabel;
  };

  /*
   * 子类 IVMS4200主预览窗口右边小部件类
   */
  class EXPORT IVMS4200MainPreviewRightWgt_Frame : public Frame {
    Q_OBJECT
  public:
    IVMS4200MainPreviewRightWgt_Frame(QWidget* parent = nullptr);
    ~IVMS4200MainPreviewRightWgt_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    LatticeView_Frame* contentArea() const;
    IVMS4200MainPreviewStatusBar_Frame* statusBar() const;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    Frame* mContentArea;
    Frame* mStatusBar;
  };

  /*
   * 子类 视频展示类
   */
  class EXPORT VideoShow_Frame : public Frame {
    Q_OBJECT
  public:
    VideoShow_Frame(QWidget* parent = nullptr);
    ~VideoShow_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
    void initLayout();
    void init();
  };

  /*
   * 子类 宫格展示
   */
  class EXPORT Lattice_Frame : public Frame {
    Q_OBJECT
  public:
    Lattice_Frame(const int row, const int column, QWidget* parent = nullptr);
    ~Lattice_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QLayout* mMainLayout;
    QHash<const QString, Frame*> mWgts;
    const int mRow;
    const int mColumn;
  };


  /*
   * 子类 目录项目类
   */
  class DirectoryItem_Frame : public UniversalLabel_Frame {
  public:
    DirectoryItem_Frame(QWidget* parent = nullptr);
    ~DirectoryItem_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  Q_SIGNALS:
    void directoryItemClicked();
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    Label* mLabel;
  };

  /*
   * 子类 目录控件类(模仿IVMS4200客户端目录控件)
   */
  class DirectoryControl_Frame : public Frame {
  public:
    DirectoryControl_Frame(QWidget* parent = nullptr);
    ~DirectoryControl_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
    // 如果已经添加过目录项目，必须先删除然后才能再次添加。
    void setDirectoryItem(DirectoryItem_Frame* item);
    DirectoryItem_Frame* directoryItem() const;
    void delDirectoryItem();
    void addItem(Frame* item);
    void delItem(Frame* item);
    Frame* item(const QString name) const;
  public Q_SLOTS:
    void directoryItemClicked();
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    QBoxLayout* mMainLayout;
    QHash<const QString, Frame*> mItems;
    DirectoryItem_Frame* mDirectoryItem;
  };

  /*
   * 子类 目录标签类
   */
  class DirectoryLabel_Frame : public UniversalLabel_Frame {
    Q_OBJECT
  public:
    DirectoryLabel_Frame(QWidget* parent = nullptr);
    ~DirectoryLabel_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    Label* mIcon;
    Label* mContent;
  };

  /*
   * 子类 目录标签类(带有子级标签)
   */
  class DirectoryLabelEx_Frame : public DirectoryLabel_Frame {
  public:
    DirectoryLabelEx_Frame(QWidget* parent = nullptr);
    ~DirectoryLabelEx_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    Label* mExpand;
  };

  /*
   * 子类 目录标签类(只显示内容)
   */
  class DirectoryLabelContent_Frame : public UniversalLabel_Frame {
  public:
    DirectoryLabelContent_Frame(QWidget* parent = nullptr);
    ~DirectoryLabelContent_Frame();
    void setupUi(QSharedPointer<const Protocol> protocol) Q_DECL_OVERRIDE;
  protected:
    void initWindow();
    void initLayout();
    void init();
  protected:
    Label* mContent;
  };

}



Q_DECLARE_METATYPE(QVector<Jinhui::Channel_Frame*>)

#endif // PARSER_H
