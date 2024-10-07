#include <memory>
#include <cassert>

#include "Window.h"
#include "App.h"
#include "Shader.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

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

    std::vector<Vertex>& vertices =  m_3dParser.getVertices();
    std::vector<unsigned int>& indices = m_3dParser.getIndices();

    VAO vao;
    VBO vbo(&vertices[0], sizeof(Vertex) * vertices.size());
    EBO ebo(&indices[0], sizeof(unsigned int) * indices.size());

    vao.bind();
    ebo.bind();
    vao.linkVBO(vbo);

    glBindVertexArray(0);
    
	while(!window.isClosed())
	{
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

        shaders.useProgram();
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		window.checkKeysInputs();
		window.update();
	}
    vao.deleteBuf();
    vbo.deleteBuf();
    ebo.deleteBuf();    
    shaders.deleteProgram();
}
