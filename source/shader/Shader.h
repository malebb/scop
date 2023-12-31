#pragma once

#include <glad/glad.h>

class Shader
{
    public:
        Shader(const char *vertexPath, const char *fragmentPath);
        void useProgram() const;
    private:
        unsigned int m_programId;
};
