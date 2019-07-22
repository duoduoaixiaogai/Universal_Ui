#include "include/signalsrelay.h"

namespace Jinhui {
  /*
   * SignalRelay
   */
  QSharedPointer<SignalsRelay> SignalsRelay::mInstance;
  // cotr
  SignalsRelay::SignalsRelay(QObject* parent)
    :QObject(parent) {

  }

  SignalsRelay::~SignalsRelay() {}

  QSharedPointer<SignalsRelay> SignalsRelay::getInstance() {
    if (!mInstance) {
      mInstance = QSharedPointer<SignalsRelay>(new SignalsRelay);
    }
    return mInstance;
  }

}
