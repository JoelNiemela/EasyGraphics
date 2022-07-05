#ifndef TEST_APP_H
#define TEST_APP_H

#include "easy_graphics.h"

class DemoApp : public EasyGraphics::Application {
public:
	DemoApp();
	~DemoApp();

	void update() override;
};

#endif
