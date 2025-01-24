//==============================
//
//  �~�j�}�b�v����[minimap.cpp]
//  Author:kaiti
//
//==============================
#include "minimap.h"
#include "player.h"
//�O���[�o���ϐ�
//�g
LPDIRECT3DTEXTURE9 g_pTextureMiniMap = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMiniMap = NULL;
//�v���C���[�A�C�R��
LPDIRECT3DTEXTURE9 g_pTextureMapPlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapPlayer = NULL;

D3DXVECTOR3 g_MiniMappos;
D3DXVECTOR3 g_MapPlayerpos;
//=============
// ����������
//=============
void InitMiniMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\map.png", &g_pTextureMiniMap);	//�g
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ownmachine.jpg", &g_pTextureMapPlayer);		//HP 


	g_MiniMappos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
	g_MapPlayerpos = D3DXVECTOR3(1063.0f, 140.0f, 0.0f);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	//�g
	{		
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMiniMap,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMiniMap->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_MiniMappos.x, g_MiniMappos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MiniMappos.x + MINIMAP_X, g_MiniMappos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MiniMappos.x, g_MiniMappos.y + MINIMAP_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MiniMappos.x + MINIMAP_X, g_MiniMappos.y + MINIMAP_Y, 0.0f);
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
		g_pVtxBuffMiniMap->Unlock();
	}

	//�v���C���[�A�C�R��
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMapPlayer,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
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
		g_pVtxBuffMapPlayer->Unlock();
	}

}
//==========
// �I������
//==========
void UninitMiniMap(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMiniMap != NULL && g_pTextureMapPlayer != NULL)
	{
		g_pTextureMiniMap->Release();
		g_pTextureMiniMap = NULL;
		g_pTextureMapPlayer->Release();
		g_pTextureMapPlayer = NULL;

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMiniMap != NULL && g_pVtxBuffMapPlayer != NULL)
	{
		g_pVtxBuffMiniMap->Release();
		g_pVtxBuffMiniMap = NULL;
		g_pVtxBuffMapPlayer->Release();
		g_pVtxBuffMapPlayer = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateMiniMap(void)
{

}
//===========
// �`�揈��
//===========
void DrawMiniMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�g
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMiniMap, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMiniMap);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//�A�C�e����
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMapPlayer, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMapPlayer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//==========================
// �v���C���[�A�C�R���ݒ�
//==========================
void SetMapPlayer(int nStageNo)
{
	//�X�e�[�W���Ƃ̏ꏊ�ύX�i���j
	if (nStageNo == 1)
	{
		g_MapPlayerpos = D3DXVECTOR3(1063.0f, 140.0f, 0.0f);
	}
	else if (nStageNo == 2)
	{
		g_MapPlayerpos = D3DXVECTOR3(1153.0f, 140.0f, 0.0f);
	}
	else if (nStageNo == 3)
	{
		g_MapPlayerpos = D3DXVECTOR3(1153.0f, 55.0f, 0.0f);
	}
	else if (nStageNo == 4)
	{
		g_MapPlayerpos = D3DXVECTOR3(1063.0f, 55.0f, 0.0f);
	}

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMapPlayer->Unlock();
}