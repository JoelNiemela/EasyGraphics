#include "texture.h"

#include "stb/stb_image.h"

#include <iostream>

namespace EasyGraphics {

Texture::Texture() {
	glGenTextures(1, &this->id);
	this->bind();
}

Texture::Texture(const std::string& file_path, GLenum min_filter, GLenum mag_filter, GLenum wrap_s, GLenum wrap_t) : file_path(file_path), buffer(nullptr), width(0), height(0), BPP(0) {
	stbi_set_flip_vertically_on_load(1);
	buffer = stbi_load(file_path.c_str(), &width, &height, &BPP, 4);

	glGenTextures(1, &this->id);
	this->bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	this->unbind();

	if (buffer) {
		stbi_image_free(buffer);
	}
}

Texture* Texture::from_bytes(unsigned char* bytes, GLsizei width, GLsizei height, GLenum min_filter, GLenum mag_filter, GLenum wrap_s, GLenum wrap_t) {
	Texture* texture = new Texture;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	texture->unbind();

	return texture;
}

Texture::~Texture() {
	glDeleteTextures(1, &this->id);
}

void Texture::bind(GLenum slot) const {
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace EasyGraphics
