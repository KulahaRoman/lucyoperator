#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  centralWidget = new QWidget(this);

  centralLayout = new QVBoxLayout();

  serverGroup = new QGroupBox("Підключення до серверу", centralWidget);

  serverGroupLayout = new QHBoxLayout();
  serverCredsLayout = new QFormLayout();
  serverButtonsLayout = new QVBoxLayout();

  addressInput = new QLineEdit(serverGroup);
  addressInput->setText("127.0.0.1");

  portInput = new QLineEdit(serverGroup);
  portInput->setMaximumWidth(50);
  portInput->setText("500");

  connectButton = new QPushButton("Підключитись", serverGroup);
  disconnectButton = new QPushButton("Відключитись", serverGroup);
  disconnectButton->setEnabled(false);

  serverCredsLayout->addRow("Адреса:", addressInput);
  serverCredsLayout->addRow("Порт:", portInput);

  serverCredsLayout->setLabelAlignment(Qt::AlignRight);

  serverButtonsLayout->addWidget(connectButton);
  serverButtonsLayout->addWidget(disconnectButton);

  serverGroupLayout->addLayout(serverCredsLayout);
  serverGroupLayout->addLayout(serverButtonsLayout);

  serverGroup->setLayout(serverGroupLayout);

  targetGroup = new QGroupBox("Цільові ПК", centralWidget);
  targetGroupLayout = new QGridLayout(targetGroup);
  targetsTable = new QTableView(targetGroup);
  targetsTable->setEnabled(false);

  targetGroupLayout->addWidget(targetsTable);

  centralLayout->addWidget(serverGroup);
  centralLayout->addWidget(targetGroup);

  centralWidget->setLayout(centralLayout);

  this->setCentralWidget(centralWidget);

  this->setMinimumWidth(500);
  this->setMaximumWidth(600);

  this->setWindowTitle("Панель керування \"LOTUS\"");
  this->setWindowIcon(QIcon(":images/logo"));

  this->menuBar()->addMenu("&Файл");
  this->menuBar()->addMenu("&Про застосунок");

  connect(connectButton, &QPushButton::released, [this] {
    connectButton->setEnabled(false);
    disconnectButton->setEnabled(true);
    targetsTable->setEnabled(true);

    auto address = addressInput->text().toStdString();
    auto port = static_cast<unsigned short>(
        std::atoi(portInput->text().toStdString().c_str()));

    emit connectButtonPressed(address, port);
  });
  connect(disconnectButton, &QPushButton::released, [this] {
    connectButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    targetsTable->reset();
    targetsTable->setEnabled(false);

    emit disconnectButtonPressed();
  });
}

MainWindow::~MainWindow() {}

void MainWindow::toggleConnectButton(bool enabled) {
  connectButton->setEnabled(enabled);
}

void MainWindow::toggleDisconnectButton(bool enabled) {
  disconnectButton->setEnabled(enabled);
}
