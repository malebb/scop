#include <memory>
#include <cassert>

#include "Window.h"
#include "app.h"
#include "Shader.h"


using SCOP::Application;

std::unique_ptr<Application> Application::m_application = nullptr;

Application::Application(char **argv)
{
    m_3dParser = ObjParser(argv[1]);
}

std::unique_ptr<Application>& Application::initApplication(int argc, char **argv)
{
	assert(m_application == nullptr);
    if (argc != 2)
    {
        throw(std::invalid_argument("Usage: ./scop <3dFile.obj>"));
    }
	if (m_application == nullptr)
	{
		m_application = std::unique_ptr<Application>(new Application(argv));
	}
	return m_application;
}

void Application::launchGameLoop()
{
	SCOP::Window window(800, 600);
    Shader shaders("./source/shader/shadersGlsl/vertexShader.glsl",
                    "./source/shader/shadersGlsl/fragmentShader.glsl");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    const std::vector<Vertex>& vertices =  m_3dParser.getVertices();
    const std::vector<unsigned int>& indices = m_3dParser.getIndices();

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

	while(!window.isClosed())
	{
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

        shaders.useProgram();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		window.checkKeysInputs();
		window.update();
	}
}
