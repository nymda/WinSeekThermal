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
#include <vector>
#include "ui.h"
#include <thread>
#include "Windows.h"
#include <TlHelp32.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

bool PROGRAM_IS_TERMINATING = false;

std::chrono::high_resolution_clock fpsTimer;
float eTime = 0.f;
float dTime = 0.f;
char exTimeTxt[64]{ 0 };
char title[64]{ 0 };
WNDPROC oWndProc;

IDirect3D9* pD3d = nullptr;
IDirect3DDevice9* pDevice = nullptr;
ID3DXFont* pFont = nullptr;
ID3DXSprite* pSprite = nullptr;
seekThermalCamera STC{};
int thermalPalette = 0;

fennUi::externalHandler exhndlr;
fennUi::universialWindow UWData;
fennUi::keyHandler khndlr;
fennUi::container backgroundItems;
bool firstFrame = true;

LRESULT APIENTRY hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	khndlr.updateKey(uMsg, wParam, lParam);
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_UP)
		{
			//thermalPalette++;
		}
		if (wParam == VK_DOWN)
		{
			//thermalPalette--;
		}
		//sprintf_s(title, 64, "WinSeek | Palette %i", thermalPalette);
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

IDirect3DSurface9* surface;
IDirect3DSurface9* surface_large;
const RECT frameDrawingTemplate = { 0, 0, 206, 156 };
const RECT thermalWindow = { 25, 25, 618, 468 };
D3DLOCKED_RECT drawCanvas;

int len = 206;
int hei = 155;
int fMin = 12000;
int fMax = 0;
USHORT calibData[32448]{};
USHORT thermFrameBuffer[32448];
USHORT calibratedBuffer[32448];

int lastAverage = 0;
int totalCount = 0;
int totalVal = 0;
int averageVal = 1;
LPDIRECT3DSURFACE9 backbuffer;
coord badPixelMap[2048]{}; //if there are more than 2048 dead pixels then it will throw an access violation, but your camera is fucked soooo....
int frameCount = 0;

bool isInBounds(UINT16 val, UINT16 upper, UINT16 lower) {
	if ((val > upper || val < lower)) {
		return false;
	}
	return true;
}

int knownBadPixelNumber = 0;
bool isKnownBadPixel(coord c) {
	for (int i = 0; i < knownBadPixelNumber; i++) {
		coord current = badPixelMap[i];
		if (current.x == c.x && current.y == c.y) {
			return true;
		}
	}
	return false;
}

void threadRetrieveFrame() {
	while (true) {
		STC.getFrame(&rtfBuffer);
		if (PROGRAM_IS_TERMINATING) {
			return;
		}
	}
}

int tMin = 12000;
int tMax = 0;
bool autoCalibrate = true;

bool setP1 = true;
bool setP2 = false;
bool setP3 = false;
bool setP4 = false;

std::vector<bool*> items = { &setP1, &setP2, &setP3, &setP4 };

