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
  //MainWindow w;
  //w.show();

  // 加载语言模块
  {
    Factory<SimplifiedChinese> factory;
    factory.createProduct();
  }

  // 加载高铁线路缺陷解析模块
  {
    Factory<XMLParserGTXLQX> factory;
    QSharedPointer<XMLParserGTXLQX> parser = qSharedPointerDynamicCast<XMLParserGTXLQX, Product>(factory.createProduct());
    parser->parse(getUiFilePath());
    QSharedPointer<const Protocol> protocol = parser->getProtocol();
  }

  return a.exec();
}
