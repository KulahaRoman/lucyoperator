#include "qtview.h"

QtView::QtView(const std::shared_ptr<Controller>& controller)
    : controller(controller) {}

void QtView::Run() {
  auto argc = 0;
  auto argv = static_cast<char**>(nullptr);

  QApplication app(argc, argv);
  MainWindow window;

  QObject::connect(
      &window, &MainWindow::connectButtonPressed,
      [this, &window](const std::string& address, unsigned short port) {
        window.toggleConnectButton(false);
        window.toggleDisconnectButton(true);

        controller->ConnectToServer(address, port, nullptr, [&window]() {
          window.toggleConnectButton(true);
          window.toggleDisconnectButton(false);
        });
      });
  QObject::connect(
      &window, &MainWindow::disconnectButtonPressed, [this, &window] {
        try {
          controller->DisconnectFromServer();
          window.toggleConnectButton(true);
          window.toggleDisconnectButton(false);
        } catch (const std::exception& exc) {
          CppUtils::Logger::Error("Failed to disconnect: {}", exc.what());
        }
      });

  window.show();

  auto result = app.exec();
  if (result) {
    throw std::runtime_error("GUI application crashed.");
  }
}

void QtView::Stop() {}
