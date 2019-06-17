#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QSharedPointer>

namespace Jinhui {

  // Forward declaration
  class Product;

  /*
   *  工厂方法模式
   */
  template<class theProduct>
  class Factory : public QObject {
  public:
      Factory(QObject *parent = nullptr);
      ~Factory() = default;
      // 工厂方法
      virtual QSharedPointer<Product> createProduct();
  };
}

#endif // FACTORY_H
