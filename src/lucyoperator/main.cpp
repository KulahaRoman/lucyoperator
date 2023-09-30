#include <lucycore/modulemanager.h>
#include <lucynet/unsecuretcpconnector.h>

#include "modules/operator/mvc/controller.h"
#include "modules/operator/mvc/operatordispatcher.h"
#include "modules/operator/mvc/qtview.h"
#include "modules/operator/mvc/targetshandler.h"
#include "modules/operator/operator.h"

int main(int argc, char** argv) {
  try {
    CppUtils::Logger::ToggleConsole(true);

    auto connector = std::make_shared<LucyNet::UnsecureTcpConnector>();

    auto dispatcher = std::make_shared<OperatorDispatcher>();
    auto targetsHandler = std::make_shared<TargetsHandler>();

    dispatcher->RegisterHandler(LucyNet::PackageType::TARGETS_RESPONSE,
                                targetsHandler);

    auto controller = std::make_shared<Controller>(connector, dispatcher);
    auto view = std::make_shared<QtView>(controller);
    auto oper = std::make_shared<Operator>(view);

    auto moduleManager = std::make_shared<LucyCore::Module::ModuleManager>();

    CppUtils::Logger::Information("Launching modules...");

    moduleManager->LaunchModule(
        oper,
        [] { CppUtils::Logger::Information("Module \"Operator\" started."); },
        [] { CppUtils::Logger::Information("Module \"Operator\" finished."); });

    moduleManager->AwaitTermination();

    CppUtils::Logger::Information("Finishing...");
  } catch (const std::exception& ex) {
    CppUtils::Logger::Critical("Critical error: {}. Application down.",
                               ex.what());
    return 1;
  }

  return 0;
}
