#include "app.h"

int main(int argc, char **argv)
{
	SCOP::Application::initApplication(argc, argv)->launchGameLoop();
	return 0;
}
