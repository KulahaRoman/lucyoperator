#pragma once
#include <cpputils/logger.h>
#include <lucynet/authrequestpackage.h>
#include <lucynet/authresponsepackage.h>
#include <lucynet/connector.h>

#include <chrono>

constexpr auto RECONNECT_PERIOD = std::chrono::seconds(5);

class Controller {
 public:
  Controller(const std::shared_ptr<LucyNet::Connector>& connector);

  bool ConnectToServer(const std::string& address, unsigned short port);
  bool DisconnectFromServer();

 private:
  std::shared_ptr<LucyNet::Connector> connector;

  std::shared_ptr<LucyNet::Machine> serverMachine;
  std::shared_ptr<LucyNet::Connection> serverConnection;
};
