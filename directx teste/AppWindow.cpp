#include "AppWindow.h"
#include "GraphicEngine.h"


AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicEngine::get()->init();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicEngine::get()->release();

}
