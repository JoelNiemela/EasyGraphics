#include "res/material.h"

namespace EasyGraphics {

Material::Material(const Shader &shader, std::initializer_list<Uniform> uniforms) : shader(shader), uniforms(uniforms), texture(nullptr) {}

Material::Material(const Shader &shader, std::initializer_list<Uniform> uniforms, const Texture* texture) : shader(shader), uniforms(uniforms), texture(texture) {}

Material::~Material() {}

void Material::bind() const {
	this->shader.bind();

	if (this->texture) this->texture->bind();

	for (const Uniform &uniform : this->uniforms) {
		this->shader.set_uniform(uniform);
	}
}

void Material::bind_with(std::initializer_list<Uniform> uniforms) const {
	this->bind();

	for (const Uniform &uniform : uniforms) {
		this->shader.set_uniform(uniform);
	}
}

void Material::unbind() const {
	
}

} // namespace EasyGraphics
