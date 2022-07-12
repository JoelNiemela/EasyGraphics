#include "buffer/vertex_buffer.h"

#include "application.h"

#include <memory>

namespace EasyGraphics {

VertexBuffer::VertexBuffer(const Application &application, const void* data, GLuint size) :
	application(application),
	offset(0),
	id(VertexBuffer::new_buffer()),
	size(size)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept : 
	application(other.application),
	offset(other.offset),
	id(other.id),
	size(other.size)
{
	std::destroy_at(&other.id);
	std::construct_at(&other.id, 0);
}

VertexBuffer::~VertexBuffer() {
	this->application.disable_vertex_buffer();
	glDeleteBuffers(1, &this->id);
}

GLuint VertexBuffer::new_buffer() {
	GLuint id;
	glGenBuffers(1, &id);

	return id;
}

void VertexBuffer::bind() const {
	this->application.use(*this);
}

void VertexBuffer::unbind() const {
	this->application.disable_vertex_buffer();
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
