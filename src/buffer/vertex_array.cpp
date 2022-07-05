#include "vertex_array.h"

#include <memory>

namespace EasyGraphics {

VertexArray::VertexArray(GLuint count, const VertexLayout layout) :
	id(new_vertex_array()),
	count(count),
	vb(VertexBuffer(nullptr, count * layout.get_stride())),
	layout(layout)
{
	this->bind();

	const auto& elements = layout.get_elements();
	size_t offset = 0;
	for (size_t i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized,
				layout.get_stride(), (const void*)offset);
		offset += element.count * VertexLayout::Element::get_size_of_type(element.type);
	}
}

VertexArray::VertexArray(VertexArray &&other) noexcept : 
	id(other.id),
	count(other.count),
	vb(std::move(other.vb)),
	layout(other.layout)
{
	std::destroy_at(&other.id);
	std::construct_at(&other.id, 0);
}

VertexArray::~VertexArray() {
	this->unbind();
	glDeleteVertexArrays(1, &this->id);
}

GLuint VertexArray::new_vertex_array() {
	GLuint id;
	glGenVertexArrays(1, &id);

	return id;
}

void VertexArray::bind() const {
	glBindVertexArray(this->id);
	this->vb.bind();
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

bool VertexArray::insert(const void *data, GLsizeiptr size) {
	return this->vb.insert(data, size);
}

void VertexArray::clear_buffer() {
	this->vb.clear();
}

} // namespace EasyGraphics