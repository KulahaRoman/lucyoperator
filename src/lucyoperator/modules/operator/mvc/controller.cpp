#include "controller.h"

Controller::Controller(const std::shared_ptr<LucyNet::Connector>& connector)
    : connector(connector) {}

void Controller::ConnectToServer(const std::string& address,
                                 unsigned short port,
                                 const std::function<void()>& onSuccess,
                                 const std::function<void()>& onFailure) {
  connector->Connect(
      address, port,
      [this, onSuccess](const auto& connectionBundle) {
        serverMachine = connectionBundle->GetMachine();
        serverConnection = connectionBundle->GetConnection();

        CppUtils::Logger::Information(
            "Connected to the server {} ({}:{}).", serverMachine->GetName(),
            serverConnection->GetAddress(), serverConnection->GetPort());

        if (onSuccess) {
          onSuccess();
        }

        receivePackages();
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
      [this](const auto& package) { receivePackages(); },
      [this](const auto& exc) {});
}
