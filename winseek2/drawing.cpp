#include "drawing.h"
#include <vector>
#include <iostream>

void drawPolyFilledRect(vec2 p1, vec2 p2, vec2 p3, vec2 p4, D3DCOLOR color, IDirect3DDevice9* pDev) {
	Vert tri1[4]{
		{ p1.x, p1.y, 1.f, 0.f, color },
		{ p2.x, p2.y, 1.f, 0.f, color },
		{ p4.x, p4.y, 1.f, 0.f, color },
		{ p1.x, p1.y, 1.f, 0.f, color }
	};

	Vert tri2[4]{
		{ p1.x, p1.y, 1.f, 0.f, color },
		{ p4.x, p4.y, 1.f, 0.f, color },
		{ p3.x, p3.y, 1.f, 0.f, color },
		{ p1.x, p1.y, 1.f, 0.f, color }
	};

	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 3, tri1, sizeof(Vert));
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 3, tri2, sizeof(Vert));
}

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev)
{
	D3DRECT BarRect = { x, y, x + w, y + h };
	dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

ID3DXLine* LineL;
void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color, IDirect3DDevice9* dev) {

	if (!LineL) {
		D3DXCreateLine(dev, &LineL);
	}

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	LineL->SetWidth(thickness);
	LineL->Draw(Line, 2, color);
}

//draws a skeletal circle using drawPrimitiveUP
void drawCircleD3D(float x, float y, float radius, int sides, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	float angle = D3DX_PI * 2 / sides;
	float _cos = cos(angle);
	float _sin = sin(angle);
	float x1 = radius, y1 = 0, x2, y2;
	Vert* cVerts = new Vert[(sides + 1)];

	for (int i = 0; i < sides; i++)
	{
		x2 = _cos * x1 - _sin * y1 + x;
		y2 = _sin * x1 + _cos * y1 + y;
		x1 += x;
		y1 += y;
		cVerts[i] = { x1, y1, 0.f, 1.f, color };
		x1 = x2 - x;
		y1 = y2 - y;
	}
	cVerts[sides] = cVerts[0];
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, sides, cVerts, sizeof(Vert));
	free(cVerts);
}

//draws a filled circle using drawPrimitiveUP
void drawCircleFilledD3D(float x, float y, float radius, int sides, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	float angle = D3DX_PI * 2 / sides;
	float _cos = cos(angle);
	float _sin = sin(angle);
	float x1 = radius, y1 = 0, x2, y2;
	Vert* cVerts = new Vert[(sides * 3 + 3)];

	for (int i = 0; i < sides * 3; i++)
	{
		//every third loop, insert the center point for vertex 3 of this triangle
		if (i % 3 == 0) {
			cVerts[i] = { x, y, 0.f, 1.f, color };
		}
		else { //add the two other vertecies
			x2 = _cos * x1 - _sin * y1 + x;
			y2 = _sin * x1 + _cos * y1 + y;
			x1 += x;
			y1 += y;
			cVerts[i] = { x1, y1, 0.f, 1.f, color };
			x1 = x2 - x;
			y1 = y2 - y;
		}
	}
	//duplicate the first triangle to the last to close the circle
	cVerts[sides * 3] = cVerts[0];
	cVerts[sides * 3 + 1] = cVerts[1];
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, sides * 3, cVerts, sizeof(Vert));
	free(cVerts);
}


bool initFonts = true;
std::vector< ID3DXFont* > fonts = {};
int DrawTextC(const char* text, float x, float y, int size, int alignment, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	RECT rect;
	size -= 2;
	if (size < 1) {
		size = 1;
	}
	if (size > 20) {
		size = 20;
	}

	if (initFonts) {
		for (int i = 0; i < 20; i++) {
			ID3DXFont* tmpFont;
			D3DXCreateFontW(pDevice, i, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, L"Lucida console", &tmpFont);
			fonts.push_back(tmpFont);
		}
		initFonts = false;
	}

	SetRect(&rect, x, y, x, y);
	return fonts[size]->DrawTextA(NULL, text, -1, &rect, alignment | DT_NOCLIP, color);
}

//draw triangle, clockwise notation
void drawTriangle(float x, float y, float z, bool filled, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {

}

void drawRect(vec2 start, int width, int height, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	Vert rectVerts[5] = {
		{start.x, start.y, 0.0, 1.0, color},
		{start.x + width, start.y, 0.0, 1.0, color},
		{start.x + width, start.y + height, 0.0, 1.0, color},
		{start.x, start.y + height, 0.0, 1.0, color},
		{start.x, start.y, 0.0, 1.0, color},
	};
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, rectVerts, sizeof(Vert));
}

void drawDbgEspBox(vec2 position, LPDIRECT3DDEVICE9 pDevice) {
	vec2 dbgTop = { position.x - 10, position.y - 200 };
	vec2 dbgBottom = { position.x + 10, position.y };

	Vert rectVerts[6] = {
		{dbgTop.x, dbgTop.y + 25, 0.0, 1.0, white},
		{dbgTop.x, dbgTop.y, 0.0, 1.0, white},
		{dbgTop.x + 100, dbgTop.y, 0.0, 1.0, white},
		{dbgTop.x + 100, dbgTop.y + 200, 0.0, 1.0, white},
		{dbgTop.x, dbgTop.y + 200, 0.0, 1.0, white},
		{dbgTop.x, dbgTop.y + 175, 0.0, 1.0, white},
	};

	Vert rectVertsOut[6] = {
		{dbgTop.x - 1, dbgTop.y + 25, 0.0, 1.0, darkGrey},
		{dbgTop.x - 1, dbgTop.y - 1, 0.0, 1.0, darkGrey},
		{dbgTop.x + 101, dbgTop.y - 1, 0.0, 1.0, darkGrey},
		{dbgTop.x + 101, dbgTop.y + 201, 0.0, 1.0, darkGrey},
		{dbgTop.x - 1, dbgTop.y + 201, 0.0, 1.0, darkGrey},
		{dbgTop.x - 1, dbgTop.y + 175, 0.0, 1.0, darkGrey},
	};

	Vert rectVertsHP[6] = {
		{dbgTop.x, dbgTop.y + 30, 0.0, 1.0, red},
		{dbgTop.x, dbgTop.y + 172, 0.0, 1.0, red},
	};

	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 6, rectVerts, sizeof(Vert));
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 6, rectVertsOut, sizeof(Vert));
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, rectVertsHP, sizeof(Vert));
	DrawTextC("HK", dbgTop.x + 102, dbgTop.y - 3, 15, DT_LEFT, white, pDevice);
	DrawTextC("NAME", dbgTop.x - 1, dbgTop.y - 13, 15, DT_LEFT, white, pDevice);
}