#pragma once

#include <glad/glad.h>

#include "Math.h"

#include <string>

class Shader
{
    public:
        Shader(const char *vertexPath, const char *fragmentPath);
        void useProgram() const;
        void deleteProgram() const;

        void setMat4(Math::mat4 t_mat, const std::string& t_name) const;

    private:
        unsigned int m_programId;
};
