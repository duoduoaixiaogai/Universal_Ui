#include "product.h"
#include "common.h"
#include "protocol.h"
#include "exception.h"

#include <QLocale>

namespace Jinhui {
  /*
   * Language
   */
  // Static variable initalize out of class
  char Language::mCnCount = 0;

  // ctor
  Language::Language()
    :Product()
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
  SimplifiedChinese::SimplifiedChinese()
    :Language() {
    // ? 下面这句话为何不能放到成员初始化列表中 难道基类受保护的成员变量不能在子类的成员初始化列表中初始化吗
    mCurrentLan = CHINESE;

    ConfigPro::Lan lan = mLanguages[lanNameEnumToLanNameStr(mCurrentLan)];
    try {
      QString relativeDir = getExeInDirPath()
                            .append('/')
                            .append(mTraDirPath);
      // 不包含前缀 调用包含绝对文件名的加载函数
      if (lan.prefix.isNull()) {
        if (!mTranslator.load(lan.filename, relativeDir)) {
          throw LoadTranslationFile();
        }
      } else {
        // 包含前缀 调用包含前缀的加载函数
        if (!mTranslator.load(QLocale(), lan.filename, lan.prefix, relativeDir, lan.suffix)) {
          throw LoadTranslationFile();
        }
      }
      // 语言计数大于1证明翻译文件已经被加载到了翻译文件列表中
      if (mCnCount) {
        if (!qApp->removeTranslator(&mTranslator)) {
          throw delTranslationFile();
        }
      }
      if (!qApp->installTranslator(&mTranslator)) {
        throw addTranslationFile();
      }
      mCnCount++;
    } catch (LanguageException& ex) {
      const QString msg = ex.what();
      ex.writeLogError(msg);
      //ex.showMessage(nullptr, MessageLevel::ERROR, msg);
    }
  }

}
