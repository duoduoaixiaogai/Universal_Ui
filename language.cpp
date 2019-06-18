#include "product.h"
#include "common.h"
#include "protocol.h"
#include "exception.h"

#include <QLocale>

namespace Jinhui {
  /*
   * Language
   */
  // ctor
  Language::Language(QObject* parent)
    :QObject(parent)
    ,mCurrentLan(INVALID)
    ,mChinese("Chinese") {
    loadTranslationFiles();
  }

  // protected
  // load translation files
  void Language::loadTranslationFiles() {
    ConfigParser configPar;
    configPar.parse(getConfigFilePath());
    QSharedPointer<const Protocol> protocol = configPar.getProtocol();
    // config配置文件
    if (ProType::CONFIG == protocol->proType) {
      QSharedPointer<const ConfigPro> configPro = qSharedPointerCast<const ConfigPro, const Protocol>(protocol);
      try {
        if (!configPro) {
          throw DowncastProtocolConversion();
        }
      } catch (ProtocolException& ex) {
        const QString msg = ex.what();
        ex.writeLogError(msg);
        ex.showMessage(nullptr, MessageLevel::ERROR, msg);
      }

      mRootDirPath = configPro->rootDirPath;
      mTraDirPath = configPro->traDirPath;
      mLanguages = configPro->languages;
    }
  }

  // private
  // the language name string is converted to the enum type of the laguage
  Language::LanTypes Language::lanNameStrToLanNameEnum(const QString& name) {
    LanTypes lanType = INVALID;

    if (mChinese == name) {
      lanType = LanTypes::CHINESE;
    }

    return lanType;
  }

  // the enum type of the language is converted to the name string of the language
  const QString Language::lanNameEnumToLanNameStr(Language::LanTypes lanType) const {
    QString lanName;

    switch (lanType) {
      case INVALID:
        // do nothing
        break;
      case CHINESE:
        lanName = QLatin1String("Chinese");
        break;
    }

    return lanName;
  }

  /*
   * SimplifiedChinese
   */
  // ctor
  SimplifiedChinese::SimplifiedChinese(QObject* parent)
    :Language(parent) {
    // ? 下面这句话为何不能放到成员初始化列表中 难道基类受保护的成员变量不能在子类的成员初始化列表中初始化吗
    mCurrentLan = CHINESE;

    ConfigPro::Lan lan = mLanguages[lanNameEnumToLanNameStr(mCurrentLan)];
    try {
      if (!mTranslator.load(QLocale(), lan.filename, lan.prefix, mTraDirPath, lan.suffix)) {
        throw LoadTranslationFile();
      }
      if (qApp->removeTranslator(&mTranslator)) {
        throw delTranslationFile();
      }
      if (qApp->installTranslator(&mTranslator)) {
        throw addTranslationFile();
      }
    } catch (LanguageException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
    }
  }

}
