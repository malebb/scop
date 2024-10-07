#include "VBO.h"

VBO::VBO()
{

}

VBO::VBO(void* t_vertices, GLuint t_size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, t_size, t_vertices, GL_STATIC_DRAW);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteBuf() const
{
	glDeleteBuffers(1, &m_id);
}