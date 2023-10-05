#include "operator.h"

Operator::Operator(const std::shared_ptr<RunnableView>& runnableView)
    : runnableView(runnableView) {}

void Operator::run() { runnableView->Run(); }

void Operator::stop() { runnableView->Stop(); }
