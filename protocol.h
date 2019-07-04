#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>
#include <QHash>
#include <QVector>

namespace Jinhui {
  /*
   * 协议类型
   */
  enum ProType {
    GTXLQX = 0x01,
    CONFIG,
  };

  /*******************************************************************************
   * 基类
   ******************************************************************************/
  /*
   * 协议
   */
  struct Protocol {
    ProType proType;
  };

  /*
   * 协议 高铁线路缺陷识别系统
   */
  typedef struct GTXLQX_Protocol : public Protocol {
    /*
     * 菜单
     */
    // 菜单项
    struct MenuItem {
      // 和具体业务逻辑相关的名字
      QString objectName;
      // XML文件中和图片相关的名字
      QString itemDefaultPicture;
      QString itemClickedPicture;
    };

    // 子菜单
    struct Submenu {
      QString objectName;
      QString hide;
      // 所有菜单项的名称
      QVector<MenuItem> itemsName;
    };
    // 顶级菜单
    struct Menu {
      QString objectName;
      QString menuPicName;
      QString menuPicWidth;
      QString menuPicHeight;
      // 子菜单
      /*
      QString subPicName;
      QString subPicWidth;
      QString subPicHeight;
      */
      //QString hide;
      //QStringList itemsName;
      Submenu subMenu;
    };

    /*
     * 通用
     */
    QString rootDirPath;
    QString picDirPath;
    /*
     * 主窗口
     */
    QString rimless;
    QString menubar;
    QString statusbar;
    QString mainMinWidth;
    QString mainMinHeight;
    QString mainBackgroundCol;
    /*
     * 标题
     */
    QString titlePicName;
    QString titleMinWidgetWidth;
    QString titleMinWidgetHeight;
    /*
     * 标题标签
     */
    QString mousetracking;
    // 最小化
    QString minPicDefault;
    QString minPicMoved;
    QString minWidgetMinWidth;
    QString minWidgetMinHeight;
    // 最大化
    // 窗口正常显示时
    QString normalPicDefault;
    QString normalPicMoved;
    QString normalWidgetMinWidth;
    QString normalWidgetMinHeight;
    // 窗口最大化显示时
    QString maxPicDefault;
    QString maxPicMoved;
    QString maxWidgetMinWidth;
    QString maxWidgetMinHeight;
    // 关闭
    QString shutPicDefault;
    QString shutPicMoved;
    QString shutWidgetMinWidth;
    QString shutWidgetMinHeight;

    /*
     * 门脸
     */
    QString doorPicName;
    QString doorPicWidth;
    QString doorPicHeight;
    /*
     * 所有的菜单(xml解析菜单栏中的菜单时是顺序解析的，因为菜单栏样式是从上到下的，所以索引0就是第一个菜单，依次类推)
     */
    QVector<Menu> menus;

    /*
     * 布局
     */
    QString separator;
    // 主窗口
    QString mainwindowContentsMargins;
    QString mainwindowSpacing;
    // 以下调整的都是布局在主窗口布局中的表现(下面这些布局全是主窗口中的小布局)
    // 标题栏
    QString titlebarContentsMargins;
    QString titlebarSpacing;
    QString titlebarStretch;
    // 门脸
    QString doorfaceContentsMargins;
    QString doorfaceSpacing;
    QString doorfaceStretch;
    // 菜单和内容区
    QString menuContentsMargins;
    QString menuContentSpacing;
    QString menuContentStretch;
    // 以下调整的是具体的小部件在加入到具体小布局中的表现
    // 菜单栏
    QString menubarStretch;
    QString menubarAlignment;
    // 内容区
    QString contentStretch;
    QString contentAlignment;

  } GTXLQXPro;

  /*
   * 协议 配置文件
   */
  typedef struct Config_Protocol : public Protocol {
    /*
     * 语言
     */
    typedef struct Language {
      QString prefix;
      QString filename;
      QString suffix;
    } Lan;

    /*
     * 通用
     */
    QString rootDirPath;
    QString traDirPath;
    /*
     * 所有的语言
     */
    QHash<QString, Lan> languages;
    /*
     * 数据库
     */
    QString hostName;
    QString databaseName;
    QString tableName;
    QString userName;
    QString userPassword;
  } ConfigPro;

  /*
   * 数据库中表的类型对应不同的数据表
   */
  enum DatabaseTable_Type {
    INVALID = 0x70,
    GTXLQX_Table,
  };

  /*
   * 不同数据库数据表每条记录类型
   */
  struct RecordType {
    DatabaseTable_Type type;
  };

  /*******************************************************************************
   * 子类
   ******************************************************************************/
  /*
   * 高铁线路缺陷数据表记录类型
   */
  struct GTXLQX_Record : public RecordType {
    int index;
    QString lineName;
    QString lineDirection;
    QString exportState;
    QString defectType;
    QString defectName;
    QString picturePath;
  };

}

#endif // PROTOCOL_H
