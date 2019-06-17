#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>

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
  struct Menu {
    // 顶级菜单
    QString picNameMenu;
    QString picWidthMenu;
    QString picHeightMenu;
    // 子菜单
    QString picNameSub;
    QString picWidthSub;
    QString picHeightSub;
  };

  typedef struct GTXLQX_Protocol : public Protocol {
    // 通用
    QString rootDirPath;
    QString picDirPath;
    // 标题
    QString picNameTitle;
    QString picWidthTitle;
    QString picHeightTitle;
    // 门脸
    QString picNameDoor;
    QString picWidthDoor;
    QString picHeightDoor;
    // 菜单
    Menu menus;
  } GTXLQXPro;

  /*
   * 协议 配置文件
   */
  typedef struct Config_Protocol : public Protocol {
    // 通用
    QString rootDirPath;
    QString traDirPath;
    // 语言
    // 选择哪种语言
    QString select;
    QString prefix;
    QString filename;
    QString suffix;
  } ConfigPro;
}

#endif // PROTOCOL_H
