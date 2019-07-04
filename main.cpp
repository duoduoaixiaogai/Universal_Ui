#include "mainwindow.h"
#include "log.h"
#include "factory.h"
#include "product.h"
#include "common.h"

#include <QApplication>

using namespace Jinhui;

int main(int argc, char *argv[])
{
  // 加载日志模块
  Log log;

  QApplication a(argc, argv);

  // 加载配置文件模块
  QSharedPointer<const ConfigPro> configPro;
  {
    Factory<ConfigParser> factory;
    QSharedPointer<ConfigParser> gtxlqxParser = qSharedPointerDynamicCast<ConfigParser, Product>(factory.createProduct());
    gtxlqxParser->parse(getConfigFilePath());
    configPro = qSharedPointerCast<const ConfigPro, const Protocol>(gtxlqxParser->getProtocol());
  }

  // 加载语言模块
  QSharedPointer<SimplifiedChinese> lanChinese;
  {
    Factory<SimplifiedChinese> factory;
    lanChinese = qSharedPointerDynamicCast<SimplifiedChinese, Product>(factory.createProduct(configPro));
  }

  // 加载高铁线路缺陷解析模块
  QSharedPointer<const GTXLQXPro> proGTXLQX;
  {
    Factory<GTXLQX_XMLParser> factory;
    QSharedPointer<GTXLQX_XMLParser> parserGTXLQX = qSharedPointerDynamicCast<GTXLQX_XMLParser, Product>(factory.createProduct());
    parserGTXLQX->parse(getUiFilePath());
    proGTXLQX = qSharedPointerCast<const GTXLQXPro, const Protocol>(parserGTXLQX->getProtocol());
  }

  // 加载主窗口
  QSharedPointer<GTXLQX_MainWindow> mainWinGTXLQX;
  {
    Factory<GTXLQX_MainWindow, GTXLQX_MainWindow::doDeleteLater> factory;
    mainWinGTXLQX = qSharedPointerDynamicCast<GTXLQX_MainWindow, Product>(factory.createProduct(proGTXLQX, configPro));
    mainWinGTXLQX->show();
  }


  return a.exec();
}
