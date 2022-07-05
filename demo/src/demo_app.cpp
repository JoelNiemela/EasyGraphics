#include "demo_app.h"

#include "res/material.h"

#include "views/menu_view.h"

DemoApp::DemoApp() : EasyGraphics::Application() {
	this->renderer.set_clear_color(0.2f, 0.3f, 0.3f, 1.0f);


	// Load Textures
	this->renderer.load_texture("opengl", "res/textures/opengl.png");


	// Load Materials

	// Basic Material
	this->renderer.load_shader("basic", "res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
	this->renderer.make_material("basic",
			this->renderer.shader("basic"),
			{
				EasyGraphics::Uniform("u_color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f))
			}
	);


	// Texture Material
	this->renderer.load_shader("texture", "res/shaders/texture_vertex.glsl", "res/shaders/texture_fragment.glsl");
	this->renderer.make_material("texture",
			this->renderer.shader("texture"),
			{
				EasyGraphics::Uniform("u_texture", 0)
			},
			this->renderer.texture("opengl")
	);


	// Load View
	this->view = new MenuView(this->renderer);
}

DemoApp::~DemoApp() {

}

void DemoApp::update() {

}
