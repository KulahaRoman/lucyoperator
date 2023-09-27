#include "operator.h"

Operator::Operator(const std::shared_ptr<View>& view) : view(view) {}

Operator::~Operator() {}

void Operator::run() { view->Run(); }

void Operator::stop() { view->Stop(); }
