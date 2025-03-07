//=============================
//
//�@�J��������[camera.cpp]
//�@Author:kaiti
//
//=============================

//�C���N���[�h
#include "camera.h"
#include "input.h"
#include "player.h"
#include "mouse.h"
#include "lockon.h"

//�O���[�o���ϐ�
Camera g_camera;

//=================
// �J�����̏�����
//=================
void InitCamera(void)
{
	//���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, 300.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf(((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x))
							 + ((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y))
							 + ((g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)));
}

//===================
// �J�����̏I������
//===================
void UninitCamera(void)
{

}

//====================
// �J�����̍X�V����
//====================
void UpdateCamera(void)
{
	//�e����擾
	Player* pPlayer = GetPlayer();				//�v���C���[
	Lockon* pLockon = GetLockOn();				//���b�N�I��
	MODE pMode = GetMode();						//�Q�[�����[�h

	// �p�x�̋ߓ�
	if (g_camera.rotDest.y >= D3DX_PI)
	{
		g_camera.rotDest.y -= D3DX_PI * 2.0f;
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rotDest.y <= -D3DX_PI)
	{
		g_camera.rotDest.y += D3DX_PI * 2.0f;
		g_camera.rot.y += D3DX_PI * 2.0f;
	}
	// �p�x�̋ߓ�
	if (g_camera.rotDest.x >= D3DX_PI)
	{
		g_camera.rotDest.x -= D3DX_PI * 2.0f;
	}
	else if ((g_camera.rotDest.x) <= -D3DX_PI)
	{
		g_camera.rotDest.x += D3DX_PI * 2.0f;
	}
	
	g_camera.rot += (g_camera.rotDest - g_camera.rot) * 0.3f;

	////�v���C���[�����b�N�I�����Ă���Ȃ�
	//if (pPlayer->bLockOn == true)
	//{
	//	g_camera.posRDest.x = pLockon->pos.x + sinf(pPlayer->rot.x) * (pLockon->pos.x - g_camera.posR.x);
	//	g_camera.posRDest.y = pLockon->pos.y;
	//	g_camera.posRDest.z = pLockon->pos.z + cosf(pPlayer->rot.z) * (pLockon->pos.z - g_camera.posR.z);

	//	g_camera.posVDest.x = pLockon->pos.x + sinf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//	g_camera.posVDest.z = pLockon->pos.z + cosf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//}
	//else
	//{
	//	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.x) * (pPlayer->pos.x - g_camera.posR.x);
	//	g_camera.posRDest.y = pPlayer->pos.y;
	//	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.z) * (pPlayer->pos.z - g_camera.posR.z);

	//	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//}

	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.08f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 1.0f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.08f;

	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.08f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.08f;


	//�^�C�g���ƃ��U���g�̎�
	if (pMode == MODE_TITLE || pMode == MODE_RESULT)
	{//�J�����̎�����]
		pPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�v���C���[�̈ʒu���O��
		//��]
		g_camera.rotDest.y += 0.01f;
	}
	//����ȊO
	else
	{
#ifdef _DEBUG

		//���_�̏㉺
		if (GetKeyboardPress(DIK_UP) == true)
		{//��
			if (g_camera.posV.y <= 500)
			{
				g_camera.posV.y += 5;
			}
		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//��
			if (g_camera.posV.y >= -500)
			{
				g_camera.posV.y -= 5;
			}
		}
#endif

		Player* pPlayer = GetPlayer();
		if (pPlayer->bLockOn == false)
		{
			UpdateCameratoMousePos();
			UpdateCameratoJoyPadPos();
		}
		else
		{
			SetCursorPos(640, 360);
		}


		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}
}

//=============================
//�}�E�X�ɂ��J�������쏈��
//=============================
void UpdateCameratoMousePos(void)
{
	static POINT SetMousePos = { (LONG)SCREEN_WIDTH / (LONG)2.0f,(LONG)SCREEN_HEIGHT / (LONG)2.0f };
	POINT MousePos;
	GetCursorPos(&MousePos);
	D3DXVECTOR2 DiffMouse = D3DXVECTOR2((FLOAT)MousePos.x - (FLOAT)SetMousePos.x,
		(FLOAT)MousePos.y - (FLOAT)SetMousePos.y);
	
	const FLOAT MouseSensitivity = 0.0008f;
	DiffMouse *= MouseSensitivity;
	g_camera.rotDest.x += DiffMouse.y;
	g_camera.rotDest.y += DiffMouse.x;

	SetCursorPos((int)SetMousePos.x, (int)SetMousePos.y);
}

//====================================
//�W���C�p�b�h�ɂ��J�������쏈��
//====================================
void UpdateCameratoJoyPadPos(void)
{
	XINPUT_STATE* pStick = GetJoyStickAngle();
	if (GetJoyStickR() == true)
	{
		float fStickAngleX = (float)pStick->Gamepad.sThumbRX * pStick->Gamepad.sThumbRX;
		float fStickAngleY = (float)pStick->Gamepad.sThumbRY * pStick->Gamepad.sThumbRY;

		float DeadZone = 10920.0f;
		float fMag = sqrtf(fStickAngleX + fStickAngleY);

		if (fMag > DeadZone)
		{
			if (pStick->Gamepad.sThumbRX < -DeadZone)
			{
				g_camera.rot.y += 0.03f;
			}
			else if (pStick->Gamepad.sThumbRX > DeadZone)
			{
				g_camera.rot.y -= 0.03f;
			}
		}
	}
}

//================
// �J�����̐ݒ�
//================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
					   &g_camera.posV,
					   &g_camera.posR,
					   &g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f), //����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, //�A�X�y�N�g��
		10.0f,
		5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//=================
//�J�����̏��擾����
//=================
Camera * GetCamera(void)
{
	return &g_camera;
}

void SetMouseWheel(int zDelta)
{
	g_camera.fDistance += zDelta * CAMERA_DISTANCESPEED;
}

//=============================
//�J�����̎��_�A�����_�̐ݒ�
//=============================
void ResetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	g_camera.posV = posV;				//���_
	g_camera.posR = posR;				//�����_
	g_camera.posVDest = posV;				//���_
	g_camera.posRDest = posR;				//�����_

	int i = 0;
}
