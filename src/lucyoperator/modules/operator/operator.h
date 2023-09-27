#pragma once
#include <lucycore/abstractcontiniousmodule.h>

#include <atomic>

#include "mvc/view.h"

class Operator : public LucyCore::Module::AbstractContiniousModule {
 public:
  Operator(const std::shared_ptr<View>& view);
  ~Operator();

 private:
  void run() override;
  void stop() override;

 private:
  std::shared_ptr<View> view;
};
