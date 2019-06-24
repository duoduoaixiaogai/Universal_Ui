#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QSharedPointer>

namespace Jinhui {

  // Forward declaration
  class Product;

  /*
   * 工厂方法模式
   */
  template<class theProduct>
  class Factory : public QObject {
  public:
    Factory(QObject* parent = nullptr);
    ~Factory() = default;
    // 工厂方法
    template<class... Args>
    QSharedPointer<Product> createProduct(Args&&... args);
  };

  // ctor
  template<class theProduct>
  Factory<theProduct>::Factory(QObject* parent)
    :QObject(parent) {}

  template<class theProduct>
  template<class... Args>
  QSharedPointer<Product> Factory<theProduct>::createProduct(Args&&... args) {
    return qSharedPointerDynamicCast<Product, theProduct>(QSharedPointer<theProduct>(new theProduct(std::forward<Args>(args)...)));
  }

}

#endif // FACTORY_H
