#include "app.h"
#include <memory>
#include <cassert>
#include "Window.h"

using SCOP::Application;
using SCOP::ObjParser;

std::unique_ptr<Application> Application::m_application = nullptr;

Application::Application(int argc, char **argv)
{
    if (argc != 2)
    {
        throw("Usage: ./scop <3dFile.obj>");
    }
    m_3dParser = ObjParser(argv[1]);
    m_3dParser.printParsedFile();
}

std::unique_ptr<Application>& Application::initApplication(int argc, char **argv)
{
	assert(m_application == nullptr);
	if (m_application == nullptr)
	{
		m_application = std::unique_ptr<Application>(new Application(argc, argv));
	}
	return m_application;
}

void Application::launchGameLoop()
{
	SCOP::Window window(800, 600);
	while(!window.isClosed())
	{
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		window.checkKeysInputs();
		window.update();
	}
}
