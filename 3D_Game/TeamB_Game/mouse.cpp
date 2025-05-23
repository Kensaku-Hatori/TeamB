//**************************************
// 
// Author: HATORI
// マウス関係の処理をまとめた[mouse.cpp]
// 
//**************************************
#include "mouse.h"

LPDIRECTINPUT8 g_pInputInterface = NULL;
LPDIRECTINPUTDEVICE8 g_pMouseDevice = NULL;
DIMOUSESTATE g_MouseState;
DIMOUSESTATE g_MouseOldState;
//*******************
// マウスの初期化処理
//*******************
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//キーボード初期化
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputInterface, NULL)))
	{
		return E_FAIL;
	}
	//
	if (FAILED(g_pInputInterface->CreateDevice(GUID_SysMouse, &g_pMouseDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pMouseDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pMouseDevice->Acquire();

	return S_OK;
}
//*****************
// マウスの終了処理
//*****************
void UninitMouse(void)
{
	//入力デバイスの破棄
	if (g_pMouseDevice != NULL)
	{
		g_pMouseDevice->Unacquire();
		g_pMouseDevice->Release();
		g_pMouseDevice = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (g_pInputInterface != NULL)
	{
		g_pInputInterface->Release();
		g_pInputInterface = NULL;
	}
}
//*****************
// マウスの更新処理
//*****************
void UpdateMouse(void)
{
	// 更新前に最新マウス情報を保存する
	g_MouseOldState = g_MouseState;

	// 最新のマウスの状態を更新
	HRESULT	hr = g_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_MouseState);
	if (FAILED(hr))
	{
		g_pMouseDevice->Acquire();
	}
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(FindWindowA(CLASS_NAME, WINDOW_NAME), &p);
	g_MouseState.lX = p.x;
	g_MouseState.lY = p.y;
}
//***********************************
// マウスのボタンを押している間の処理
//***********************************
bool OnMousePress(int button_type)
{
	return(g_MouseState.rgbButtons[button_type] & (0x80)) ? true : false;
}
//*********************************
// マウスのボタンを押した瞬間の処理
//*********************************
bool OnMouseDown(int button_type)
{
	if (!(g_MouseOldState.rgbButtons[button_type] & (0x80)) &&
		g_MouseState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}
//*********************************
// マウスのボタンを離した瞬間の処理
//*********************************
bool OnMouseUp(int button_type)
{
	if (g_MouseOldState.rgbButtons[button_type] & (0x80) &&
		!(g_MouseState.rgbButtons[button_type] & (0x80)))
	{
		return true;
	}

	return false;
}
//*******************************
// マウスのOldStageを取得する処理
//*******************************
D3DXVECTOR2 GetMouseVelocityOld(void)
{
	return D3DXVECTOR2((float)g_MouseOldState.lX, (float)g_MouseOldState.lY);
}
//****************************
// マウスのStageを取得する処理
//****************************
D3DXVECTOR2 GetMouseVelocity(void)
{
	return D3DXVECTOR2((float)g_MouseState.lX, (float)g_MouseState.lY);
}