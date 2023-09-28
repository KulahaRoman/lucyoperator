#include "controller.h"

Controller::Controller(const std::shared_ptr<LucyNet::Connector>& connector)
    : connector(connector) {}

bool Controller::ConnectToServer(const std::string& address,
                                 unsigned short port) {
  try {
    CppUtils::Logger::Information("Connecting to {}:{}", address, port);
    auto connectionBundle = connector->Connect(address, port);

    serverMachine = connectionBundle->GetMachine();
    serverConnection = connectionBundle->GetConnection();

    CppUtils::Logger::Information("Connected to {}:{}", address, port);
  } catch (const std::exception& ex) {
    CppUtils::Logger::Error("{}", ex.what());
    return false;
  }
  return true;
}

bool Controller::DisconnectFromServer() {
  try {
    CppUtils::Logger::Information("Disconnecting...");
    serverConnection.reset();
    CppUtils::Logger::Information("Disconnected.");
  } catch (const std::exception& ex) {
    CppUtils::Logger::Error("{}", ex.what());
    return false;
  }
  return true;
}
