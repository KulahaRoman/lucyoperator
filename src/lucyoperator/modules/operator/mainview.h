#pragma once
#include <cpputils/logger.h>
#include <cpputils/threadpool.h>
#include <qapplication.h>

#include <memory>

#include "guiengine.h"
#include "mainwindow.h"
#include "runnableview.h"

class MainView : public RunnableView {
 public:
  MainView();
  MainView(const std::shared_ptr<Controller>& controller);

  void Run() override;
  void Stop() override;

 private:
  void initializeGUI();
  void terminateGUI();
  void initializeRoutes();

 private:
  GUIEngine* guiEngine;
  MainWindow* mainWindow;
};
