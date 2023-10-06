#include "mainview.h"

MainView::MainView() { initializeRoutes(); }

MainView::MainView(const std::shared_ptr<Controller>& controller)
    : RunnableView(controller) {
  initializeRoutes();
}

void MainView::Run() {
  initializeGUI();

  mainWindow->show();

  auto result = guiEngine->Run();
  if (result) {
    throw std::runtime_error("GUI application crashed.");
  }

  getController()->Notify("disconnect");

  terminateGUI();
}

void MainView::Stop() { guiEngine->Stop(); }

void MainView::initializeGUI() {
  auto argc = 0;
  auto argv = static_cast<char**>(nullptr);

  guiEngine = new GUIEngine(argc, argv);
  mainWindow = new MainWindow();

  QObject::connect(mainWindow, &MainWindow::connectButtonPressed, mainWindow,
                   [this](const std::string& address, unsigned short port) {
                     mainWindow->toggleConnectButton(false);
                     mainWindow->toggleDisconnectButton(false);
                     mainWindow->toggleLineEdit(false);

                     ServerCredentials serverCredentials;
                     serverCredentials.SetAddress(address);
                     serverCredentials.SetPort(port);

                     getController()->Notify("connect", serverCredentials);
                   });
  QObject::connect(
      mainWindow, &MainWindow::disconnectButtonPressed, mainWindow, [this] {
        try {
          mainWindow->toggleConnectButton(true);
          mainWindow->toggleDisconnectButton(false);
          mainWindow->toggleLineEdit(true);
          mainWindow->toggleTable(false);

          getController()->Notify("disconnect");
        } catch (const std::exception& exc) {
          CppUtils::Logger::Error("Failed to disconnect: {}", exc.what());
        }
      });
  QObject::connect(mainWindow, &MainWindow::connected, mainWindow,
                   [this] { mainWindow->toggleDisconnectButton(true); });
  QObject::connect(mainWindow, &MainWindow::disconnected, mainWindow, [this] {
    mainWindow->toggleConnectButton(true);
    mainWindow->toggleDisconnectButton(false);
    mainWindow->toggleLineEdit(true);

    mainWindow->clearTable();
  });
  QObject::connect(
      mainWindow, &MainWindow::targetsReceived, mainWindow,
      [this](const TargetsList& targets) { mainWindow->updateTable(targets); });
}

void MainView::terminateGUI() {
  delete mainWindow;
  mainWindow = nullptr;

  delete guiEngine;
  guiEngine = nullptr;
}

void MainView::initializeRoutes() {
  RegisterRoute("connected", [this] { emit mainWindow->connected(); });
  RegisterRoute("disconnected", [this] { emit mainWindow->disconnected(); });
  RegisterRoute<TargetsList>("targetsReceived",
                             [this](const TargetsList& targets) {
                               emit mainWindow->targetsReceived(targets);
                             });
}
