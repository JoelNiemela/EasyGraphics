#include "shader.h"

#include "material.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

namespace EasyGraphics {

Shader::Shader(const std::string &vertex_shader_filepath, const std::string &fragment_shader_filepath)
	: vertex_shader_filepath(vertex_shader_filepath), fragment_shader_filepath(fragment_shader_filepath) {

	this->id = Shader::create_program(Shader::load_file(vertex_shader_filepath), Shader::load_file(fragment_shader_filepath));
}

Shader::~Shader() {
	this->unbind();
	glDeleteProgram(this->id);
}

Shader* Shader::from_source(const char* vertex_shader_src, const char* fragment_shader_src) {
	Shader* shader = new Shader;
	shader->id = Shader::create_program(vertex_shader_src, fragment_shader_src);
	return shader;
}

void Shader::bind() const {
	glUseProgram(this->id);
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::set_uniform(const Uniform &uniform) const {
	std::visit([&](auto data){ this->set_uniform(uniform.name, data); }, uniform.data);
}

void Shader::set_uniform(const std::string &name, GLint value) const {
	glUniform1i(this->get_uniform_location(name), value);
}

void Shader::set_uniform(const std::string &name, GLfloat value) const {
	glUniform1f(this->get_uniform_location(name), value);
}

void Shader::set_uniform(const std::string &name, glm::vec3 vec) const {
	glUniform3f(this->get_uniform_location(name), vec[0], vec[1], vec[2]);
}

void Shader::set_uniform(const std::string &name, glm::vec4 vec) const {
	glUniform4f(this->get_uniform_location(name), vec[0], vec[1], vec[2], vec[3]);
}

void Shader::set_uniform(const std::string &name, glm::mat4 mat) const {
	glUniformMatrix4fv(this->get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(mat));
}

std::string Shader::load_file(const std::string &file_path) {
	std::ifstream file(file_path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string src = buffer.str();

	return src;
}

GLuint Shader::compile_shader(GLuint type, const std::string &src) {
	GLuint id = glCreateShader(type);

	const char* source = src.c_str();

	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Error: Failed to compile shader: " << message << std::endl;

		glDeleteShader(id);

		delete[] message;

		return 0;
	}

	return id;
}

GLuint Shader::create_program(const std::string &vertex_src, const std::string &fragment_src) {
	GLuint program = glCreateProgram();

	GLuint vs = Shader::compile_shader(GL_VERTEX_SHADER, vertex_src);
	GLuint fs = Shader::compile_shader(GL_FRAGMENT_SHADER, fragment_src);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

GLint Shader::get_uniform_location(const std::string &name) const {
	if (this->uniform_location_cache.find(name) != this->uniform_location_cache.end()) {
		return this->uniform_location_cache[name];
	}

	GLint location = glGetUniformLocation(this->id, name.c_str());
	if (location == -1) {
		std::cerr << "Error: couldn't find uniform '" << name << "'" << std::endl;
	}

	this->uniform_location_cache[name] = location;
	return location;
}

} // namespace EasyGraphics
