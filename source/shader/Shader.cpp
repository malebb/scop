#include "Shader.h"

#include <fstream>
#include <iostream>
#include <cstring>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::ifstream vertexFile;
    std::ifstream fragmentFile;


    // Read vertex content
    vertexFile.open(vertexPath);
    if (!vertexFile.is_open())
        throw (std::runtime_error("Error: vertex shader could not be opened"));
    std::string vertexShaderContent((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
    const char *vertexShader = vertexShaderContent.c_str();

    // Read fragment content
    fragmentFile.open(fragmentPath);
    if (!fragmentFile.is_open())
        throw (std::runtime_error("Error: fragment shader could not be opened"));
    std::string fragmentShaderContent((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
    const char *fragmentShader = fragmentShaderContent.c_str();

    // Create and compile the shaders
    int success;
    char errorLog[512];

    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, errorLog);
        throw (std::runtime_error("Error: vertex shader could not be opened" + std::string(errorLog)));
    }

    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, errorLog);
        throw (std::runtime_error("Error: fragment shader could not be opened" + std::string(errorLog)));
    }

    // Create the program
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShaderId);
    glAttachShader(m_programId, fragmentShaderId);
    glLinkProgram(m_programId);
}

void Shader::useProgram() const
{
    glUseProgram(m_programId);
}
