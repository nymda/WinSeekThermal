#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "NativeWindow.h"
#include <chrono>
#include "drawing.h"
#include <iostream>
#include "seekhandler.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

std::chrono::high_resolution_clock fpsTimer;
float eTime = 0.f;
char exTimeTxt[256]{ 0 };

IDirect3D9* pD3d = nullptr;
IDirect3DDevice9* pDevice = nullptr;
ID3DXFont* pFont = nullptr;
ID3DXSprite* pSprite = nullptr;

bool InitD3D(HWND hWnd, UINT uWidth, UINT uHeight)
{
	pD3d = Direct3DCreate9( D3D_SDK_VERSION );
	D3DPRESENT_PARAMETERS dp{ 0 };
	dp.BackBufferWidth = uWidth;
	dp.BackBufferHeight = uHeight;
	dp.hDeviceWindow = hWnd;
	dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dp.Windowed = TRUE;

	HRESULT hr = pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &dp, &pDevice );
	if (FAILED( hr ) || !pDevice)
	{
		MessageBox( NULL, _T( "Failed to create D3D Device." ), _T( "Error" ), MB_ICONERROR | MB_OK );
		return false;
	}
	return true;
}

void Render(NativeWindow& wnd)
{
	auto startTime = fpsTimer.now();
	pDevice->BeginScene();
	pDevice->Clear( 1, nullptr, D3DCLEAR_TARGET, 0x00111111, 1.0f, 0 );
	//START





	//END
	DrawTextC(exTimeTxt, 10, 10, 15, white, pDevice);
	pDevice->EndScene();
	pDevice->Present( 0, 0, 0, 0 );
	auto endTime = fpsTimer.now();
	eTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f; 
	sprintf_s(exTimeTxt, 256, "FPS    : %i", (int)(1000.f / eTime));
}

FILE* createConsole() {
	AllocConsole();
	std::wstring strW = L"FennHooks";
	SetConsoleTitle(strW.c_str());
	HWND console = GetConsoleWindow();
	DeleteMenu(GetSystemMenu(console, false), SC_CLOSE, MF_BYCOMMAND);
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.precision(2);
	SMALL_RECT tmp = { 0, 0, 120, 15 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &tmp);
	std::cout << "Init" << std::endl;
	return f;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	createConsole();

	NativeWindow wnd;

	wnd.Create( hInstance, nCmdShow );

	initWinusb();

	if (!InitD3D( wnd.GetHandle(), WND_WIDTH, WND_HEIGHT ))
		return 1;

	MSG m;
	while (true)
	{
		while (PeekMessage( &m, NULL, 0, 0, PM_REMOVE ) && m.message != WM_QUIT)
		{
			TranslateMessage( &m );
			DispatchMessage( &m );
		}
		if (m.message == WM_QUIT)
			break;

		Render(wnd);
	}

	return 0;
}