#include "controller.h"

Controller::Controller(const std::shared_ptr<LucyNet::Connector>& connector)
    : connector(connector) {}

void Controller::OnConnectButtonPressed(const std::string& address,
                                        unsigned short port) {
  CppUtils::Logger::Information("Connecting to {}:{}", address, port);
  connector->Connect(address, port);
  CppUtils::Logger::Information("Connected to {}:{}", address, port);
}

void Controller::OnDisconnectButtonPressed() {
  CppUtils::Logger::Information("Disconnecting...");
}
