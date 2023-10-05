#pragma once
#include <qapplication.h>

#include <condition_variable>
#include <mutex>

class GUIEngine : public QApplication {
  Q_OBJECT
 public:
  GUIEngine(int argc, char** argv);

  int Run();
  void Stop();

 signals:
  void start();
  void stop();

 private:
  int returnCode;

  bool running;

  std::mutex mx;
  std::condition_variable cv;
};
