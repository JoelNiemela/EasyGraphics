#include "buffer/vertex_buffer.h"

#include <memory>

namespace EasyGraphics {

VertexBuffer::VertexBuffer(const void* data, GLuint size) :
	id(VertexBuffer::new_buffer()),
	size(size),
	offset(0)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept : 
	id(other.id),
	size(other.size),
	offset(other.offset)
{
	std::destroy_at(&other.id);
	std::construct_at(&other.id, 0);
}

VertexBuffer::~VertexBuffer() {
	this->unbind();
	glDeleteBuffers(1, &this->id);
}

GLuint VertexBuffer::new_buffer() {
	GLuint id;
	glGenBuffers(1, &id);

	return id;
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool VertexBuffer::insert(const void* data, GLsizeiptr size) {
	if (this->offset + size > this->size) {
		return false;
	}

	glBufferSubData(GL_ARRAY_BUFFER, this->offset, size, data);
	this->offset += size;

	return true;
}

void VertexBuffer::clear() {
	this->offset = 0;
}

} // namespace EasyGraphics
