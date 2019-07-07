#ifndef FACTORY_H
#define FACTORY_H

#include "product.h"

#include <QObject>
#include <QSharedPointer>

namespace Jinhui {

  // Forward declaration
  class Product;

  // func pointer
  typedef void (*DoDelete)(Product* obj);

  /*
   * 工厂方法模式
   */
  template<class theProduct, DoDelete deleter = Product::doDelete>
  class Factory : public QObject {
  public:
    Factory(QObject* parent = nullptr);
    ~Factory() = default;
    // 工厂方法
    template<class... Args>
    QSharedPointer<Product> createProduct(Args&&... args);
  };

  // ctor
  template<class theProduct, DoDelete deleter>
  Factory<theProduct, deleter>::Factory(QObject* parent)
    :QObject(parent) {}

  template<class theProduct, DoDelete deleter>
  template<class... Args>
  QSharedPointer<Product> Factory<theProduct, deleter>::createProduct(Args&&... args) {
    return qSharedPointerDynamicCast<Product, theProduct>(QSharedPointer<theProduct>(new theProduct(std::forward<Args>(args)...), deleter));
  }

}

#endif // FACTORY_H
