//================================
//
//�@�E�C���h�E�\������[main.cpp]
//�@Author:kaiti
//
//================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "result.h"
#include "game.h"
#include "ranking.h"
#include "sound.h"
#include "particleEditer.h"

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;
LPD3DXFONT g_pFont;

//=============
// ���C���֐�
//=============
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR ipCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		                  CLASS_NAME,
		                  WINDOW_NAME,
		                  WS_OVERLAPPEDWINDOW,
		                  CW_USEDEFAULT,
		                  CW_USEDEFAULT,
		                  (rect.right - rect.left),
		                  (rect.bottom - rect.top),
		                  NULL,
		                  NULL,
		                  hInstance,
		                  NULL);

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}
	//�I������
	Uninit();

	//
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̉���
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//========================
// �E�C���h�E�v���V�[�W��
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (g_mode)
	{
	case MODE_END:
		DestroyWindow(hWnd);
		break;

	default:
		break;
	}

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]�L�[�������ꂽ�ꍇ
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
			else
			{
				return 0;
			}
		default:
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//==================
// �f�o�C�X�̎擾
//==================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============
// ����������
//=============
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		                            D3DDEVTYPE_HAL,
		                            hWnd,
		                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
		                            &d3dpp,
		                            &g_pD3DDevice)))
	{//Direct3D�f�o�C�X�̐���
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			                            D3DDEVTYPE_HAL,
			                            hWnd,
			                            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			                            &d3dpp,
			                            &g_pD3DDevice)))
		{//Direct3D�f�o�C�X�̐���
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				                            D3DDEVTYPE_REF,
				                            hWnd,
				                            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				                            &d3dpp,
				                            &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	
	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//------------------------------
	//�e��I�u�W�F�N�g�̏���������
	//------------------------------
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//�T�E���h�̏���������
	InitSound(hWnd);
	//
	InitRanking();
	//���[�h�̐ݒ�
	SetMode(g_mode);
	//�t�F�[�h
	InitFade(g_mode);

	return S_OK;
}
//==========
// �I������
//==========
void Uninit(void)
{
	//----------------------------
	//�e��I�u�W�F�N�g�̏I������
	//----------------------------
	//�T�E���h�̏I������
	UninitSound();

	UninitKeyboard();

	//
	UninitFade();

	//D3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//D3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}
//==========
// �X�V����
//==========
void Update(void)
{
	//----------------------------
	//�e��I�u�W�F�N�g�̍X�V����
	//----------------------------
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_RANK:
		UpdateRanking();
		break;
	}
	//
	UpdateFade();

#ifdef _DEBUG
	//���C���[
	if (GetKeyboardPress(DIK_F1) == true)
	{
		onWireFrame();
	}
	else if (GetKeyboardPress(DIK_F2) == true)
	{
		offWireFrame();
	}

#endif 
}
//==========
// �`�揈��
//==========
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		                (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		                D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f ,0);
	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n������
		//-----------------------------
		//�e��I�u�W�F�N�g�̕`�揈��
		//-----------------------------
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_RANK:
			DrawRanking();
			break;
		}

#ifdef _DEBUG
		DrawEffectEditer();
#endif // DEBUG

		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//==============
// ���[�h�̐ݒ�
//==============
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANK:
		UninitRanking();
		break;
	default:
		break;
	}

	//�V������ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_RANK:
		InitRanking();
		break;
	case MODE_END:

		break;
	default:
		break;
	}

	g_mode = mode;
}
//=============
// ���[�h�擾
//=============
MODE GetMode(void)
{
	return g_mode;
}
void DrawEffectEditer()
{
	PARTICLEEDITER* pEditer = GetParticleInfo();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	// ������ɑ��
	sprintf(&aStr[0], "*****************PARTICLEEDITER*****************\n�J���[�ύX:R,G,B\n���ˊp�ύX:X,Y,Z\n���q�̐��ύX:L\n�����ύX:H\n���ꂼ��SHIFT�����Ȃ�����ƌ���");

	// �e�L�X�g�\��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));

	rect = { 0,120,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ������ɑ��
	sprintf(&aStr[0], "R,G,B:%3.2f,%3.2f,%3.2f\nX,Y,Z:%3.2f,%3.2f,%3.2f\n�G�t�F�N�g�̍ő吔:%d\n�G�t�F�N�g�̎���:%d\n���q�̑傫��X,Y,Z:%3.2f,%3.2f,%3.2f", pEditer->ParticleInfo.col.r,
		pEditer->ParticleInfo.col.g, 
		pEditer->ParticleInfo.col.b,
		pEditer->ParticleInfo.dir.x,
		pEditer->ParticleInfo.dir.y, 
		pEditer->ParticleInfo.dir.z,
		pEditer->ParticleInfo.forlimit,
		pEditer->ParticleInfo.nLife,
		pEditer->ParticleInfo.Scale.x,
		pEditer->ParticleInfo.Scale.y, 
		pEditer->ParticleInfo.Scale.z);

	// �e�L�X�g�\��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));
}
//=============
// ���C���[
//=============
void onWireFrame()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}
void offWireFrame()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
//*******************************
// ���W�A���l����PI�ɕϊ����鏈��
//*******************************
D3DXVECTOR3* PitoRadian(D3DXVECTOR3* rot)
{
	// ���W�A���l����PI�ɕϊ�
	rot->x = rot->x * TOPI;
	rot->y = rot->y * TOPI;
	rot->z = rot->z * TOPI;

	// �p�x�̐��K��(X)
	if (rot->x >= D3DX_PI)
	{
		rot->x -= D3DX_PI * 2.0f;
	}
	else if (rot->x <= -D3DX_PI)
	{
		rot->x += D3DX_PI * 2.0f;
	}
	// �p�x�̐��K��(Y)
	if (rot->y >= D3DX_PI)
	{
		rot->y -= D3DX_PI * 2.0f;
	}
	else if (rot->y <= -D3DX_PI)
	{
		rot->y += D3DX_PI * 2.0f;
	}
	// �p�x�̐��K��(Z)
	if (rot->z >= D3DX_PI)
	{
		rot->z -= D3DX_PI * 2.0f;
	}
	else if (rot->z <= -D3DX_PI)
	{
		rot->z += D3DX_PI * 2.0f;
	}

	return rot;
}