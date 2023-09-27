#include "qtview.h"

QtView::QtView(const std::shared_ptr<Controller>& controller)
    : controller(controller) {}

void QtView::Run() {
  auto argc = 0;
  auto argv = static_cast<char**>(nullptr);

  QApplication app(argc, argv);
  MainWindow window;

  QObject::connect(&window, &MainWindow::connectButtonPressed,
                   [this](const auto& address, auto port) {
                     controller->OnConnectButtonPressed(address, port);
                   });
  QObject::connect(&window, &MainWindow::disconnectButtonPressed,
                   [this] { controller->OnDisconnectButtonPressed(); });

  window.show();

  auto result = app.exec();
  if (result) {
    throw std::runtime_error("GUI application crashed.");
  }
}

void QtView::Stop() {}
