#include <lucycore/modulemanager.h>
#include <lucynet/unsecuretcpconnector.h>

#include "modules/operator/maincontroller.h"
#include "modules/operator/mainview.h"
#include "modules/operator/operator.h"
#include "modules/operator/operatordispatcher.h"
#include "modules/operator/targetshandler.h"

int main(int argc, char** argv) {
  try {
    CppUtils::Logger::ToggleConsole(true);

    auto connector = std::make_shared<LucyNet::UnsecureTcpConnector>();

    auto dispatcher = std::make_shared<OperatorDispatcher>();

    auto controller = std::make_shared<MainController>(connector, dispatcher);
    auto view = std::make_shared<MainView>(controller);

    controller->SetView(view);

    auto targetsHandler = std::make_shared<TargetsHandler>(view);
    dispatcher->RegisterHandler(LucyNet::PackageType::TARGETS_RESPONSE,
                                targetsHandler);

    auto oper = std::make_shared<Operator>(view);

    auto moduleManager = std::make_shared<LucyCore::Module::ModuleManager>();

    CppUtils::Logger::Information("Launching modules...");

    moduleManager->LaunchModule(
        oper,
        [] { CppUtils::Logger::Information("Module \"Operator\" started."); },
        [] { CppUtils::Logger::Information("Module \"Operator\" finished."); });

    /*std::thread th([&moduleManager] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        moduleManager->InitiateTermination();
        });
    th.join();*/

    moduleManager->AwaitTermination();

    CppUtils::Logger::Information("Finishing...");
  } catch (const std::exception& ex) {
    CppUtils::Logger::Critical("Critical error: {}. Application down.",
                               ex.what());
    return 1;
  }

  return 0;
}
