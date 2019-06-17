#include "product.h"
#include

namespace Jinhui {
  /*
   * Language
   */
  // ctor
  Language::Language(QObject* parent)
    :QObject(parent) {
    loadTranslationFile();
  }

  void Language::loadTranslationFile() {

  }

  /*
   * SimplifiedChinese
   */
  // ctor
  SimplifiedChinese::SimplifiedChinese(QObject* parent)
    :Language(parent) {}

}
