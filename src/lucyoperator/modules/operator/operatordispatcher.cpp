#include "operatordispatcher.h"

void OperatorDispatcher::DispatchPackage(
    const std::shared_ptr<LucyNet::Package>& package,
    const std::shared_ptr<LucyNet::Connection>& connection) {
  auto lock = std::unique_lock<std::mutex>(mx);

  try {
    auto handler = handlers.at(package->GetType());
    handler->Handle(package, connection);
  } catch (const std::exception& exc) {
    CppUtils::Logger::Error("OperatorDispatcher::DispatchPackage() failed: {}",
                            exc.what());
  }
}
