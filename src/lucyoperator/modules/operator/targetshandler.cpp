#include "targetshandler.h"

TargetsHandler::TargetsHandler() {}

void TargetsHandler::Handle(
    const std::shared_ptr<LucyNet::Package>& package,
    const std::shared_ptr<LucyNet::Connection>& connection) {
  auto targetsResponse =
      std::static_pointer_cast<LucyNet::TargetsResponse>(package);
  auto targets = targetsResponse->GetTargets();

  for (const auto& [machine, address] : targets) {
    CppUtils::Logger::Information("Connected target: {} ({}).",
                                  machine->GetName(), address);
  }
}
