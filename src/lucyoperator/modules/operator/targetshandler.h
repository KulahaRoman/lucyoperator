#pragma once
#include <cpputils/logger.h>
#include <lucynet/handler.h>
#include <lucynet/targetsresponse.h>

class TargetsHandler : public LucyNet::Handler {
 public:
  TargetsHandler();

  void Handle(const std::shared_ptr<LucyNet::Package>& package,
              const std::shared_ptr<LucyNet::Connection>& connection) override;
};
