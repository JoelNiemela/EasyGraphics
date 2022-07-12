#include "buffer/index_buffer.h"

#include "application.h"

#include <algorithm>
#include <iostream>
#include <cassert>
#include <memory>

namespace EasyGraphics {

IndexBuffer::IndexBuffer(const Application &application, const GLuint* data, GLuint count) :
	application(application),
	id(IndexBuffer::new_buffer()),
	count(count)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept : 
	application(other.application),
	id(other.id),
	count(other.count)
{
	std::destroy_at(&other.id);
	std::construct_at(&other.id, 0);
}

IndexBuffer::~IndexBuffer() {
	this->application.disable_index_buffer();
	glDeleteBuffers(1, &this->id);
}

GLuint IndexBuffer::new_buffer() {
	GLuint id;
	glGenBuffers(1, &id);

	return id;
}

IndexBuffer IndexBuffer::generate(const Application &application, Shape shape, unsigned int count) {
	switch (shape) {
		case Shape::QUADS:
			GLuint indicies[count * 6];
			for (unsigned int i = 0; i < count; i++) {
				indicies[(i * 6) + 0] = 0 + (i * 4);
				indicies[(i * 6) + 1] = 1 + (i * 4);
				indicies[(i * 6) + 2] = 2 + (i * 4);

				indicies[(i * 6) + 3] = 2 + (i * 4);
				indicies[(i * 6) + 4] = 3 + (i * 4);
				indicies[(i * 6) + 5] = 0 + (i * 4);
			}

			return IndexBuffer(application, indicies, count * 6);
	}

	std::cerr << "Error in IndexBuffer::generate: unsupported shape (" << shape << ")" << std::endl;
	assert(false);
}

void IndexBuffer::bind() const {
	this->application.use(*this);
}

void IndexBuffer::unbind() const {
	this->application.disable_index_buffer();
}

} // namespace EasyGraphics
