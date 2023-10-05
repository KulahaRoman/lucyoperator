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
                     mainWindow->toggleDisconnectButton(true);

                     /*controller->ConnectToServer(
                         address, port,
                         [&window, address, port]() { emit
                        window.successfullyConnected(); },
                         [&window, address, port]() {
                           emit window.unsuccessfullyConnected();
                         });*/
                   });
  QObject::connect(
      mainWindow, &MainWindow::disconnectButtonPressed, mainWindow, [this] {
        try {
          /*controller->DisconnectFromServer();*/

          mainWindow->toggleConnectButton(true);
          mainWindow->toggleDisconnectButton(false);
          mainWindow->toggleLineEdit(true);
          mainWindow->toggleTable(false);

        } catch (const std::exception& exc) {
          CppUtils::Logger::Error("Failed to disconnect: {}", exc.what());
        }
      });
  QObject::connect(mainWindow, &MainWindow::successfullyConnected, mainWindow,
                   [this] {
                     mainWindow->toggleConnectButton(false);
                     mainWindow->toggleDisconnectButton(true);
                     mainWindow->toggleLineEdit(false);
                   });
  QObject::connect(mainWindow, &MainWindow::unsuccessfullyConnected, mainWindow,
                   [this] {
                     mainWindow->toggleConnectButton(true);
                     mainWindow->toggleDisconnectButton(false);
                     mainWindow->toggleLineEdit(true);
                   });
}

void MainView::terminateGUI() {
  delete mainWindow;
  mainWindow = nullptr;

  delete guiEngine;
  guiEngine = nullptr;
}

void MainView::initializeRoutes() {}
