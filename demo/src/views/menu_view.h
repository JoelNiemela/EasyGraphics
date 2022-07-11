#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "demo_app.h"
#include "view.h"

#include <vector>
#include <string>
#include <utility>
#include <functional>

class MenuView : public EasyGraphics::View<DemoApp> {
private:
	std::vector<std::pair<std::string, std::function<EasyGraphics::View<DemoApp>*()> > > views;
	EasyGraphics::View<DemoApp>* current_view = nullptr;
public:
	MenuView(const DemoApp &application);
	~MenuView();

	void update(double delta_time) override;
	void render() override;
	void gui() override;
};

#endif
