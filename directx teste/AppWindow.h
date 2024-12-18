#pragma once
#include "Window.h"

class AppWindow: public Window
{


public:
	AppWindow();
	~AppWindow();

	// Herdado por meio de Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;
};

