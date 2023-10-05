#include "guiengine.h"

GUIEngine::GUIEngine(int argc, char** argv)
    : QApplication(argc, argv), returnCode(0), running(false) {
  QObject::connect(this, &GUIEngine::start, this,
                   [this] { returnCode = this->exec(); });
  QObject::connect(this, &GUIEngine::stop, this, [this] { this->quit(); });
}

int GUIEngine::Run() {
  emit start();

  auto lock = std::unique_lock<std::mutex>(mx);
  auto predicate = [this] { return running; };

  running = true;

  cv.wait(lock, predicate);

  return returnCode;
}

void GUIEngine::Stop() {
  emit stop();

  cv.notify_one();
}
