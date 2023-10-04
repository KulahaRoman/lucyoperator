#pragma once
#include <cpputils/logger.h>
#include <lucynet/packagedispatcher.h>

class OperatorDispatcher : public LucyNet::PackageDispatcher {
 public:
  void DispatchPackage(
      const std::shared_ptr<LucyNet::Package>& package,
      const std::shared_ptr<LucyNet::Connection>& connection) override;
};
