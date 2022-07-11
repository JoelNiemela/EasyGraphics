#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

namespace EasyGraphics {

class VertexBuffer {
private:
	const GLuint id;
	const GLuint size;
	GLuint offset;
public:
	VertexBuffer(const void* data, GLuint size);
	VertexBuffer(const VertexBuffer &other) = delete;
	VertexBuffer(VertexBuffer &&other) noexcept;
	~VertexBuffer();

	static GLuint new_buffer();

	void bind() const;
	void unbind() const;

	bool insert(const void* data, GLsizeiptr size);
	void clear();

	inline GLuint get_offset() const { return this->offset; }
};

} // namespace EasyGraphics

#endif
