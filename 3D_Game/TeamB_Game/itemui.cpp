//==============================
//
//  �A�C�e��������[ItemUI.cpp]
//  Author:kaiti
//
//==============================
#include "itemui.h"
#include "player.h"

#define MAX_ITEM (3)

//�O���[�o���ϐ�
//�g
LPDIRECT3DTEXTURE9 g_pTextureItemUIframe = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUIframe = NULL;

//�A�C�e�� �~
LPDIRECT3DTEXTURE9 g_pTextureItemUI[MAX_ITEM] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;

//����
LPDIRECT3DTEXTURE9 g_pTextureItemUINo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUINo = NULL;

D3DXVECTOR3 g_ItemUIframepos;
D3DXVECTOR3 g_ItemUIpos;
D3DXVECTOR3 g_ItemUINopos;
//=============
// ����������
//=============
void InitItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UIfram.jpg", &g_pTextureItemUIframe);	//�g
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI2.png", &g_pTextureItemUI[0]);		//HP 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI1.png", &g_pTextureItemUI[1]);		//MP 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI3.png", &g_pTextureItemUI[2]);		//AT 

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number002.png", &g_pTextureItemUINo);		//No 

	g_ItemUIframepos = D3DXVECTOR3(1025.0f, 470.0f, 0.0f);
	g_ItemUIpos = D3DXVECTOR3(1040.0f, 490.0f, 0.0f);
	g_ItemUINopos = D3DXVECTOR3(ITEMUI_X + 1040.0f, 490.0f, 0.0f);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	//�g
	{		
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUIframe,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffItemUIframe->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_ItemUIframepos.x, g_ItemUIframepos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ItemUIframepos.x + ITEMUIFRAME_X, g_ItemUIframepos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ItemUIframepos.x, g_ItemUIframepos.y + ITEMUIFRAME_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ItemUIframepos.x + ITEMUIFRAME_X, g_ItemUIframepos.y + ITEMUIFRAME_Y, 0.0f);
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
		g_pVtxBuffItemUIframe->Unlock();
	}

	//�A�C�e��
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUI,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
		{
			//�A�C�e����
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ItemUIpos.x, g_ItemUIpos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUIpos.x + ITEMUI_X, g_ItemUIpos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUIpos.x, g_ItemUIpos.y + ITEMUI_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUIpos.x + ITEMUI_X, g_ItemUIpos.y + ITEMUI_Y, 0.0f);
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

			pVtx += 4;
			g_ItemUIpos.y += ITEMUI_Y + 20.0f;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffItemUI->Unlock();
	}

	//����
	{

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUINo,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
		{
			//�A�C�e����
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ItemUINopos.x, g_ItemUINopos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUINopos.x + ITEMUINO_SIZE, g_ItemUINopos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUINopos.x, g_ItemUINopos.y + ITEMUINO_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUINopos.x + ITEMUINO_SIZE, g_ItemUINopos.y + ITEMUINO_SIZE, 0.0f);
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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
			g_ItemUINopos.y += ITEMUI_Y + 20.0f;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffItemUINo->Unlock();
	}
}
//==========
// �I������
//==========
void UninitItemUI(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureItemUIframe != NULL && g_pTextureItemUINo != NULL)
	{
		g_pTextureItemUIframe->Release();
		g_pTextureItemUIframe = NULL;
		g_pTextureItemUINo->Release();
		g_pTextureItemUINo = NULL;

	}
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_pTextureItemUI[nCnt] != NULL)
		{
			g_pTextureItemUI[nCnt]->Release();
			g_pTextureItemUI[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItemUIframe != NULL && g_pVtxBuffItemUI != NULL && g_pVtxBuffItemUINo != NULL)
	{
		g_pVtxBuffItemUIframe->Release();
		g_pVtxBuffItemUIframe = NULL;
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
		g_pVtxBuffItemUINo->Release();
		g_pVtxBuffItemUINo = NULL;

	}
}
//==========
// �X�V����
//==========
void UpdateItemUI(void)
{

}
//===========
// �`�揈��
//===========
void DrawItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�g
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffItemUIframe, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureItemUIframe);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//�A�C�e����
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItemUI[nCnt]);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//����
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffItemUINo, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItemUINo);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

}