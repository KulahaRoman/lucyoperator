#pragma once

class View {
 public:
  virtual void Run() = 0;
  virtual void Stop() = 0;

  virtual ~View() = default;
};
