#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace EasyGraphics {

class IndexBuffer {
public:
	const GLuint id;
	const GLuint count;
public:
	IndexBuffer(const GLuint* data, GLuint count);
	IndexBuffer(const IndexBuffer &other) = delete;
	IndexBuffer(IndexBuffer &&other) noexcept;
	~IndexBuffer();

	static GLuint new_buffer();

	enum Shape {
		QUADS,
	};

	static IndexBuffer generate(Shape shape, unsigned int count);

	void bind() const;
	void unbind() const;

	inline GLuint get_count() const { return this->count; };
};

} // namespace EasyGraphics

#endif
