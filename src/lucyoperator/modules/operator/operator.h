#pragma once
#include <lucycore/abstractcontiniousmodule.h>

#include <atomic>

#include "runnableview.h"

class Operator : public LucyCore::Module::AbstractContiniousModule {
 public:
  Operator(const std::shared_ptr<RunnableView>& runnableView);

 private:
  void run() override;
  void stop() override;

 private:
  std::shared_ptr<RunnableView> runnableView;
};
