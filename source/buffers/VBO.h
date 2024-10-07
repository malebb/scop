#pragma once

#include "glad/glad.h"

class VBO
{
public:
	VBO();
	VBO(void* t_vertices, GLuint t_size);
	void bind() const;
	void unbind() const;
	void deleteBuf() const;
    
private:
	GLuint m_id;
};