void Render(NativeWindow& wnd)
{
	if (firstFrame) {
		UWData.init({ 643, 25 }, 1, &exhndlr, &khndlr, pDevice);
		backgroundItems.init({ 0, 0 }, { 0, 0 }, 4, pDevice);
		backgroundItems.addBasicLabel(title, { 0, 0 }, 20);
		backgroundItems.addBasicLabel("Min:", { 0, 25 }, 20);
		backgroundItems.addBasicLabel("Max:", { 0, 50 }, 20);
		backgroundItems.addIntSlider({ 55, 25 }, 200, 1000, 12000, &tMin);
		backgroundItems.addIntSlider({ 55, 50 }, 200, 1000, 12000, &tMax);
		backgroundItems.addCheckbox("Auto calibrate", { 0, 75 }, 255, &autoCalibrate);

		backgroundItems.addRadioButton("black-hot", { 0, 100 }, 125, &setP1, items);
		backgroundItems.addRadioButton("white-hot", { 130, 100 }, 125, &setP2, items);
		backgroundItems.addRadioButton("iron", { 0, 125 }, 125, &setP3, items);
		backgroundItems.addRadioButton("rainbow", { 130, 125 }, 125, &setP4, items);

		UWData.addContainer(&backgroundItems);
		firstFrame = false;
	}

	exhndlr.update(wnd.GetHandle(), pDevice);
	auto startTime = fpsTimer.now();
	pDevice->BeginScene();
	pDevice->Clear( 1, nullptr, D3DCLEAR_TARGET, 0x00111111, 1.0f, 0 );
	//START


	if (setP1) {
		thermalPalette = 0;
	}
	else if (setP2) {
		thermalPalette = 1;
	}
	else if (setP3) {
		thermalPalette = 2;
	}
	else if (setP4) {
		thermalPalette = 3;
	}

	sprintf_s(title, 64, "WinSeek | Palette %i", thermalPalette);

#pragma region thermalFrameRendering
	int pt = 0;

	if (autoCalibrate) {
		tMin = 12000;
		tMax = 0;
	}

	UINT16 allowMin = 1000;
	UINT16 allowMax = 12000;

	struct fixedShade {
		byte brightness;
	};

	bool displayCalibFrames = false;

	if (rtfBuffer.frameType == 0x03 || displayCalibFrames) {
		totalVal = 0;
		totalCount = 0;
		frameCount++;
		memcpy(thermFrameBuffer, rtfBuffer.convertedData, sizeof(thermFrameBuffer));
	}
	if (rtfBuffer.frameType == 0x01) {
		memcpy(calibData, rtfBuffer.convertedData, sizeof(calibData));
	}
	
	auto drawStartTime = fpsTimer.now();
	surface->LockRect(&drawCanvas, &frameDrawingTemplate, D3DLOCK_DISCARD);
	char* data = (char*)drawCanvas.pBits;
	UCHAR lastPx = 0;

	//calibrated based on shutter frames before doing anything else
	for (int y = 0; y < hei; y++)
	{
		for (int x = 0; x < len; x++)
		{
			UINT16 calibValue = calibData[y * 208 + x];
			UINT16 intensityOffset = allowMax - calibValue;
			UINT16 currentPx = thermFrameBuffer[y * 208 + x];
			UINT16 calibratedPx = currentPx + intensityOffset;

			if ((calibratedPx >= 1000 && calibratedPx <= 12000)) {
				calibratedBuffer[y * 208 + x] = calibratedPx;
			}
			else {
				//invalid pixel
				calibratedBuffer[y * 208 + x] = 0x0000;
			}
		}
	}

	//using calibrated data, correct bad pixels and draw it
	UINT16 badPixelBound = 100;
	bool cPixelIsBad = false;
	bool skipAltBadPixDetection = false;
	
	for (int y = 0; y < hei; y++)
	{
		DWORD* row = (DWORD*)data;
		for (int x = 0; x < len; x++)
		{
			cPixelIsBad = false;
			if (isKnownBadPixel({ x, y })) {
				cPixelIsBad = true;
				skipAltBadPixDetection = true;
			}
			else {
				UINT16 calibratedPx = calibratedBuffer[y * 208 + x];
				if (calibratedPx != 0x0000) {
					if (x > 0 && x < len && y > 0 && y < len) {
						coord thisLocation = { x, y };
						coord upperLocation = { y - 1, x };
						coord lowerLocation = { y + 1, x };
						coord leftLocation = { y, x - 1 };
						coord rightLocation = { y, x + 1 };

						UINT16 upper = calibratedBuffer[(y + 1) * 208 + x];
						UINT16 lower = calibratedBuffer[(y - 1) * 208 + x];
						UINT16 left = calibratedBuffer[y * 208 + (x - 1)];
						UINT16 right = calibratedBuffer[y * 208 + (x + 1)];
						UINT16 avg_h = (right + left) / 2u;
						UINT16 avg_v = (upper + lower) / 2u;

						if (!isInBounds(calibratedPx, avg_h + badPixelBound, avg_h - badPixelBound) && !isInBounds(calibratedPx, avg_v + badPixelBound, avg_v - badPixelBound)) {
							cPixelIsBad = true;
						}
					}

					if (!cPixelIsBad) {
						if (calibratedPx < 12000 && autoCalibrate) {
							if (calibratedPx < tMin) { tMin = calibratedPx; }
							if (calibratedPx > tMax) { tMax = calibratedPx; }
						}

						int vec = ((fMax)-(fMin - 100));
						if (vec <= 0) { vec = 1; }
						int pix = (calibratedPx - fMin) * 256 / vec;
						if (pix > 256) { pix = 256; }
						if (pix < 0) { pix = 0; }

						*row++ = (paletteLookup[(thermalPalette * 256) + pix]);
						lastPx = pix;
					}
				}
				else {
					cPixelIsBad = true;
				}
			}
			
			if (cPixelIsBad) {
				if (!skipAltBadPixDetection) {
					if (!isKnownBadPixel({ x, y }) && frameCount > 10) {
						badPixelMap[knownBadPixelNumber] = { x, y };
						knownBadPixelNumber++;
						std::cout << "Added dead pixel: " << std::to_string(x) << ":" << std::to_string(y) << std::endl;
					}
				}

				*row++ = (paletteLookup[(thermalPalette * 256) + lastPx]);
			}
		}
		data += drawCanvas.Pitch;
	}

	surface->UnlockRect();

	auto drawEndTime = fpsTimer.now();
	fMin = tMin;
	fMax = tMax;

	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	pDevice->StretchRect(surface, NULL, backbuffer, &thermalWindow, D3DTEXF_POINT);
#pragma endregion

	UWData.draw();
	fennUi::drawCursor(&exhndlr, pDevice);

	//END
	//pDevice->Release();
	pDevice->EndScene();
	pDevice->Present( 0, 0, 0, 0 );

	auto endTime = fpsTimer.now();
	eTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f; 
	dTime = std::chrono::duration_cast<std::chrono::microseconds>(drawEndTime - drawStartTime).count() / 1000.f;
	std::cout << "Frame took " << dTime << " MS" << std::endl;
	//td::cout << "FPS " << 1000 / dTime << std::endl;
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

	initWinusb(&STC);
	std::thread frameGetter(threadRetrieveFrame);

	std::cout << "frame buffer: " << std::hex << &rtfBuffer.data << std::endl;

	if (!InitD3D( wnd.GetHandle(), WND_WIDTH, WND_HEIGHT ))
		return 1;

	pDevice->CreateOffscreenPlainSurface(206, 156, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);

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

	PROGRAM_IS_TERMINATING = true;
	frameGetter.join();
	return 0;
}