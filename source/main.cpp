#include "app.h"

int main(int argc, char **argv)
{
    try
    {
        auto& app = SCOP::Application::initApplication(argc, argv);
        app->launchGameLoop();
    }
    catch (const char* err)
    {
        std::cerr << err << std::endl;
    }
	return 0;
}
