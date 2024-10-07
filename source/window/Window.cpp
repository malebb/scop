#include "Window.h"
#include "App.h"

using SCOP::Window;

void glfwError(int code, const char *error)
{
	std::cout << "Glfw error (" << code << ") : " << error << std::endl; 
}

Window::Window(std::size_t t_width, std::size_t t_height) : m_width(t_width), m_height(t_height)
{
	if (!glfwInit())
		std::cerr << "Error: GLWF initialization failed" << std::endl;
	glfwSetErrorCallback(glfwError);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, AppConstants::openGLMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, AppConstants::openGLMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(t_width, t_height, m_title.data(), NULL, NULL);
	if (m_window == nullptr)
	{
		std::cerr << "Error: Failed to create the GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    std::cerr << "Error: Failed to initialize GLAD" << std::endl;
	    return ;
	}
	glViewport(0, 0, m_width, m_height);
	glfwSetFramebufferSizeCallback(m_window, resize);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::resize(GLFWwindow* t_window, int t_width, int t_height)
{
	(void)t_window;
    glViewport(0, 0, t_width, t_height);
}

void Window::checkKeysInputs()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(m_window, true);
	}
}

void Window::update()
{
   	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

std::size_t Window::getWidth(void) const
{
	return m_width;
}

std::size_t Window::getHeight(void) const
{
	return m_height;
}

bool Window::isClosed() const
{
	return glfwWindowShouldClose(m_window);
}
