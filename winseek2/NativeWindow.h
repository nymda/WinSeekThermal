#pragma once
#include <Windows.h>
#include <tchar.h>

#define APPCLASS _T( "WinSeek" )
#define WND_WIDTH 923
#define WND_HEIGHT 493
class NativeWindow
{
	HINSTANCE hInstance = nullptr;
	HWND hWnd = nullptr;
	int iWidth = WND_WIDTH;
	int iHeight = WND_HEIGHT;
public:
	NativeWindow();
	~NativeWindow();

	bool Create( HINSTANCE hInstance, int nCmdShow );
	HWND GetHandle() { return hWnd; }

private:
	void Register();
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

};

