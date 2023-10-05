#include "runnableview.h"

RunnableView::RunnableView() {}

RunnableView::RunnableView(const std::shared_ptr<Controller>& controller)
    : View(controller) {}
