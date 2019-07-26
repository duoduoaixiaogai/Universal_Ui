/*******************************************************************************
* Description: 文件类(RAII)
* Author: Niu yi qun
* Creation date: 2019/7/26
* Last modified person: Niu yi qun
* Last modified date: 2019/7/26
******************************************************************************/
#include "include/product.h"
#include "include/exception.h"

namespace Jinhui {
  /*
   * File
   */
  // cotr
  File::File(QObject* parent)
    :QFile(parent) {}

  File::File(const QString& name)
    :QFile(name) {
    try {
      if (!open(QFile::ReadOnly)) {
        throw FileExceptionOpenErr();
      }
    } catch (FileException& ex) {
      const QString msg = ex.what();
      ex.writeLogWarn(msg);
      ex.showMessage(nullptr, MessageLevel::WARN, msg);
    }
  }

  File::~File() {
    if (isOpen()) {
      close();
    }
  }

}
