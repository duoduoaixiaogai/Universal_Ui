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
    struct Menu {
      // 顶级菜单
      QString menuPicName;
      QString menuPicWidth;
      QString menuPicHeight;
      // 子菜单
      QString subPicName;
      QString subPicWidth;
      QString subPicHeight;
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
     * 所有的菜单
     */
    QVector<Menu> menus;
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
  } ConfigPro;

}

#endif // PROTOCOL_H
