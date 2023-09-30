#pragma once
#include <cpputils/logger.h>
#include <cpputils/threadpool.h>
#include <lucynet/connector.h>

#include <chrono>

class Controller {
 public:
  Controller(const std::shared_ptr<LucyNet::Connector>& connector);

  void ConnectToServer(const std::string& address, unsigned short port,
                       const std::function<void()>& onSuccess,
                       const std::function<void()>& onFailure);
  void DisconnectFromServer();

 private:
  void receivePackages();

 private:
  std::shared_ptr<LucyNet::Connector> connector;

  std::shared_ptr<LucyNet::Machine> serverMachine;
  std::shared_ptr<LucyNet::Connection> serverConnection;
};
