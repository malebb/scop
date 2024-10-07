#include "EBO.h"

EBO::EBO()
{

}

EBO::EBO(void* t_indices, GLuint t_size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_size, t_indices, GL_STATIC_DRAW);
}

void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteBuf() const
{
	glDeleteBuffers(1, &m_id);
}