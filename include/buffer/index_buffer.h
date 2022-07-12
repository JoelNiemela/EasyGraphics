#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace EasyGraphics {

class Application;

class IndexBuffer {
private:
	const Application &application;
public:
	const GLuint id;
	const GLuint count;
public:
	IndexBuffer(const Application &application, const GLuint* data, GLuint count);
	IndexBuffer(const IndexBuffer &other) = delete;
	IndexBuffer(IndexBuffer &&other) noexcept;
	~IndexBuffer();

	static GLuint new_buffer();

	enum Shape {
		QUADS,
	};

	static IndexBuffer generate(const Application &application, Shape shape, unsigned int count);

	inline GLuint get_count() const { return this->count; };
};

} // namespace EasyGraphics

#endif
