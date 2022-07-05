#include "menu_view.h"

#include "imgui/imgui.h"

#include "demo_view.h"
#include "texture_view.h"

MenuView::MenuView(const EasyGraphics::Renderer &renderer) : View(renderer) {
	views.push_back(std::make_pair("test view", [&renderer]{ return new DemoView(renderer); }));
	views.push_back(std::make_pair("texture view", [&renderer]{ return new TextureView(renderer); }));
}

MenuView::~MenuView() {

}

void MenuView::update(double delta_time) {
	if (this->current_view) {
		this->current_view->update(delta_time);
	}
}

void MenuView::render() {
	if (this->current_view) {
		this->current_view->render();
	}
}

void MenuView::gui() {
	if (this->current_view) {
		this->current_view->gui();

		if (ImGui::Button("back")) {
			delete this->current_view;
			this->current_view = nullptr;
		}
	} else {
		for (auto& [label, make_view] : this->views) {
			if (ImGui::Button(label.c_str())) {
				this->current_view = make_view();
			}
		}
	}
}
