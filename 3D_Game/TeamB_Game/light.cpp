//==================================
//
//�@�E�C���h�E�\������[light.cpp]
//�@Author:kaiti
//
//==================================
#include "light.h"
//�O���[�o���ϐ�
D3DLIGHT9 g_light[MAX_LIGHT]; //���C�g���
bool bUse[MAX_LIGHT];
//==================
// ���C�g�̏�����
//==================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g���N���A����
		ZeroMemory(&g_light, sizeof(g_light));


		//���C�g�̊g�U����ݒ�
		g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���C�g�̐F

		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		vecDir[1] = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
		vecDir[2] = D3DXVECTOR3(0.9f, -0.1f, 0.4f);

		//���K������i�傫���P�̃x�N�g���ɂ���j
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		g_light[nCnt].Direction = vecDir[nCnt];

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, &g_light[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);

		bUse[nCnt] = false;
	}	
}
//====================
// ���C�g�̏I������
//====================
void UninitLight(void)
{

}
//====================
// ���C�g�̍X�V����
//====================
void UpdateLight(void)
{

}
//
//
//
void SetLight(D3DXVECTOR3 Dir, D3DXCOLOR Diffuse)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		if (bUse[nCnt] == false)
		{
			D3DXVECTOR3 vecDir;

			//���C�g�̎�ނ�ݒ�
			g_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//���s����

			//���C�g�̊g�U����ݒ�
			g_light[nCnt].Diffuse = Diffuse;//���C�g�̐F

			//���C�g�̕�����ݒ�
			vecDir = Dir;

			//���K������i�傫���P�̃x�N�g���ɂ���j
			D3DXVec3Normalize(&vecDir, &vecDir);
			g_light[nCnt].Direction = vecDir;

			//���C�g��ݒ�
			pDevice->SetLight(nCnt, &g_light[nCnt]);

			//���C�g��L���ɂ���
			pDevice->LightEnable(nCnt, TRUE);

			bUse[nCnt] = true;
			break;
		}
	}
}
//*****************
// ���C�g�̎擾����
//*****************
D3DLIGHT9* GetLight()
{
	return &g_light[0];
}