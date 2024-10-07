#pragma once

#include "glad/glad.h"

#include "VBO.h"

class VAO
{
public:
	VAO();
	void bind() const;
	void unbind() const;
	void linkVBO(VBO& t_vbo) const;
	void deleteBuf() const;

private:
	GLuint m_id;
};