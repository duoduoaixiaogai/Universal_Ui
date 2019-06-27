#include "signalrelay.h"

namespace Jinhui {
  /*
   * SignalRelay
   */
  QSharedPointer<SignalRelay> SignalRelay::mInstance;
  // cotr
  SignalRelay::SignalRelay(QObject* parent)
    :QObject(parent) {

  }

  SignalRelay::~SignalRelay() {}

  QSharedPointer<SignalRelay> SignalRelay::getInstance() {
    if (!mInstance) {
      mInstance = QSharedPointer<SignalRelay>(new SignalRelay);
    }
    return mInstance;
  }

}
