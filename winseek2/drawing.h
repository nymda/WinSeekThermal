#pragma once
#ifndef drawing
#define drawing
#include <d3d9.h>
#include <d3dx9.h>
#include "drawing.h"

struct Vert
{
	float x, y, z, ht;
	DWORD Color;
};

struct vec2 {
	float x;
	float y;
};

static D3DCOLOR red = D3DCOLOR_ARGB(255, 255, 0, 0);
static D3DCOLOR green = D3DCOLOR_ARGB(255, 0, 255, 0);
static D3DCOLOR blue = D3DCOLOR_ARGB(255, 0, 0, 255);
static D3DCOLOR white = D3DCOLOR_ARGB(255, 255, 255, 255);
static D3DCOLOR grey = D3DCOLOR_ARGB(255, 132, 132, 130);
static D3DCOLOR lightGrey = D3DCOLOR_ARGB(255, 180, 180, 180);
static D3DCOLOR darkGrey = D3DCOLOR_ARGB(255, 100, 100, 100);
static D3DCOLOR black = D3DCOLOR_ARGB(255, 0, 0, 0);

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev);

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color, IDirect3DDevice9* dev);

void DrawTextC(const char* text, float x, float y, int size, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);

void drawCircleD3D(float x, float y, float radius, int sides, float width, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void drawCircleFilledD3D(float x, float y, float radius, int sides, float width, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);

void drawRect(vec2 start, int width, int height, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);

void drawDbgEspBox(vec2 position, LPDIRECT3DDEVICE9 pDevice);

#endif