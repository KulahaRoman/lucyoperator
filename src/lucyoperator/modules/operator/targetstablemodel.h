#pragma once
#include <QAbstractTableModel>

#include "models/targetslist.h"

class TargetsTableModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  TargetsTableModel(QObject* parent = nullptr);

  void SetTargets(const TargetsList& list);
  void Clear();

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

 private:
  std::vector<std::pair<std::string, std::string>> targets;
};
