#include "qtview.h"

QtView::QtView(const std::shared_ptr<Controller>& controller)
    : controller(controller) {}

void QtView::Run() {
  auto argc = 0;
  auto argv = static_cast<char**>(nullptr);

  QApplication app(argc, argv);
  MainWindow window;

  QObject::connect(
      &window, &MainWindow::connectButtonPressed, &window,
      [this, &window](const std::string& address, unsigned short port) {
        window.toggleConnectButton(false);
        window.toggleDisconnectButton(true);

        controller->ConnectToServer(
            address, port,
            [&window, address, port]() { emit window.successfullyConnected(); },
            [&window, address, port]() {
              emit window.unsuccessfullyConnected();
            });
      });
  QObject::connect(
      &window, &MainWindow::disconnectButtonPressed, &window, [this, &window] {
        try {
          controller->DisconnectFromServer();

          window.toggleConnectButton(true);
          window.toggleDisconnectButton(false);
          window.toggleLineEdit(true);
          window.toggleTable(false);

        } catch (const std::exception& exc) {
          CppUtils::Logger::Error("Failed to disconnect: {}", exc.what());
        }
      });
  QObject::connect(&window, &MainWindow::successfullyConnected, &window,
                   [&window] {
                     window.toggleConnectButton(false);
                     window.toggleDisconnectButton(true);
                     window.toggleLineEdit(false);
                   });
  QObject::connect(&window, &MainWindow::unsuccessfullyConnected, &window,
                   [&window] {
                     window.toggleConnectButton(true);
                     window.toggleDisconnectButton(false);
                     window.toggleLineEdit(true);
                   });

  window.show();

  auto result = app.exec();
  if (result) {
    throw std::runtime_error("GUI application crashed.");
  }
}

void QtView::Stop() {}
