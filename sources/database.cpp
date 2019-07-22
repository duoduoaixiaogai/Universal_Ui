/*******************************************************************************
* Description: 数据库类(对不同数据库的抽象,不同数据库中都有共同的增、删、改、查功能，其他具体
* 不同的功能在不同的子类中具体实现。)
* Author: Niu yi qun
* Creation date: 2019/6/27
* Last modified person: Niu yi qun
* Last modified date: 2019/6/27
******************************************************************************/
#include "include/product.h"
#include "include/exception.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>

namespace Jinhui {
  /*
   * Database
   */
  // cotr
  Database::Database(QSharedPointer<const Protocol> protocol, const QString &connectionName)
    :mProtocol(protocol)
    ,mQuery(QSqlDatabase::database(connectionName)) {}

  void Database::insert(const QString& sql) {
    sqlExec(sql);
  }

  void Database::deleteEx(const QString& sql) {
    sqlExec(sql);
  }

  void Database::update(const QString& sql) {
    sqlExec(sql);
  }

  void Database::selectEx(const QString& sql) {
    sqlExec(sql);
  }

  void Database::commit() {}

  QVector<Record> Database::getData(const ColumnsName& columnsName) {
    QVector<Record> records;
    while (mQuery.next()) {
      auto it = columnsName.begin();
      auto end = columnsName.end();
      Record record;
      while (it != end) {
        int nameCol = mQuery.record().indexOf(*it);
        record.append(mQuery.value(nameCol).toString());
        ++it;
      }
      records.append(record);
    }
    return records;
  }

  void Database::sqlExec(const QString& sql) {
    try {
      if (!mQuery.exec(sql)) {
        throw SqlQuery_Exception();
      }
    } catch (DatabaseException& ex) {
      QSqlError err = mQuery.lastError();
      QString msg = ex.what();
      ex.writeLogWarn(msg.append(err.text()));
      ex.showMessage(nullptr, MessageLevel::WARN, msg.append(err.text()));
      return;
    }
  }

  /*
   * Mysql_Database
   */
  //int Mysql_Database::mRow = 0;
  //// cotr
  //Mysql_Database::Mysql_Database(QSqlDatabase connection, QSharedPointer<const Protocol> protocol, QObject* parent)
  //  :Database(protocol)
  //  ,QSqlTableModel(parent, connection) {
  //  init();
  //  setTableHeader();
  //}

  //Mysql_Database::~Mysql_Database() {}

  //void Mysql_Database::append_Into(const RecordType& record) {
  //  switch (record.type) {
  //    case GTXLQX_Table:
  //      appendGTXLQXRecord(record);
  //      break;
  //  }
  //  ++mRow;
  //}

  //void Mysql_Database::delete_From(const int row) {
  //  record(row).clear();
  //  --mRow;
  //  submitAll();
  //}

  //void Mysql_Database::update() {
  //  QSqlRecord record1 = record(1);
  //  QSqlField field = record1.field("LineName");
  //  field.setValue("test");
  //  field.setGenerated(false);
  //  setRecord(1, record1);
  //}

  //void Mysql_Database::selectEx() {
  //  select();
  //}

  //void Mysql_Database::commit() {
  //  submitAll();
  //}
  ////QVariant Mysql_Database::data(const QModelIndex &index, int role) const {
  ////  if (Qt::TextAlignmentRole == role) {
  ////    return Qt::AlignVCenter;
  ////  }

  ////  return QSqlTableModel::data(index, role);
  ////}

  //void Mysql_Database::init() {
  //  QSharedPointer<const ConfigPro> pro = qSharedPointerCast<const ConfigPro, const Protocol>(mProtocol);
  //  setTable(pro->tableName);
  //  setEditStrategy(QSqlTableModel::OnManualSubmit);
  //}

  //void Mysql_Database::setTableHeader() {
  //  //int fieldsCount = record().count();
  //  //for (int i = 0; i <fieldsCount; ++i) {
  //  //  setHeaderData(i, Qt::Horizontal, record().fieldName(i));
  //  //}
  //  setHeaderData(0, Qt::Horizontal, tr("index"));
  //  setHeaderData(1, Qt::Horizontal, tr("lineName"));
  //  setHeaderData(2, Qt::Horizontal, tr("lineDirection"));
  //  setHeaderData(3, Qt::Horizontal, tr("exportState"));
  //  setHeaderData(4, Qt::Horizontal, tr("defectType"));
  //  setHeaderData(5, Qt::Horizontal, tr("defectName"));
  //  setHeaderData(6, Qt::Horizontal, tr("picturePath"));
  //}

  //void Mysql_Database::appendGTXLQXRecord(const RecordType &record) {
  //  const GTXLQX_Record& gtxlqxRecord = static_cast<const GTXLQX_Record&>(record);

  //  QSqlField index(QLatin1String("Indexs"), QVariant::Int);
  //  index.setValue(gtxlqxRecord.index);
  //  //index.setGenerated(true);
  //  QSqlField lineName(QLatin1String("LineName"), QVariant::String);
  //  lineName.setValue(gtxlqxRecord.lineName);
  //  //lineName.setGenerated(true);
  //  QSqlField lineDirection(QLatin1String("LineDirection"), QVariant::String);
  //  lineDirection.setValue(gtxlqxRecord.lineDirection);
  //  //lineDirection.setGenerated(true);
  //  QSqlField exportState(QLatin1String("ExportState"), QVariant::String);
  //  exportState.setValue(gtxlqxRecord.exportState);
  //  //exportState.setGenerated(true);
  //  QSqlField defectType(QLatin1String("DefectType"), QVariant::String);
  //  defectType.setValue(gtxlqxRecord.defectType);
  //  //defectType.setGenerated(true);
  //  QSqlField defectName(QLatin1String("DefectName"), QVariant::String);
  //  defectName.setValue(gtxlqxRecord.defectName);
  //  //defectName.setGenerated(true);
  //  QSqlField picturePath(QLatin1String("PicturePath"), QVariant::String);
  //  picturePath.setValue(gtxlqxRecord.picturePath);
  //  //picturePath.setGenerated(true);

  //  QSqlRecord record1;
  //  record1.append(index);
  //  record1.append(lineName);
  //  record1.append(lineDirection);
  //  record1.append(exportState);
  //  record1.append(defectType);
  //  record1.append(defectName);
  //  record1.append(picturePath);

  //  insertRecord(-1, record1);
  //}

  /*
   * Mysql_Database
   */
  // cotr
  MySQL_Database::MySQL_Database(QSharedPointer<const Protocol> protocol, const QString& connectionName)
    :Database(protocol, connectionName) {}

  MySQL_Database::~MySQL_Database() {}

  void MySQL_Database::selectAll() {
    QSharedPointer<const ConfigPro> pro = qSharedPointerCast<const ConfigPro, const Protocol>(mProtocol);

    selectEx(QString("select * from %1")
             .arg(pro->tableName));
  }
}
