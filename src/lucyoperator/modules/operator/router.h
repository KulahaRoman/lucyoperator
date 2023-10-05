#pragma once
#include <any>
#include <functional>
#include <map>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>

class Router {
 public:
  virtual ~Router() = default;

  template <class Model>
  void RegisterRoute(const std::string& route,
                     const std::function<void(const Model&)>& handler);
  void RegisterRoute(const std::string& route,
                     const std::function<void()>& handler);
  void UnregisterRoute(const std::string& route);

 protected:
  Router() = default;

  template <class Model>
  void route(const std::string& route, const Model& model);
  void route(const std::string& route);

 private:
  std::map<std::string, std::function<void()>> routeMap;
  std::map<std::string, std::pair<size_t, std::function<void(const std::any&)>>>
      routeModelMap;
};

template <class Model>
inline void Router::RegisterRoute(
    const std::string& route,
    const std::function<void(const Model&)>& handler) {
  try {
    auto type = typeid(Model).hash_code();
    auto func = [handler](const std::any& model) {
      handler(std::any_cast<Model>(model));
    };

    routeModelMap[route] = std::make_pair(type, func);
  } catch (...) {
    throw std::runtime_error("ModelRouter::RegisterRoute() failed.");
  }
}

inline void Router::RegisterRoute(const std::string& route,
                                  const std::function<void()>& handler) {
  try {
    routeMap[route] = handler;
  } catch (...) {
    throw std::runtime_error("ModelRouter::RegisterRoute() failed.");
  }
}

inline void Router::UnregisterRoute(const std::string& route) {
  try {
    if (routeMap.count(route)) {
      routeMap.erase(route);
    }
    if (routeModelMap.count(route)) {
      routeModelMap.erase(route);
    }
  } catch (...) {
    throw std::runtime_error(
        "ModelRouter::UnregisterRoute() failed: route isn't "
        "registered.");
  }
}

template <class Model>
inline void Router::route(const std::string& route, const Model& model) {
  std::function<void(const std::any&)> handler;

  try {
    const auto& handlerBundle = routeModelMap.at(route);

    if (typeid(Model).hash_code() != handlerBundle.first) {
      throw std::runtime_error(
          "ModelRouter::routeModel() failed: invalid handler argument type.");
    }

    handler = handlerBundle.second;
  } catch (...) {
    throw std::runtime_error(
        "ModelRouter::routeModel() failed: route isn't registered.");
  }

  if (!handler) {
    throw std::runtime_error(
        "ModelRouter::routeModel() failed: handler in null.");
  }

  handler(model);
}

inline void Router::route(const std::string& route) {
  std::function<void()> handler;

  try {
    handler = routeMap.at(route);
  } catch (...) {
    throw std::runtime_error(
        "ModelRouter::routeModel() failed: route isn't registered.");
  }

  if (!handler) {
    throw std::runtime_error(
        "ModelRouter::routeModel() failed: handler in null.");
  }

  handler();
}
