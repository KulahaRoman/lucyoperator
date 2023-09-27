#pragma once
#include <qapplication.h>

#include <memory>

#include "controller.h"
#include "mainwindow.h"
#include "view.h"

class QtView : public View {
 public:
  QtView(const std::shared_ptr<Controller>& controller);

  void Run() override;
  void Stop() override;

 private:
  std::shared_ptr<Controller> controller;
};
