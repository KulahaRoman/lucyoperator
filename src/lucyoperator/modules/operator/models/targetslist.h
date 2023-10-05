#pragma once
#include <lucynet/machine.h>

#include <vector>

class TargetsList {
 public:
  TargetsList();
  TargetsList(const std::vector<
              std::pair<std::shared_ptr<LucyNet::Machine>, std::string>>& list);

  std::vector<std::pair<std::shared_ptr<LucyNet::Machine>, std::string>>
  GetList() const;
  void SetList(const std::vector<std::pair<std::shared_ptr<LucyNet::Machine>,
                                           std::string>>& list);

 private:
  std::vector<std::pair<std::shared_ptr<LucyNet::Machine>, std::string>> list;
};
