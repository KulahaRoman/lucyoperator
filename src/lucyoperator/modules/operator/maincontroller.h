#pragma once
#include <cpputils/logger.h>
#include <cpputils/threadpool.h>
#include <lucynet/connector.h>
#include <lucynet/machinehelper.h>
#include <lucynet/packagedispatcher.h>
#include <lucynet/targetsrequest.h>

#include <chrono>

#include "viewcontroller.h"

class MainController : public Controller {
 public:
  MainController(const std::shared_ptr<LucyNet::Connector>& connector,
                 const std::shared_ptr<LucyNet::PackageDispatcher>& dispatcher);
  MainController(const std::shared_ptr<View>& view,
                 const std::shared_ptr<LucyNet::Connector>& connector,
                 const std::shared_ptr<LucyNet::PackageDispatcher>& dispatcher);

  void ConnectToServer(const std::string& address, unsigned short port,
                       const std::function<void()>& onSuccess,
                       const std::function<void()>& onFailure);
  void DisconnectFromServer();

 private:
  void receivePackages();

 private:
  std::shared_ptr<LucyNet::Connector> connector;
  std::shared_ptr<LucyNet::PackageDispatcher> packageDispatcher;

  std::shared_ptr<LucyNet::Machine> serverMachine;
  std::shared_ptr<LucyNet::Connection> serverConnection;
};
