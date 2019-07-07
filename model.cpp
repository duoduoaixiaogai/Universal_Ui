/*******************************************************************************
* Description: 模型类(Model/View架构中的模型抽象类)，封装了对数据的操作。
* Author: Niu yi qun
* Creation date: 2019/6/28
* Last modified person: Niu yi qun
* Last modified date: 2019/6/28
******************************************************************************/
#include "product.h"

namespace Jinhui {
  /*
   * Model
   */
  // cotr
  Model::Model(QObject* parent)
    :QAbstractItemModel(parent) {}

  Model::~Model() {}

  int Model::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return mColumnsName.count();
  }

  QVariant Model::data(const QModelIndex& index, int role) const {
    if (index.row() > mRecords.count() || index.column() > mColumnsName.count()) {
      return QVariant();
    }

    if (role == Qt::DisplayRole) {
      return mRecords.at(index.row()).at(index.column());
    } else if (role == Qt::TextAlignmentRole) {
      return Qt::AlignCenter;
    } else if (role == Qt::BackgroundRole) {
      return QBrush(QColor(0, 255, 0));
    }

    return QVariant();
  }

  Qt::ItemFlags Model::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
      return 0;
    }

    return Qt::ItemIsEnabled | QAbstractItemModel::flags(index);
  }

  QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (Qt::Horizontal == orientation && Qt::DisplayRole == role) {
      if (section >= mColumnsName.count()) {
        return QVariant();
      }
      return mColumnsName.at(section);
    } else if (Qt::Vertical == orientation && Qt::DisplayRole == role) {
      return section;
    }

    return QVariant();
  }

  QModelIndex Model::index(int row, int column, const QModelIndex& parent) const {
    return createIndex(row, column, parent.internalId());
  }

  bool Model::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
  }

  QModelIndex Model::parent(const QModelIndex &index) const {
    Q_UNUSED(index);
    return QModelIndex();
  }

  bool Model::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
  }

  int Model::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mRecords.count();
  }

  void Model::updateHeader(ColumnsName& columnsName) {
    mColumnsName = columnsName;
  }


  const ColumnsName Model::getHeader() const {
    return mColumnsName;
  }

  /*
   * GTXLQX_Model
   */
  // cotr
  GTXLQX_Model::GTXLQX_Model(QObject* parent)
    :Model(parent) {
    mColumnsName << tr("Indexs")
                 << tr("LineName")
                 << tr("LineDirection")
                 << tr("ExportState")
                 << tr("DefectType")
                 << tr("DefectName")
                 << tr("PicturePath");
  }

  GTXLQX_Model::~GTXLQX_Model() {}

  void GTXLQX_Model::showReviewResult(QList<Record>& records) {
    if (!mRecords.isEmpty()) {
      removeRows(0, mRecords.count());
      mRecords.clear();
    }

    mRecords.swap(records);
    insertRows(0, mRecords.count());
  }
}
