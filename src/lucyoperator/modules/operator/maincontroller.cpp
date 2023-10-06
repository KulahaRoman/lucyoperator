#include "maincontroller.h"

MainController::MainController(
    const std::shared_ptr<LucyNet::Connector>& connector,
    const std::shared_ptr<LucyNet::PackageDispatcher>& dispatcher)
    : connector(connector), packageDispatcher(dispatcher) {
  initializeRoutes();
}

MainController::MainController(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<LucyNet::Connector>& connector,
    const std::shared_ptr<LucyNet::PackageDispatcher>& dispatcher)
    : Controller(view), connector(connector), packageDispatcher(dispatcher) {
  initializeRoutes();
}

void MainController::receivePackages() {
  serverConnection->ReceivePackage(
      [this](const auto& package) {
        packageDispatcher->DispatchPackage(package, serverConnection);
        receivePackages();
      },
      [this](const auto& exc) {
        CppUtils::Logger::Information("Disconnected from server.");
        getView()->Update("disconnected");
        disconnect();
      });
}

void MainController::initializeRoutes() {
  RegisterRoute<ServerCredentials>(
      "connect", [this](const ServerCredentials& creds) {
        auto address = creds.GetAddress();
        auto port = creds.GetPort();

        connect(
            address, port, [this] { getView()->Update("connected"); },
            [this] { getView()->Update("disconnected"); });
      });
  RegisterRoute("disconnect", [this] {
    disconnect();
    getView()->Update("disconnected");
  });
}

void MainController::connect(const std::string& address, unsigned short port,
                             const std::function<void()>& onSuccess,
                             const std::function<void()>& onFailure) {
  connector->Connect(
      address, port,
      [this, onSuccess, onFailure](const auto& connectionBundle) {
        serverMachine = connectionBundle->GetMachine();
        serverConnection = connectionBundle->GetConnection();

        receivePackages();

        CppUtils::Logger::Information(
            "Connected to the server {} ({}:{}).", serverMachine->GetName(),
            serverConnection->GetAddress(), serverConnection->GetPort());

        auto targetsRequest = std::make_shared<LucyNet::TargetsRequest>();
        targetsRequest->SetReceiver(serverMachine);
        targetsRequest->SetSender(LucyNet::MachineHelper::GetCurrentMachine());

        serverConnection->SendPackage(
            targetsRequest,
            [this, onSuccess](const auto&) {
              if (onSuccess) {
                onSuccess();
              }
            },
            [onFailure](const auto& exc) {
              if (onFailure) {
                onFailure();
              }
            });
      },
      [this, onFailure, address, port](const auto& exc) {
        CppUtils::Logger::Error("Failed to connect the server ({}:{}).",
                                address, port);
        if (onFailure) {
          onFailure();
        }
      });
}

void MainController::disconnect() {
  serverMachine.reset();
  serverConnection.reset();
}
