//=============================
//
//�@�J��������[camera.cpp]
//�@Author:kaiti
//
//=============================
#include "camera.h"
#include "input.h"
#include "player.h"
//�O���[�o���ϐ�
Camera g_camera;

//=================
// �J�����̏�����
//=================
void InitCamera(void)
{
	//���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -250.0f);
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
	Player* pPlayer;
	pPlayer = GetPlayer();

	MODE pMode;
	pMode = GetMode();
	
	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.x) * (pPlayer->pos.x - g_camera.posR.x);
	g_camera.posRDest.y = pPlayer->pos.y;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.z) * (pPlayer->pos.z - g_camera.posR.z);

	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.fDistance;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.fDistance;


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
		g_camera.rot.y += 0.01f;

		g_camera.posV.y = 200.0f;
		g_camera.posR.y = 100.0f;
	}
	//����ȊO
	else
	{

		////���_�̐���
		//if (GetKeyboardPress(DIK_Z) == true)
		//{
		//	g_camera.rot.y += 0.05f;
		//	//�p�x�̐��K��
		//	if (g_camera.rot.y > D3DX_PI)
		//	{
		//		g_camera.rot.y = -D3DX_PI;
		//	}
		//	if (g_camera.rot.y < -D3DX_PI)
		//	{
		//		g_camera.rot.y = D3DX_PI;
		//	}

		//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		//}
		if (GetKeyboardPress(DIK_C) == true)
		{
			g_camera.rot.y -= 0.05f;
			//�p�x�̐��K��
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y = -D3DX_PI;
			}
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y = D3DX_PI;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		////���_�̏㉺
		//if (GetKeyboardPress(DIK_Y) == true)
		//{//��
		//	if (g_camera.posV.y <= 500)
		//	{
		//		g_camera.posV.y += 5;
		//	}
		//}
		if (GetKeyboardPress(DIK_N) == true)
		{//��
			if (g_camera.posV.y >= -500)
			{
				g_camera.posV.y -= 5;
			}
		}

		//�����_�̏㉺
		//if (GetKeyboardPress(DIK_R) == true)
		//{//��
		//	g_camera.rot.x += 0.05f;
		//	//�p�x�̐��K��
		//	if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x = -D3DX_PI;
		//	}
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x = D3DX_PI;
		//	}

		//	g_camera.posV.y -= sinf(g_camera.rot.x - D3DX_PI) * 1;

		//	g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot.x) * g_camera.fDistance;
		//}
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
//
//=================
Camera * GetCamera(void)
{
	return &g_camera;
}