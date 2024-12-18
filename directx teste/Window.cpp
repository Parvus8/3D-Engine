#include "Window.h"

//Window* window = NULL;

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}	

}

bool Window::init() 
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;


	if(!::RegisterClassEx(&wc))
		return false;

	//cria a janela
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,L"MyWindowClass",L"DirectX Application",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,1024,768,NULL,NULL,NULL,this);

	//erro na criação da janela TODO: ajustar o error handling.
	if (!m_hwnd) 
		return false; 
	
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_run = true;
	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	this->onUpdate();

	Sleep(0);
	
	return true;
}

bool Window::release()
{
	//fecha a janela 
	if (m_hwnd)
		if (!::DestroyWindow(m_hwnd))
			return false;

	return true;
}
bool Window::isRun()
{
	return m_is_run;
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{

}