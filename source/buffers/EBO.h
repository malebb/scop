#pragma once

#include "glad/glad.h"

class EBO
{
public:
	EBO();
	EBO(void* t_indices, GLuint t_size);
	void bind() const;
	void unbind() const;
	void deleteBuf() const;

private:
	GLuint m_id;
};