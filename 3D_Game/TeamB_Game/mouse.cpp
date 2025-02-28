#include "mouse.h"

LPDIRECTINPUT8 g_pInputInterface = NULL;
LPDIRECTINPUTDEVICE8 g_pMouseDevice = NULL;
DIMOUSESTATE g_MouseState;
DIMOUSESTATE g_MouseOldState;
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//�L�[�{�[�h������
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputInterface, NULL)))
	{
		return E_FAIL;
	}
	//
	if (FAILED(g_pInputInterface->CreateDevice(GUID_SysMouse, &g_pMouseDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pMouseDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pMouseDevice->Acquire();

	return S_OK;
}
void UninitMouse(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pMouseDevice != NULL)
	{
		g_pMouseDevice->Unacquire();
		g_pMouseDevice->Release();
		g_pMouseDevice = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInputInterface != NULL)
	{
		g_pInputInterface->Release();
		g_pInputInterface = NULL;
	}
}
void UpdateMouse(void)
{
	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	g_MouseOldState = g_MouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
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
// �N���b�N�����u�Ԃ̔���
bool OnMouseDown(int button_type)
{
	if (!(g_MouseOldState.rgbButtons[button_type] & (0x80)) &&
		g_MouseState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}
// �ړ��ʂ̎擾
D3DXVECTOR2 GetMouseVelocity(void)
{
	return D3DXVECTOR2((float)g_MouseState.lX, (float)g_MouseState.lY);
}