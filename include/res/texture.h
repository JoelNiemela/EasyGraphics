#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace EasyGraphics {

class Texture {
private:
	GLuint id;
	std::string file_path;
	unsigned char* buffer;
	int width, height, BPP;
public:
	Texture();
	Texture(const std::string& file_path, GLenum min_filter = GL_LINEAR, GLenum mag_filter = GL_LINEAR, GLenum wrap_s = GL_CLAMP_TO_EDGE, GLenum wrap_t = GL_CLAMP_TO_EDGE);
	~Texture();

	static Texture* from_bytes(unsigned char* bytes, GLsizei width, GLsizei height, GLenum min_filter = GL_LINEAR, GLenum mag_filter = GL_LINEAR, GLenum wrap_s = GL_CLAMP_TO_EDGE, GLenum wrap_t = GL_CLAMP_TO_EDGE);

	void bind(GLenum slot = GL_TEXTURE0) const;
	void unbind() const;

	inline int get_width() const { return this->width; }
	inline int get_height() const { return this->height; }
};

} // namespace EasyGraphics

#endif
