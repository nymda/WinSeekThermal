#pragma once
#include <d3dx9.h>
#include <d3dx9.h>
#include "drawing.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>
#include <chrono>
namespace fennUi {

	/*This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

	std::chrono::high_resolution_clock clock;

	enum buttonMode {
		BMODE_SINGLE,
		BMODE_CONSTANT
	};

	enum tAlign {
		ALIGN_CENTER,
		ALIGN_LEFT,
		ALIGN_RIGHT
	};

	POINT GetMousePos(HWND hWnd)
	{
		ShowCursor(FALSE);
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(hWnd, &cursorPos);
		return cursorPos;
	}

	struct preservedInfo {
		int uid;
		vec2 position;
		vec2 size;
	};

	class keyHandler {
	public:
		char lastKey;
		bool charSet = false;
		int lastCall = 0;
		SYSTEMTIME st;

		char* text;
		int* offset;
		uintptr_t activeControl;

	private:
		void push(char c) {
			*(text + *offset) = c;
			*offset = *offset + 1;
		}

		void bkspace() {
			if (*offset != 0) {
				*offset = *offset - 1;
				*(text + *offset) = 0x00;
			}
		}

	public:
		void disconnect() {
			text = nullptr;
			offset = nullptr;
			activeControl = (uintptr_t)nullptr;
		}

		void connect(char* arrayBegin, int* position, uintptr_t control) {
			text = arrayBegin;
			offset = position;
			activeControl = control;
		}

		void updateKey(UINT msg, WPARAM wparam, LPARAM lparam) {
			if (msg == WM_KEYDOWN && activeControl) {
				if (*offset > 128) {
					*offset = 128;
				}
				if (wparam == VK_BACK) {
					bkspace();
				}
				else if ((wparam >= 0x30 && wparam <= 0x39) || wparam == 0x20) {
					//numeric and space
					push((char)wparam);
				}
				else if (wparam >= 0x41 && wparam <= 0x5A) {
					//characters
					if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 || GetAsyncKeyState(VK_SHIFT)) {
						push((char)wparam);
					}
					else {
						push((char)(wparam + 0x20));
					}
				}
				else if (wparam == VK_RETURN || wparam == VK_ESCAPE) {
					this->disconnect();
				}
			}
			if (msg == WM_MOUSEWHEEL) {
				int d = GET_WHEEL_DELTA_WPARAM(wparam);
				if (d > 0) {
					std::cout << "Mouse up" << std::endl;
				}
				else {
					std::cout << "Mouse down" << std::endl;
				}
			}
		}
	};

	//handles mouse controls and other important shit
	//move to wndproc?
	class externalHandler {
	public:
		vec2 frameMousePos = { 0, 0 };
		bool mouseDown = false;
		bool lastMouseDown = false;
		int focusedId = -1;
		int focusedFunction = -1;
		bool mouseIsOnControl = false;
		bool controlIsInUse = false;

		bool mouseHasJustClicked() {
			if (mouseDown != lastMouseDown && !lastMouseDown) {
				return true;
			}
			return false;
		}

		void update(HWND hWnd, LPDIRECT3DDEVICE9 pDev) {
			pDev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
			lastMouseDown = mouseDown;
			POINT tmp = GetMousePos(hWnd);
			frameMousePos = { (float)tmp.x, (float)tmp.y };
			mouseDown = (((GetAsyncKeyState(VK_LBUTTON) >> 15) & 0x0001) == 0x0001);
			if (!mouseDown) {
				focusedId = -1;
				focusedFunction = -1;
			}
		}
	};

	void DrawLine2(IDirect3DDevice9* m_pD3Ddev, float X, float Y, float X2, float Y2, D3DCOLOR Color)
	{
		Vert pVertex[2] = { { X, Y, 0.0f, 1.0f, Color }, { X2, Y2, 0.0f, 1.0f, Color } };
		m_pD3Ddev->DrawPrimitiveUP(D3DPT_LINELIST, 1, &pVertex, sizeof(Vert));
	}

	void drawCursor(externalHandler* pmg, LPDIRECT3DDEVICE9 pDev) {

		float X = pmg->frameMousePos.x;
		float Y = pmg->frameMousePos.y;

		Vert cursorMain_W = { X, Y, 0.0f, 1.0f, white };
		Vert cursorBL_W = { X + 6, Y + 16, 0.0f, 1.0f, white };
		Vert cursorC_W = { X + 9, Y + 9, 0.0f, 1.0f, white };
		Vert cursorBR_W = { X + 16, Y + 6, 0.0f, 1.0f, white };

		Vert cursorMain_B = { X, Y, 0.0f, 1.0f, black };
		Vert cursorBL_B = { X + 6, Y + 16, 0.0f, 1.0f, black };
		Vert cursorC_B = { X + 9, Y + 9, 0.0f, 1.0f, black };
		Vert cursorBR_B = { X + 16, Y + 6, 0.0f, 1.0f, black };

		Vert pVertex[6] = {
			cursorMain_W,
			cursorBL_W,
			cursorC_W,
			cursorMain_W,
			cursorBR_W,
			cursorC_W,
		};

		Vert pVertexOutline[5] = {
			cursorMain_B,
			cursorBL_B,
			cursorC_B,
			cursorBR_B,
			cursorMain_B,
		};

		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 6, pVertex, sizeof(Vert));
		pDev->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, pVertexOutline, sizeof(Vert));
	}

	void drawCursorRawCont(vec2 position, externalHandler* pmg, LPDIRECT3DDEVICE9 pDev) {

		pDev->SetTexture(NULL, NULL);

		float X = position.x;
		float Y = position.y;

		Vert cursorMain_W = { X, Y, 0.0f, 1.0f, white };
		Vert cursorBL_W = { X + 6, Y + 16, 0.0f, 1.0f, white };
		Vert cursorC_W = { X + 9, Y + 9, 0.0f, 1.0f, white };
		Vert cursorBR_W = { X + 16, Y + 6, 0.0f, 1.0f, white };

		Vert cursorMain_B = { X, Y, 0.0f, 1.0f, black };
		Vert cursorBL_B = { X + 6, Y + 16, 0.0f, 1.0f, black };
		Vert cursorC_B = { X + 9, Y + 9, 0.0f, 1.0f, black };
		Vert cursorBR_B = { X + 16, Y + 6, 0.0f, 1.0f, black };

		Vert pVertex[6] = {
			cursorMain_W,
			cursorBL_W,
			cursorC_W,
			cursorMain_W,
			cursorBR_W,
			cursorC_W,
		};

		Vert pVertexOutline[5] = {
			cursorMain_B,
			cursorBL_B,
			cursorC_B,
			cursorBR_B,
			cursorMain_B,
		};

		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, pVertex, sizeof(Vert));
		pDev->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, pVertexOutline, sizeof(Vert));
	}

	bool isPointInRegion(vec2 point, vec2 top, int width, int height) {
		if (point.x > top.x && point.y > top.y && point.x < (top.x + width) && point.y < (top.y + height)) {
			return true;
		}
		return false;
	}

	vec2 getOffset(vec2 cursor, vec2 wndPos) {
		return { cursor.x - wndPos.x, cursor.y - wndPos.y };
	}

	//easy-ish struct for handling strings. 128 bytes.
	struct packagedText {
		char labelText[128];
	};

	class textInputBox {
	public:
		bool enabled = true;
		vec2 position;
		vec2 size;
		vec2 relPos;
		buttonMode mode;
		bool* val;
		tAlign alignment;
		fennUi::keyHandler* khandler;
		int cursoroffset = 0;

		int selectionPositionPointer = 0;
		char text[128];

		bool isHover(externalHandler* ehnd) {
			if (isPointInRegion(ehnd->frameMousePos, relPos, size.x, size.y)) {
				return true;
			}
			return false;
		}

		bool isClicked(externalHandler* ehnd) {
			if (isHover(ehnd) && ehnd->mouseDown) {
				return true;
			}
			return false;
		}

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition, int yOffset) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };

			if (ehnd->mouseHasJustClicked() && !this->isHover(ehnd)) {
				if (khandler->activeControl == (uintptr_t)this) {
					khandler->disconnect();
				}
			}

			if (this->isHover(ehnd) && this->isClicked(ehnd)) {
				//this textbox takes input
				khandler->connect(text, &selectionPositionPointer, (uintptr_t)this);
			}

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(text, relPos.x + (size.x / 2), relPos.y + (size.y / 2), 15, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(text, relPos.x + 4, relPos.y + 3, 15, DT_LEFT, black, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(text, relPos.x + size.x - 4, relPos.y + 3, 15, DT_RIGHT, black, pDev);
				break;
			}

			if (khandler->activeControl == (uintptr_t)this) {
				drawRect(relPos, size.x, size.y - 1, green, pDev);
			}
			else {
				drawRect(relPos, size.x, size.y - 1, black, pDev);
			}
		}
	};

	class button {
	public:
		bool enabled = true;
		vec2 position;
		vec2 size;
		vec2 relPos;
		const char* label;
		buttonMode mode;
		bool* val;
		tAlign alignment;

		bool isHover(externalHandler* ehnd) {
			if (isPointInRegion(ehnd->frameMousePos, relPos, size.x, size.y)) {
				return true;
			}
			return false;
		}

		bool isClicked(externalHandler* ehnd) {
			if (isHover(ehnd) && ehnd->mouseDown) {
				return true;
			}
			return false;
		}

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition, int yOffset) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };

			if (!enabled) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				drawRect(relPos, size.x, size.y - 1, black, pDev);
				return;
			}

			if (this->isHover(ehnd)) {
				ehnd->mouseIsOnControl = true;
			}

			if (this->isHover(ehnd) && this->isClicked(ehnd)) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				if (mode == BMODE_SINGLE) {
					if (ehnd->mouseHasJustClicked()) {
						*val = true;
					}
					else {
						*val = false;
					}
				}
				else if (mode == BMODE_CONSTANT) {
					*val = true;
				}
			}
			else if (this->isHover(ehnd)) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, lightGrey, pDev);
			}
			else {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, white, pDev);
			}

			if (!this->isClicked(ehnd)) {
				*val = false;
			}

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(label, relPos.x + (size.x / 2), relPos.y + (size.y / 2), 15, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(label, relPos.x + 2, relPos.y + 2, 15, DT_LEFT, black, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(label, relPos.x + size.x - 2, relPos.y + 2, 15, DT_RIGHT, black, pDev);
				break;
			}

			drawRect(relPos, size.x, size.y - 1, black, pDev);
		}
	};

	class checkbox {
	public:
		bool enabled = true;
		vec2 position;
		vec2 size;
		vec2 relPos;
		bool* val;
		const char* label;
		tAlign alignment;

		bool isHover(externalHandler* ehnd) {
			if (isPointInRegion(ehnd->frameMousePos, relPos, size.x, size.y)) {
				return true;
			}
			return false;
		}

		bool isClicked(externalHandler* ehnd) {
			if (isHover(ehnd) && ehnd->mouseDown) {
				return true;
			}
			return false;
		}

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition, int yOffset) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };

			if (!enabled) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				drawRect(relPos, size.x, size.y - 1, black, pDev);
				return;
			}

			if (this->isHover(ehnd)) {
				ehnd->mouseIsOnControl = true;
			}

			if (this->isHover(ehnd) && this->isClicked(ehnd)) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				if (ehnd->mouseHasJustClicked()) {
					*val = !*val;
				}
			}
			else if (this->isHover(ehnd)) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, lightGrey, pDev);
			}
			else {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, white, pDev);
			}

			DrawFilledRect(relPos.x + 2, relPos.y + 2, size.y - 4, size.y - 4, grey, pDev);

			if (*val) { DrawFilledRect(relPos.x + 4, relPos.y + 4, size.y - 8, size.y - 8, white, pDev); }

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(label, relPos.x + (size.x / 2), relPos.y + (size.y / 2), 15, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(label, relPos.x + size.y + 2, relPos.y + 3, 15, DT_LEFT, black, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(label, relPos.x + size.x - 2, relPos.y + 3, 15, DT_RIGHT, black, pDev);
				break;
			}


			drawRect(relPos, size.x, size.y - 1, black, pDev);
		}
	};

	class radioButton {
	public:
		bool enabled = true;
		vec2 position;
		vec2 size;
		vec2 relPos;
		const char* label;
		std::vector<bool*> allItems;
		bool* myItem;
		tAlign alignment;

		bool isHover(externalHandler* ehnd) {
			if (isPointInRegion(ehnd->frameMousePos, relPos, size.x, size.y)) {
				return true;
			}
			return false;
		}

		bool isClicked(externalHandler* ehnd) {
			if (isHover(ehnd) && ehnd->mouseDown) {
				return true;
			}
			return false;
		}

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition, int yOffset) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };

			if (!enabled) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				drawRect(relPos, size.x, size.y - 1, black, pDev);
				return;
			}

			if (this->isHover(ehnd)) {
				ehnd->mouseIsOnControl = true;
			}

			if (this->isHover(ehnd) && this->isClicked(ehnd)) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				if (ehnd->mouseHasJustClicked()) {
					for (bool* itm : allItems) {
						*itm = false;
					}

					*myItem = true;
				}
			}
			else if (this->isHover(ehnd)) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, lightGrey, pDev);
			}
			else {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, white, pDev);
			}

			drawCircleFilledD3D(relPos.x + (size.y / 2), relPos.y + (size.y / 2), (size.y / 2) - 2, 15, grey, pDev);

			if (*myItem) { drawCircleFilledD3D(relPos.x + (size.y / 2), relPos.y + (size.y / 2), (size.y / 2) - 4, 15, white, pDev); }

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(label, relPos.x + (size.x / 2), relPos.y + (size.y / 2), 15, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(label, relPos.x + size.y + 2, relPos.y + 3, 15, DT_LEFT, black, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(label, relPos.x + size.x - 2, relPos.y + 3, 15, DT_RIGHT, black, pDev);
				break;
			}

			drawRect(relPos, size.x, size.y - 1, black, pDev);
		}
	};

	class floatSlider {
		float sliderPosOffset = 0;
		bool hold = false;
		bool active = false;

	public:
		bool enabled = true;
		const char* label;
		vec2 position;
		vec2 size;
		vec2 relPos;
		float max;
		float min;
		float* output;
		tAlign alignment;

		bool isHover(externalHandler* ehnd) {
			if (isPointInRegion(ehnd->frameMousePos, relPos, size.x, size.y)) {
				return true;
			}
			return false;
		}

		bool isClicked(externalHandler* ehnd) {
			if (isHover(ehnd) && ehnd->mouseDown) {
				return true;
			}
			return false;
		}

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };
			float pixelValue = (max - min) / size.x;

			if (!enabled) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, darkGrey, pDev);
				drawRect(relPos, size.x, size.y - 1, black, pDev);
				return;
			}

			if (ehnd->mouseHasJustClicked() && this->isHover(ehnd)) {
				active = true;
			}
			if (!ehnd->mouseDown) {
				active = false;
			}

			if (this->isHover(ehnd) || hold) {
				ehnd->mouseIsOnControl = true;
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, lightGrey, pDev);
				if (ehnd->mouseDown && active) {
					hold = true;
					float newPosOffset = (ehnd->frameMousePos.x) - relPos.x;
					if (newPosOffset < 0.f) {
						newPosOffset = 0.f;
						*output = min;
					}
					else if (newPosOffset > size.x) {
						newPosOffset = size.x;
						*output = max;
					}
					else {
						*output = min + (pixelValue * newPosOffset);
					}
				}
			}
			else {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, white, pDev);
			}

			if (!ehnd->mouseDown) {
				hold = false;
			}
			std::string strVal = std::to_string(*output);
			int index = strVal.find(".", 0);

			if (*output == max) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y - 1.f, grey, pDev);
			}
			else {
				sliderPosOffset = ((*output - min) / pixelValue);
				DrawFilledRect(relPos.x, relPos.y, sliderPosOffset, size.y - 1.f, grey, pDev);
			}

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(strVal.substr(0, index + 4).c_str(), relPos.x + (size.x / 2), relPos.y + (size.y / 2), 15, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(strVal.substr(0, index + 4).c_str(), relPos.x + 2, relPos.y + 3, 15, DT_LEFT, black, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(strVal.substr(0, index + 4).c_str(), relPos.x + size.x - 2, relPos.y + 3, 15, DT_RIGHT, black, pDev);
				break;
			}

			drawRect(relPos, size.x, size.y - 1, black, pDev);
		}
	};

	class intSlider {
		float sliderPosOffset = 0;
		bool hold = false;
		bool active = false;

	public:
		bool enabled = true;
		const char* label;
		vec2 position;
		vec2 size;
		vec2 relPos;
		int max;
		int min;
		int* output;
		tAlign alignment;

		bool isHover(externalHandler* ehnd) {
			if (isPointInRegion(ehnd->frameMousePos, relPos, size.x, size.y)) {
				return true;
			}
			return false;
		}

		bool isClicked(externalHandler* ehnd) {
			if (isHover(ehnd) && ehnd->mouseDown) {
				return true;
			}
			return false;
		}

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };
			float pixelValue = (max - min) / size.x;

			if (ehnd->mouseHasJustClicked() && this->isHover(ehnd)) {
				active = true;
			}
			if (!ehnd->mouseDown) {
				active = false;
			}

			if (this->isHover(ehnd) || hold) {
				ehnd->mouseIsOnControl = true;
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, lightGrey, pDev);
				if (ehnd->mouseDown && active) {
					hold = true;
					float newPosOffset = (ehnd->frameMousePos.x) - relPos.x;
					if (newPosOffset < 0.f) {
						newPosOffset = 0.f;
						*output = min;
					}
					else if (newPosOffset > size.x) {
						newPosOffset = size.x;
						*output = max;
					}
					else {
						*output = min + (int)floor(pixelValue * newPosOffset);
					}
				}
			}
			else {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y, white, pDev);
			}

			if (!ehnd->mouseDown) {
				hold = false;
			}

			if (*output == max) {
				DrawFilledRect(relPos.x, relPos.y, size.x, size.y - 1.f, grey, pDev);
			}
			else {
				sliderPosOffset = ((*output - min) / pixelValue);
				DrawFilledRect(relPos.x, relPos.y, sliderPosOffset, size.y - 1.f, grey, pDev);
			}

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(std::to_string(*output).c_str(), relPos.x + (size.x / 2), relPos.y + (size.y / 2), 15, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(std::to_string(*output).c_str(), relPos.x + 2, relPos.y + 3, 15, DT_LEFT, black, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(std::to_string(*output).c_str(), relPos.x + size.x - 2, relPos.y + 3, 15, DT_RIGHT, black, pDev);
				break;
			}

			drawRect(relPos, size.x, size.y - 1, black, pDev);
		}
	};

	class flabel {
	public:
		bool enabled = true;
		packagedText* text;
		vec2 position;
		vec2 relPos;
		int fontSize;
		tAlign alignment;

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };
			DrawTextC(text->labelText, relPos.x, relPos.y, fontSize, DT_LEFT, white, pDev);

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(text->labelText, relPos.x, relPos.y, fontSize, (DT_VCENTER | DT_CENTER), black, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(text->labelText, relPos.x, relPos.y, fontSize, DT_LEFT, white, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(text->labelText, relPos.x, relPos.y, fontSize, DT_RIGHT, white, pDev);
				break;
			}

		}
	};

	class blabel {
	public:
		bool enabled = true;
		const char* text;
		vec2 position;
		vec2 relPos;
		int fontSize;
		tAlign alignment;

		void draw(externalHandler* ehnd, LPDIRECT3DDEVICE9 pDev, vec2 parentPosition) {
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };

			switch (alignment) {
			case ALIGN_CENTER:
				DrawTextC(text, relPos.x, relPos.y, fontSize, (DT_VCENTER | DT_CENTER), white, pDev);
				break;

			case ALIGN_LEFT:
				DrawTextC(text, relPos.x, relPos.y, fontSize, DT_LEFT, white, pDev);
				break;

			case ALIGN_RIGHT:
				DrawTextC(text, relPos.x, relPos.y, fontSize, DT_RIGHT, white, pDev);
				break;
			}
		}
	};

	class container {
		LPDIRECT3DDEVICE9 pDev;
		vec2 position;
		vec2 relPos;
		vec2 size;
		int uid;

	public:
		bool enabled = true;
		bool outline = false;
		std::vector<button> objButtons = {};
		std::vector<textInputBox> objTextBoxes = {};
		std::vector<checkbox> objCheckbox = {};
		std::vector<radioButton> objRadioButtons = {};
		std::vector<floatSlider> objFloatSliders = {};
		std::vector<intSlider> objIntSliders = {};
		std::vector<flabel> objLabels = {};
		std::vector<blabel> objBasicLabels = {};

		void init(vec2 startPosition, vec2 startSize, int uid, LPDIRECT3DDEVICE9 pDev) {
			this->position = startPosition;
			this->size = startSize;
			this->uid = uid;
			this->pDev = pDev;
		}

		void addButton(const char* label, vec2 pos, float width, buttonMode mode, bool* out, tAlign alignment = ALIGN_CENTER) {
			button tmp;
			tmp.label = label;
			tmp.position = pos;
			tmp.size = { width, 20 };
			tmp.mode = mode;
			tmp.val = out;
			tmp.alignment = alignment;
			objButtons.push_back(tmp);
		}

		void addTextbox(const char* label, vec2 pos, float width, fennUi::keyHandler* khandler, tAlign alignment = ALIGN_LEFT) {
			textInputBox tmp;
			tmp.position = pos;
			tmp.size = { width, 20 };
			tmp.alignment = alignment;
			tmp.khandler = khandler;
			objTextBoxes.push_back(tmp);
		}

		void addCheckbox(const char* label, vec2 pos, float width, bool* out, tAlign alignment = ALIGN_CENTER) {
			checkbox tmp;
			tmp.label = label;
			tmp.position = pos;
			tmp.size = { width, 20 };
			tmp.val = out;
			tmp.alignment = alignment;
			objCheckbox.push_back(tmp);
		}

		void addRadioButton(const char* label, vec2 pos, float width, bool* out, std::vector<bool*> allItems, tAlign alignment = ALIGN_CENTER) {
			radioButton tmp;
			tmp.label = label;
			tmp.position = pos;
			tmp.size = { width, 20 };
			tmp.myItem = out;
			tmp.allItems = allItems;
			tmp.alignment = alignment;
			objRadioButtons.push_back(tmp);
		}

		void addFloatSlider(vec2 pos, float width, float min, float max, float* output, tAlign alignment = ALIGN_CENTER) {
			floatSlider tmp;
			tmp.position = pos;
			tmp.size = { width, 20 };
			tmp.min = min;
			tmp.max = max;
			tmp.output = output;
			tmp.alignment = alignment;
			objFloatSliders.push_back(tmp);
		}

		void addIntSlider(vec2 pos, float width, int min, int max, int* output, tAlign alignment = ALIGN_CENTER) {
			intSlider tmp;
			tmp.position = pos;
			tmp.min = min;
			tmp.size = { width, 20 };
			tmp.max = max;
			tmp.output = output;
			tmp.alignment = alignment;
			objIntSliders.push_back(tmp);
		}

		void addLabel(packagedText* plt, vec2 pos, int fontSize, tAlign alignment = ALIGN_LEFT) {
			flabel tmp;
			tmp.text = plt;
			tmp.position = pos;
			tmp.fontSize = fontSize;
			tmp.alignment = alignment;
			objLabels.push_back(tmp);
		}


		void addBasicLabel(const char* plt, vec2 pos, int fontSize, tAlign alignment = ALIGN_LEFT) {
			blabel tmp;
			tmp.text = plt;
			tmp.position = pos;
			tmp.fontSize = fontSize;
			tmp.alignment = alignment;
			objBasicLabels.push_back(tmp);
		}


		void draw(externalHandler* ehnd, vec2 parentPosition) {
			if (!enabled) {
				return;
			}
			relPos = { parentPosition.x + position.x, parentPosition.y + position.y };
			DrawFilledRect(relPos.x, relPos.y, size.x, size.y, grey, pDev);

			for (button& i : objButtons) {
				i.draw(ehnd, pDev, relPos, 0);
			}
			for (textInputBox& i : objTextBoxes) {
				i.draw(ehnd, pDev, relPos, 0);
			}
			for (checkbox& i : objCheckbox) {
				i.draw(ehnd, pDev, relPos, 0);
			}
			for (radioButton& i : objRadioButtons) {
				i.draw(ehnd, pDev, relPos, 0);
			}
			for (floatSlider& i : objFloatSliders) {
				i.draw(ehnd, pDev, relPos);
			}
			for (intSlider& i : objIntSliders) {
				i.draw(ehnd, pDev, relPos);
			}
			for (flabel& i : objLabels) {
				i.draw(ehnd, pDev, relPos);
			}
			for (blabel& i : objBasicLabels) {
				i.draw(ehnd, pDev, relPos);
			}

			if (outline) {
				drawRect(relPos, size.x, size.y, white, pDev);
			}
		}
	};

	class basicWindow {
		bool* masterswitch;
		vec2 position;
		vec2 size;
		const char* label;
		vec2 mouseStoredOffset;
		int uid;
		LPDIRECT3DDEVICE9 pDev;
		std::vector<container*> containers = {};
		fennUi::keyHandler* keyHandler;
		fennUi::externalHandler* ehnd;

	public:
		bool resizable = true;

		void init(const char* label, vec2 startPosition, vec2 startSize, int uid, bool* masterswitch, fennUi::externalHandler* ehnd, fennUi::keyHandler* keyHandler, LPDIRECT3DDEVICE9 pDev) {
			this->masterswitch = masterswitch;
			this->position = startPosition;
			this->label = label;
			this->size = startSize;
			this->uid = uid;
			this->pDev = pDev;
			this->ehnd = ehnd;
			this->keyHandler = keyHandler;
		}

		void addContainer(container* container) {
			this->containers.push_back(container);
		}

		void draw() {
			if (!*masterswitch) {
				keyHandler->disconnect();
				return;
			}

			if (ehnd->mouseDown) {
				if (resizable && ehnd->focusedId == -1 && ehnd->mouseHasJustClicked() && isPointInRegion(ehnd->frameMousePos, { this->position.x + this->size.x - 20,  this->position.y + this->size.y - 20 }, 20, 20)) {
					this->mouseStoredOffset = getOffset(ehnd->frameMousePos, this->position);
					ehnd->focusedId = uid;
					ehnd->focusedFunction = 1;
				}
				if (ehnd->focusedId == uid && ehnd->focusedFunction == 1 && resizable) {
					vec2 newSize = { 0, 0 };

					newSize.x = ((ehnd->frameMousePos.x + 10) - this->position.x);
					newSize.y = ((ehnd->frameMousePos.y + 10) - this->position.y);

					if (newSize.x > 50) {
						this->size.x = newSize.x;
					}
					if (newSize.y > 50) {
						this->size.y = newSize.y;
					}
				}

				if (ehnd->focusedId == -1 && ehnd->mouseHasJustClicked() && isPointInRegion(ehnd->frameMousePos, position, size.x, size.y) && !ehnd->mouseIsOnControl) {
					this->mouseStoredOffset = getOffset(ehnd->frameMousePos, this->position);
					ehnd->focusedId = uid;
					ehnd->focusedFunction = 2;
				}
				if (ehnd->focusedId == uid && ehnd->focusedFunction == 2 && !ehnd->mouseIsOnControl) {
					position.x = (ehnd->frameMousePos.x - mouseStoredOffset.x);
					position.y = (ehnd->frameMousePos.y - mouseStoredOffset.y);
				}
			}

			DrawFilledRect(position.x, position.y, size.x, size.y, grey, pDev);
			if (resizable) { DrawFilledRect(position.x + size.x - 20, position.y + size.y - 20, 20, 20, white, pDev); }
			DrawTextC(label, position.x + (size.x / 2), position.y + 5, 19, (DT_TOP | DT_CENTER), white, pDev);
			DrawLine(position.x, position.y + 25, position.x + size.x, position.y + 25, 1, white, pDev);

			ehnd->mouseIsOnControl = false;
			for (container* cnt : containers) {
				cnt->draw(ehnd, position);
			}

			drawRect(position, size.x, size.y, white, pDev);
		}
	};

	//basic container for adding controls to the background d3d window
	class universialWindow {
		vec2 mouseStoredOffset;
		int uid;
		LPDIRECT3DDEVICE9 pDev;
		std::vector<container*> containers = {};
		fennUi::keyHandler* keyHandler;
		fennUi::externalHandler* ehnd;
		vec2 position;

	public:
		bool resizable = true;

		void init(vec2 position, int uid, fennUi::externalHandler* ehnd, fennUi::keyHandler* keyHandler, LPDIRECT3DDEVICE9 pDev) {
			this->position = position;
			this->uid = uid;
			this->pDev = pDev;
			this->ehnd = ehnd;
			this->keyHandler = keyHandler;
		}

		void addContainer(container* container) {
			this->containers.push_back(container);
		}

		void draw() {
			for (container* cnt : containers) {
				cnt->draw(ehnd, position);
			}
		}
	};
}