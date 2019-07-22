#include "common.h"
#include <QCoreApplication>
#include <QLatin1String>

namespace Jinhui {
  // get config file path
  static QString getConfigFilePath() {
    return qApp->applicationDirPath()
        .append('/')
        .append("config.xml");
  }

  // get ui file path
  static QString getUiFilePath() {
    return qApp->applicationDirPath()
        .append('/')
        .append("ui.xml");
  }
}
