#pragma once
#include <cpputils/logger.h>
#include <lucynet/handler.h>
#include <lucynet/targetsresponse.h>

#include "models/targetslist.h"
#include "viewcontroller.h"

class TargetsHandler : public LucyNet::Handler {
 public:
  TargetsHandler();
  TargetsHandler(const std::shared_ptr<View>& view);

  void SetView(const std::shared_ptr<View>& view);

  void Handle(const std::shared_ptr<LucyNet::Package>& package,
              const std::shared_ptr<LucyNet::Connection>& connection) override;

 private:
  std::shared_ptr<View> view;
};
