#include "App.h"
#include <exception>

int main(int argc, char **argv)
{
    try
    {
        auto& app = SCOP::Application::initApplication(argc, argv);
        app->launchGameLoop();
    }
    catch (const std::exception& err)
    {
        std::cout << err.what() << std::endl;
    }
	return 0;
}
