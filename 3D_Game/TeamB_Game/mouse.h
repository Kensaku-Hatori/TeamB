#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "main.h"

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool OnMouseDown(int button_type);
D3DXVECTOR2 GetMouseVelocity(void);
#endif // !_MOUSE_H_