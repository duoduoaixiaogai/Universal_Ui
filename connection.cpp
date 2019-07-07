/*******************************************************************************
* Description: 连接类(各种连接的抽象)
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#include "product.h"
#include "exception.h"

#include <QSqlError>

namespace Jinhui {
  /*
   * Connection
   */
  // cotr
  Connection::Connection(const QString& connectionName)
    :mConnectionName(connectionName) {}

  const QString Connection::getConnectionName() const {
    return mConnectionName;
  }

  /*
   * Database_Connection
   */
  // cotr
  Database_Connection::Database_Connection(const QString& driver, const QString& connectionName)
    :Connection(connectionName)
    ,mDriver(driver) {}

  Database_Connection::~Database_Connection() {
    // 还没有想好怎么解决删除连接
    //QSqlDatabase::removeDatabase(mConnectionName);
  }

  void Database_Connection::openConnection() {}

  /*
   * Mysql_Connection
   */
  // cotr
  Mysql_Connection::Mysql_Connection(QSharedPointer<const Protocol> protocol)
    :Database_Connection(QLatin1String("QMYSQL"), QLatin1String("Mysql"))
    ,mProtocol(protocol) {}

  void Mysql_Connection::openConnection() {
    QSharedPointer<const ConfigPro> pro = qSharedPointerCast<const ConfigPro, const Protocol>(mProtocol);

    QSqlDatabase db = QSqlDatabase::addDatabase(mDriver, mConnectionName);
    db.setHostName(pro->hostName);
    db.setDatabaseName(pro->databaseName);
    db.setUserName(pro->userName);
    db.setPassword(pro->userPassword);
    try {
      if (!db.open()) {
        throw ConnectionFailed_Database();
      }
    } catch (DatabaseException& ex) {
      QString msg = ex.what();
      msg.append("  Error content: ")
          .append(db.lastError().text());
      ex.writeLogError(msg);
      ex.showMessage(nullptr, MessageLevel::ERROR, msg);
    }
  }

}
