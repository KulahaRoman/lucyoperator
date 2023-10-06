#include "targetstablemodel.h"

TargetsTableModel::TargetsTableModel(QObject* parent)
    : QAbstractTableModel(parent) {}

void TargetsTableModel::SetTargets(const TargetsList& list) {
  auto data = list.GetList();

  targets.resize(0);
  targets.reserve(data.size());

  for (const auto& [machine, address] : data) {
    targets.emplace_back(std::make_pair(machine->GetName(), address));
  }

  QModelIndex topLeft = this->index(0, 0);
  QModelIndex bottomRight = this->index(data.size() - 1, 1);

  emit layoutChanged();
}

int TargetsTableModel::rowCount(const QModelIndex& parent) const {
  return targets.size();
}

int TargetsTableModel::columnCount(const QModelIndex& parent) const {
  return 2;
}

QVariant TargetsTableModel::data(const QModelIndex& index, int role) const {
  auto row = index.row();
  auto col = index.column();

  switch (role) {
    case Qt::DisplayRole: {
      auto target = targets[row];

      switch (col) {
          // name
        case 0:
          return QString::fromStdString(target.first);
          // address
        case 1:
          return QString::fromStdString(target.second);
      }
    }
  }

  return QVariant();
}
