//==============================
//
//  �A�C�e��������[ItemUI.cpp]
//  Author:kaiti
//
//==============================
#include "item.h"
#include "itemui.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "circle.h"

//�O���[�o���ϐ�
//�g
LPDIRECT3DTEXTURE9 g_pTextureItemUIframe = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUIframe = NULL;

//�A�C�e����
LPDIRECT3DTEXTURE9 g_pTextureItemUI[MAX_ITEMUI] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;

//����
LPDIRECT3DTEXTURE9 g_pTextureItemUINo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUINo = NULL;

D3DXVECTOR3 g_ItemUIframepos;
D3DXVECTOR3 g_ItemUIpos;
D3DXVECTOR3 g_ItemUINopos;

int g_nCntItemHP;
int g_nCntItemMP;

//=============
// ����������
//=============
void InitItemUI(void)
{
	Player* pPlayer = GetPlayer();
	MODE mode = GetMode();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UIfram00.jpg", &g_pTextureItemUIframe);	//�g
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI2.png", &g_pTextureItemUI[0]);		//HP 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI1.png", &g_pTextureItemUI[1]);		//MP 

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number002.png", &g_pTextureItemUINo);	//No 

	g_ItemUIframepos = D3DXVECTOR3(985.0f, 550.0f, 0.0f);
	g_ItemUIpos = D3DXVECTOR3(1000.0f, 570.0f, 0.0f);
	g_ItemUINopos = D3DXVECTOR3(ITEMUI_X + 1000.0f, 570.0f, 0.0f);


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
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEMUI,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUI,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_ITEMUI; nCnt++)
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
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEMUI * MAX_ITEMGET,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUINo,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_ITEMUI * MAX_ITEMGET; nCnt++)
		{
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

			g_ItemUINopos.x += ITEMUINO_SIZE;

			if (nCnt == MAX_ITEMGET - 1 || nCnt == MAX_ITEMGET * 2 - 1 || nCnt == MAX_ITEMGET * 3 - 1)
			{
				g_ItemUINopos.y += ITEMUI_Y + 20.0f;
				g_ItemUINopos.x = ITEMUI_X + 1000.0f;
			}
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffItemUINo->Unlock();
	}



	if (pPlayer->bfirst == true || mode == MODE_STAGEONE)
	{
		g_nCntItemHP = 0;
		g_nCntItemMP = 0;
	}
	else
	{
		SetItemUI(ITEMTYPE_HP);
		SetItemUI(ITEMTYPE_MP);
	}
}
//==========
// �I������
//==========
void UninitItemUI(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureItemUIframe != NULL)
	{
		g_pTextureItemUIframe->Release();
		g_pTextureItemUIframe = NULL;
	}
	if (g_pTextureItemUINo != NULL)
	{
		g_pTextureItemUINo->Release();
		g_pTextureItemUINo = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_ITEMUI; nCnt++)
	{
		if (g_pTextureItemUI[nCnt] != NULL)
		{
			g_pTextureItemUI[nCnt]->Release();
			g_pTextureItemUI[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItemUIframe != NULL)
	{
		g_pVtxBuffItemUIframe->Release();
		g_pVtxBuffItemUIframe = NULL;
	}
	if (g_pVtxBuffItemUI != NULL)
	{
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
	}
	if (g_pVtxBuffItemUINo != NULL)
	{
		g_pVtxBuffItemUINo->Release();
		g_pVtxBuffItemUINo = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateItemUI(void)
{
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

	if (KeyboardTrigger(DIK_Q) || KeyboardTrigger(DIK_E) || GetJoypadTrigger(JOYKEY_UP) || GetJoypadTrigger(JOYKEY_DOWN))
	{
		switch (pPlayer->ItemType)
		{
		case ITEMTYPE_HP:
			pPlayer->ItemType = ITEMTYPE_MP;

			break;

		case ITEMTYPE_MP:
			pPlayer->ItemType = ITEMTYPE_HP;

			break;

		default:
			break;
		}
	}

	if (pPlayer->ItemType == ITEMTYPE_HP)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//���_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	}
	else if (pPlayer->ItemType == ITEMTYPE_MP)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		//���_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItemUI->Unlock();
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
		for (int nCnt = 0; nCnt < MAX_ITEMUI; nCnt++)
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
		for (int nCnt = 0; nCnt < MAX_ITEMUI * MAX_ITEMGET; nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItemUINo);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

}
//=================
// �A�C�e��UI�ݒ�
//=================
void SetItemUI(ITEMTYPE type)
{
	int aPosTexU[MAX_ITEMGET];
	int nItemType = 0;
	if (type == ITEMTYPE_HP)
	{
		nItemType = g_nCntItemHP;
	}
	else if (type == ITEMTYPE_MP)
	{
		nItemType = g_nCntItemMP;

	}

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * type * 2;

	for (nCnt = 0; nCnt < MAX_ITEMGET; nCnt++)
	{
		aPosTexU[nCnt] = (nItemType % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItemUINo->Unlock();
}
//==================
// �A�C�e�������Z
//==================
void AddItemUI(ITEMTYPE type)
{
	int aPosTexU[MAX_ITEMGET];
	int nItemType = 0;
	if (type == ITEMTYPE_HP)
	{
		g_nCntItemHP++;
		nItemType = g_nCntItemHP;
	}
	else if (type == ITEMTYPE_MP)
	{
		g_nCntItemMP++;
		nItemType = g_nCntItemMP;
	}

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * type * 2;

	for (nCnt = 0; nCnt < MAX_ITEMGET; nCnt++)
	{
		aPosTexU[nCnt] = (nItemType % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);
		
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItemUINo->Unlock();
}
//===================
// �A�C�e�������Z
//===================
void UseItem(ITEMTYPE type)
{
	Player* pPlayer = GetPlayer();

	int aPosTexU[MAX_ITEMGET];
	int nItemType = 0;
	int circleIndx = 0;
	if (type == ITEMTYPE_HP)
	{
		if (g_nCntItemHP >= 1)
		{
			SetVibRation(1000, 1000, 60);
			PlaySound(SOUND_LABEL_POTION);

			pPlayer->Status.fHP += ITEMABILITY_HP;
			if (pPlayer->Status.fHP >= PLAYER_HP)
			{
				pPlayer->Status.fHP = PLAYER_HP;
			}

			//�T�[�N���̐ݒ�
			circleIndx = SetCircle(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 1.0f, pPlayer->pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				20,
				0,
				10.0f,
				36.0f,
				false,
				true,
				0);

			//�T�[�N���̃A�j���[�V�����̐ݒ�
			SetAnime(circleIndx,
				ANIMETYPE_0,
				60);
		}

		g_nCntItemHP--;
		if (g_nCntItemHP <= 0)
		{
			g_nCntItemHP = 0;
		}
		nItemType = g_nCntItemHP;
	}
	else if (type == ITEMTYPE_MP)
	{
		if (g_nCntItemMP >= 1)
		{
			SetVibRation(1000, 1000, 60);
			PlaySound(SOUND_LABEL_POTION);

			pPlayer->Status.nMP = PLAYER_MP;

			//�T�[�N���̐ݒ�
			circleIndx = SetCircle(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 1.0f, pPlayer->pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
				20,
				0,
				10.0f,
				36.0f,
				false,
				true,
				0);

			//�T�[�N���̃A�j���[�V�����̐ݒ�
			SetAnime(circleIndx,
				ANIMETYPE_0,
				60);
		}
		g_nCntItemMP--;
		if (g_nCntItemMP <= 0)
		{
			g_nCntItemMP = 0;
		}
		nItemType = g_nCntItemMP;
	}

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * type * 2;

	for (nCnt = 0; nCnt < MAX_ITEMGET; nCnt++)
	{
		aPosTexU[nCnt] = (nItemType % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItemUINo->Unlock();
}