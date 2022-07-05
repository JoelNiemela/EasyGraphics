#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "view.h"

#include <vector>
#include <string>
#include <utility>
#include <functional>

class MenuView : public EasyGraphics::View {
private:
	std::vector<std::pair<std::string, std::function<EasyGraphics::View*()> > > views;
	EasyGraphics::View* current_view = nullptr;
public:
	MenuView(const EasyGraphics::Renderer &renderer);
	~MenuView();

	void update(double delta_time) override;
	void render() override;
	void gui() override;
};

#endif
