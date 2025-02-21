//==============================
//
//  �~�j�}�b�v����[Mission.cpp]
//  Author:kaiti
//
//==============================
#include "mission.h"
#include "player.h"
//�O���[�o���ϐ�
//�~�b�V����
LPDIRECT3DTEXTURE9 g_pTextureMission[MISSION_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMission = NULL;

Mission g_Mission;

D3DXVECTOR3 g_Missionpos;
//=============
// ����������
//=============
void InitMission(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mission00.jpg", &g_pTextureMission[0]);	//�g
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mission01.jpg", &g_pTextureMission[1]);	//�g
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mission02.jpg", &g_pTextureMission[2]);	//�g

	g_Mission.mission = MISSION_ZENMETU;

	g_Missionpos = D3DXVECTOR3(1130.0f, 380.0f, 0.0f);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	//�g
	{		
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMission,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMission->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffMission->Unlock();
	}
}
//==========
// �I������
//==========
void UninitMission(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MISSION_MAX; nCnt++)
	{
		if (g_pTextureMission[nCnt] != NULL)
		{
			g_pTextureMission[nCnt]->Release();
			g_pTextureMission[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMission != NULL)
	{
		g_pVtxBuffMission->Release();
		g_pVtxBuffMission = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateMission(void)
{
}
//===========
// �`�揈��
//===========
void DrawMission(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�g
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMission, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMission[g_Mission.mission]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//
//
//
Mission* GetMission()
{
	return &g_Mission;
}