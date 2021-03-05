#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "NativeWindow.h"
#include <chrono>
#include "drawing.h"
#include <iostream>
#include "seekhandler.h"
#include <string>
#include <sstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

std::chrono::high_resolution_clock fpsTimer;
float eTime = 0.f;
char exTimeTxt[256]{ 0 };
char title[64]{ 0 };
WNDPROC oWndProc;

IDirect3D9* pD3d = nullptr;
IDirect3DDevice9* pDevice = nullptr;
ID3DXFont* pFont = nullptr;
ID3DXSprite* pSprite = nullptr;
seekThermalCamera STC{};
int thermalPalette = 0;

LRESULT APIENTRY hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_UP)
		{
			thermalPalette++;
		}
		if (wParam == VK_DOWN)
		{
			thermalPalette--;
		}

		if (thermalPalette < 0) {
			thermalPalette = 0;
		}
		if (thermalPalette > 5) {
			thermalPalette = 5;
		}

		sprintf_s(title, 64, "WinSeek | Palette %i", thermalPalette);
		SetWindowTextA(hWnd, title);
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

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

rawThermalFrameContainer rtfBuffer{};

int len = 206;
int hei = 156;
int fMin = 12000;
int fMax = 0;
USHORT calibData[32448]{};

USHORT drawFrameBuffer[32448];
int lastAverage = 0;

int totalCount = 0;
int totalVal = 0;
int averageVal = 1;

void Render(NativeWindow& wnd)
{
	auto startTime = fpsTimer.now();
	pDevice->BeginScene();
	pDevice->Clear( 1, nullptr, D3DCLEAR_TARGET, 0x00111111, 1.0f, 0 );
	//START
	STC.getFrame(&rtfBuffer);

	int pt = 0;

	int tMin = 12000;
	int tMax = 0;


	UINT16 allowMin = 1000;
	UINT16 allowMax = 12000;

	struct fixedShade {
		byte brightness;
	};

	if (rtfBuffer.frameType == 0x03) {
		totalVal = 0;
		totalCount = 0;
		memcpy(drawFrameBuffer, rtfBuffer.convertedData, sizeof(drawFrameBuffer));		
	}
	else if (rtfBuffer.frameType == 0x01) {
		memcpy(calibData, rtfBuffer.convertedData, sizeof(calibData));
		//memcpy(drawFrameBuffer, rtfBuffer.convertedData, sizeof(drawFrameBuffer));
	}

	int lastPx = 0;
	for (int y = 0; y < hei; y++)
	{
		for (int x = 0; x < len; x++)
		{
			pt++;
			UINT16 currentPx = drawFrameBuffer[y * 208 + x];
			currentPx = ((calibData[y * 208 + x]) * 1.25) - currentPx;

			int drawPosX = (x * 2);
			int drawPosY = (y * 2);

			if (currentPx >= 1000 && currentPx <= 12000) {
				if (currentPx < tMin) { tMin = currentPx; }
				if (currentPx > tMax) { tMax = currentPx; }

				int vec = fMax - fMin;
				if (vec <= 0) { vec = 1; }
				int pix = (currentPx - fMin) * 255 / vec;
				if (pix > 254) { pix = 254; }
				if (pix < 0) { pix = 0; }

				if (vec <= 0) { vec = 1; }

				D3DCOLOR tmp = (D3DCOLOR)(paletteLookup[(thermalPalette * 255) + pix]);
				lastPx = pix;
				DrawFilledRect(drawPosX, drawPosY, 2, 2, tmp, pDevice);

				totalVal += pix;
				totalCount++;

			}
			else {
				D3DCOLOR tmp = (D3DCOLOR)(paletteLookup[(thermalPalette * 255) + lastPx]);
				DrawFilledRect(drawPosX, drawPosY, 2, 2, tmp, pDevice);
			}
		}
	}

	if (rtfBuffer.frameType != 0x03) {
		DrawTextC("Calibrating...", 10, 27, 20, red, pDevice);
	}

	if (totalCount != 0) {
		averageVal = totalVal / totalCount;
		std::cout << std::to_string(averageVal) << std::endl;
	}


	fMin = tMin;
	fMax = tMax;

	//END
	DrawTextC(exTimeTxt, 10, 10, 17, green, pDevice);
	pDevice->EndScene();
	pDevice->Present( 0, 0, 0, 0 );
	auto endTime = fpsTimer.now();
	eTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f; 
	sprintf_s(exTimeTxt, 256, "FPS : %i", (int)(1000.f / eTime));
}

FILE* createConsole() {
	AllocConsole();
	std::wstring strW = L"WinSeek";
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
	return f;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	createConsole();
	NativeWindow wnd;
	wnd.Create( hInstance, nCmdShow );

	oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(wnd.GetHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hWndProc)));
	sprintf_s(title, 64, "WinSeek | Palette %i", thermalPalette);
	SetWindowTextA(wnd.GetHandle(), title);

	initWinusb(&STC);

	std::cout << "frame buffer: " << std::hex << &rtfBuffer.data << std::endl;

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