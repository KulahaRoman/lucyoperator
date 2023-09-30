#include "controller.h"

Controller::Controller(
    const std::shared_ptr<LucyNet::Connector>& connector,
    const std::shared_ptr<LucyNet::PackageDispatcher>& dispatcher)
    : connector(connector), packageDispatcher(dispatcher) {}

void Controller::ConnectToServer(const std::string& address,
                                 unsigned short port,
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

        DisconnectFromServer();
      });
}

void Controller::DisconnectFromServer() {
  serverMachine.reset();
  serverConnection.reset();
}

void Controller::receivePackages() {
  serverConnection->ReceivePackage(
      [this](const auto& package) {
        packageDispatcher->DispatchPackage(package, serverConnection);
        receivePackages();
      },
      [this](const auto& exc) {
        CppUtils::Logger::Information("Disconnected from server.");
      });
}
