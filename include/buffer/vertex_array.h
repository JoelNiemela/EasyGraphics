#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_layout.h"

namespace EasyGraphics {

class VertexArray {
private:
	VertexBuffer vb;
public:
	const GLuint id;
	// number of verticies in the VertexBuffer
	const GLuint count;
	const VertexLayout layout;
public:
	VertexArray(GLuint count, VertexLayout layout);
	VertexArray(const VertexArray &other) = delete;
	VertexArray(VertexArray &&other) noexcept;
	~VertexArray();

	static GLuint new_vertex_array();

	void bind() const;
	void unbind() const;

	bool insert(const void* data, GLsizeiptr size);
	void clear_buffer();

	GLuint get_used_count() const;
	inline const VertexBuffer& get_buffer() const { return this->vb; }
};

} // namespace EasyGraphics

#endif
