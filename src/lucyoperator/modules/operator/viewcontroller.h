#pragma once
#include "router.h"

class View;

class Controller : public Router {
 public:
  void SetView(const std::shared_ptr<View>& view);

  template <class Model>
  void Notify(const std::string& route, const Model& model);
  void Notify(const std::string& route);

 protected:
  Controller() = default;
  Controller(const std::shared_ptr<View>& view);

  std::shared_ptr<View> getView() const;

 private:
  std::weak_ptr<View> view;
};

inline Controller::Controller(const std::shared_ptr<View>& view) : view(view) {}

inline std::shared_ptr<View> Controller::getView() const {
  auto viewPointer = view.lock();

  if (!viewPointer) {
    throw std::runtime_error(
        "Controller::getView() failed: object doesn't exist.");
  }

  return viewPointer;
}

inline void Controller::SetView(const std::shared_ptr<View>& view) {
  this->view = view;
}

template <class Model>
inline void Controller::Notify(const std::string& route, const Model& model) {
  this->route(route, model);
}

inline void Controller::Notify(const std::string& route) { this->route(route); }

class View : public Router {
 public:
  void SetController(const std::shared_ptr<Controller>& controller);

  template <class Model>
  void Update(const std::string& route, const Model& model);
  void Update(const std::string& route);

 protected:
  View() = default;
  View(const std::shared_ptr<Controller>& controller);

  std::shared_ptr<Controller> getController() const;

 private:
  std::weak_ptr<Controller> controller;
};

inline View::View(const std::shared_ptr<Controller>& controller)
    : controller(controller) {}

inline std::shared_ptr<Controller> View::getController() const {
  auto controllerPointer = controller.lock();

  if (!controllerPointer) {
    throw std::runtime_error(
        "View::getController() failed: object doesn't exist.");
  }

  return controllerPointer;
}

inline void View::SetController(const std::shared_ptr<Controller>& controller) {
  this->controller = controller;
}

template <class Model>
inline void View::Update(const std::string& route, const Model& model) {
  this->route(route, model);
}

inline void View::Update(const std::string& route) { this->route(route); }
