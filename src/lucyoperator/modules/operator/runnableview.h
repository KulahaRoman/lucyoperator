#pragma once
#include "viewcontroller.h"

class RunnableView : public View {
 public:
  virtual void Run() = 0;
  virtual void Stop() = 0;

 protected:
  RunnableView();
  RunnableView(const std::shared_ptr<Controller>& controller);
};
