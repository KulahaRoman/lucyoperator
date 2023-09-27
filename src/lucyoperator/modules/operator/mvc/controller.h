#pragma once
#include <cpputils/logger.h>
#include <lucynet/connector.h>

#include <chrono>

constexpr auto RECONNECT_PERIOD = std::chrono::seconds(5);

class Controller {
 public:
  Controller(const std::shared_ptr<LucyNet::Connector>& connector);

  void OnConnectButtonPressed(const std::string& address, unsigned short port);
  void OnDisconnectButtonPressed();

 private:
  std::shared_ptr<LucyNet::Connector> connector;
  std::shared_ptr<LucyNet::Connection> connection;
};
