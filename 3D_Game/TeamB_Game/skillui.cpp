//==============================
//
//  �A�C�e��������[SkillUI.cpp]
//  Author:kaiti
//
//==============================
#include "skillui.h"
#include "player.h"
#include "buttonUI.h"

//�O���[�o���ϐ�
//�g
LPDIRECT3DTEXTURE9 g_pTextureSkillUIframe = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkillUIframe = NULL;

//���@�̎��
LPDIRECT3DTEXTURE9 g_pTextureSkillUI[SKILLTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkillUI = NULL;

D3DXVECTOR3 g_SkillUIframepos;
D3DXVECTOR3 g_SkillUIpos;

//=============
// ����������
//=============
void InitSkillUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\skill00.png", &g_pTextureSkillUI[0]);		// �ʏ햂�@ 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\skill01.png", &g_pTextureSkillUI[1]);		// �ǔ����@
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\skill02.png", &g_pTextureSkillUI[2]);		// �������@

	g_SkillUIframepos = D3DXVECTOR3(80.0f, 150.0f, 0.0f);
	g_SkillUIpos = g_SkillUIframepos;

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	//�g
	{		
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SKILLTYPE_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSkillUIframe,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffSkillUIframe->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_SkillUIframepos.x - SKILLUIFRAM_SIZE, g_SkillUIframepos.y - SKILLUIFRAM_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_SkillUIframepos.x + SKILLUIFRAM_SIZE, g_SkillUIframepos.y - SKILLUIFRAM_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SkillUIframepos.x - SKILLUIFRAM_SIZE, g_SkillUIframepos.y + SKILLUIFRAM_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SkillUIframepos.x + SKILLUIFRAM_SIZE, g_SkillUIframepos.y + SKILLUIFRAM_SIZE, 0.0f);
			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			
			pVtx += 4;
			g_SkillUIframepos.x += SKILLUI_SPACE;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffSkillUIframe->Unlock();
	}

	//�A�C�e��
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SKILLTYPE_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSkillUI,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffSkillUI->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//�A�C�e����
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_SkillUIpos.x - SKILLUI_SIZE, g_SkillUIpos.y - SKILLUI_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_SkillUIpos.x + SKILLUI_SIZE, g_SkillUIpos.y - SKILLUI_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SkillUIpos.x - SKILLUI_SIZE, g_SkillUIpos.y + SKILLUI_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SkillUIpos.x + SKILLUI_SIZE, g_SkillUIpos.y + SKILLUI_SIZE, 0.0f);
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
			g_SkillUIpos.x += SKILLUI_SPACE;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffSkillUI->Unlock();
	}
	
	//SetButtonUi(BUTTONUI_WHEEL, g_SkillUIpos, D3DXVECTOR3(20.0f, 20.0f, 0.0f));
}
//==========
// �I������
//==========
void UninitSkillUI(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
	{
		if (g_pTextureSkillUI[nCnt] != NULL)
		{
			g_pTextureSkillUI[nCnt]->Release();
			g_pTextureSkillUI[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSkillUIframe != NULL)
	{
		g_pVtxBuffSkillUIframe->Release();
		g_pVtxBuffSkillUIframe = NULL;
	}
	if (g_pVtxBuffSkillUI != NULL)
	{
		g_pVtxBuffSkillUI->Release();
		g_pVtxBuffSkillUI = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateSkillUI(void)
{
	//�v���C���[�̏��擾
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSkillUIframe->Lock(0, 0, (void**)&pVtx, 0);

	switch (pPlayer->Skilltype)
	{
	case SKILLTYPE_NONE:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[4].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[5].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[6].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[7].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[8].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[9].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[10].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[11].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		break;
	case SKILLTYPE_HORMING:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[8].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[9].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[10].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[11].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		break;
	case SKILLTYPE_EXPLOSION:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[4].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[5].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[6].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[7].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		break;
	default:
		break;
	}


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSkillUIframe->Unlock();
}
//===========
// �`�揈��
//===========
void DrawSkillUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�g
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffSkillUIframe, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSkillUIframe);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//�A�C�e����
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffSkillUI, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSkillUI[nCnt]);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}