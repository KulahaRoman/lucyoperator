#include "controller.h"

Controller::Controller(const std::shared_ptr<LucyNet::Connector>& connector)
    : connector(connector) {}

void Controller::ConnectToServer(const std::string& address,
                                 unsigned short port,
                                 const std::function<void()>& onSuccess,
                                 const std::function<void()>& onFailure) {
  CppUtils::Logger::Information("Connecting to {}:{}", address, port);
  connector->Connect(
      address, port,
      [this, onSuccess, address, port](const auto& connectionBundle) {
        serverMachine = connectionBundle->GetMachine();
        serverConnection = connectionBundle->GetConnection();

        CppUtils::Logger::Information("Connected to {}:{}", address, port);

        if (onSuccess) {
          onSuccess();
        }
      },
      [this, onFailure, address, port](const auto& exc) {
        serverMachine.reset();
        serverConnection.reset();

        CppUtils::Logger::Error("Failed to connected to {}:{}", address, port);

        if (onFailure) {
          onFailure();
        }
      });
}

void Controller::DisconnectFromServer() {
  CppUtils::Logger::Information("Disconnecting...");

  serverMachine.reset();
  serverConnection.reset();

  CppUtils::Logger::Information("Disconnected.");
}
