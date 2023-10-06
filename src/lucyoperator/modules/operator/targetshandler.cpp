#include "targetshandler.h"

TargetsHandler::TargetsHandler() {}

TargetsHandler::TargetsHandler(const std::shared_ptr<View>& view)
    : view(view) {}

void TargetsHandler::SetView(const std::shared_ptr<View>& view) {
  this->view = view;
}

void TargetsHandler::Handle(
    const std::shared_ptr<LucyNet::Package>& package,
    const std::shared_ptr<LucyNet::Connection>& connection) {
  auto targetsResponse =
      std::static_pointer_cast<LucyNet::TargetsResponse>(package);
  TargetsList targetsList(targetsResponse->GetTargets());

  if (!view) {
    throw std::runtime_error(
        "TargetsHandler::Handle() failed: 'view' object doesn't exist.");
  }

  view->Update("targetsReceived", targetsList);
}
