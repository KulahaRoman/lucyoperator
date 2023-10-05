#include "targetslist.h"

TargetsList::TargetsList() {}

TargetsList::TargetsList(
    const std::vector<
        std::pair<std::shared_ptr<LucyNet::Machine>, std::string>>& list)
    : list(list) {}

std::vector<std::pair<std::shared_ptr<LucyNet::Machine>, std::string>>
TargetsList::GetList() const {
  return list;
}

void TargetsList::SetList(
    const std::vector<
        std::pair<std::shared_ptr<LucyNet::Machine>, std::string>>& list) {
  this->list = list;
}
