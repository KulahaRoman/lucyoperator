#pragma once
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qpointer.h>
#include <qpushbutton.h>
#include <qtableview.h>

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:
  void connectButtonPressed(const std::string& address, unsigned short port);
  void disconnectButtonPressed();

 public slots:
  void toggleConnectButton(bool enabled);
  void toggleDisconnectButton(bool enabled);

 private:
  QPointer<QWidget> centralWidget;
  QPointer<QVBoxLayout> centralLayout;
  QPointer<QGroupBox> serverGroup;
  QPointer<QHBoxLayout> serverGroupLayout;
  QPointer<QFormLayout> serverCredsLayout;
  QPointer<QLineEdit> addressInput;
  QPointer<QLineEdit> portInput;
  QPointer<QVBoxLayout> serverButtonsLayout;
  QPointer<QPushButton> connectButton;
  QPointer<QPushButton> disconnectButton;
  QPointer<QGroupBox> targetGroup;
  QPointer<QGridLayout> targetGroupLayout;
  QPointer<QTableView> targetsTable;
};
