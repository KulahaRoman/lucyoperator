#include "controller.h"

Controller::Controller(const std::shared_ptr<LucyNet::Connector>& connector)
    : connector(connector) {}

void Controller::OnConnectButtonPressed(const std::string& address,
                                        unsigned short port) {
  try {
    CppUtils::Logger::Information("Connecting to {}:{}", address, port);
    connection = connector->Connect(address, port);
    CppUtils::Logger::Information("Connected to {}:{}", address, port);
  } catch (const std::exception& ex) {
    CppUtils::Logger::Error("{}", ex.what());
  }
}

void Controller::OnDisconnectButtonPressed() {
  try {
    CppUtils::Logger::Information("Disconnecting...");
    connection.reset();
    CppUtils::Logger::Information("Disconnected.");
  } catch (const std::exception& ex) {
    CppUtils::Logger::Error("{}", ex.what());
  }
}
