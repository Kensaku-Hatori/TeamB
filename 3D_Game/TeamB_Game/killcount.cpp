//==============================
//
//  �X�R�A����[KillCount.cpp]
//  Author:kaiti
//
//==============================
#include "killcount.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureKillCount = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKillCount = NULL;
LPDIRECT3DTEXTURE9 g_pTextureStrike = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStrike = NULL;

D3DXVECTOR3 g_posKillCount;
int g_nKillCount;
//=============
// ����������
//=============
void InitKillCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureKillCount); //1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\strike00.png", &g_pTextureStrike); //1

	g_posKillCount = D3DXVECTOR3(50.0f,0.0f,0.0f);
	g_nKillCount = 0;

	//���l
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_KILLCOUNTER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKillCount,
		NULL);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKillCount->Lock(0, 0, (void**)&pVtx, 0);
	
	int nCnt,nData=0;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posKillCount.x + (50 * nData), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posKillCount.x + (50 * (nData + 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posKillCount.x + (50 * nData), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posKillCount.x + (50 * (nData + 1)), 100.0f, 0.0f);
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

		nData++;
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffKillCount->Unlock();

	//�X�g���C�N
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStrike,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStrike->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 300.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500.0f, 300.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffStrike->Unlock();
}
//===========
// �I������
//===========
void UninitKillCount(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureKillCount != NULL && g_pTextureStrike != NULL)
	{
		g_pTextureKillCount->Release();
		g_pTextureKillCount = NULL;
		g_pTextureStrike->Release();
		g_pTextureStrike = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffKillCount != NULL && g_pVtxBuffStrike != NULL)
	{
		g_pVtxBuffKillCount->Release();
		g_pVtxBuffKillCount = NULL;
		g_pVtxBuffStrike->Release();
		g_pVtxBuffStrike = NULL;
	}
}
//===========
// �X�V����
//===========
void UpdateKillCount(void)
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStrike->Lock(0, 0, (void**)&pVtx, 0);

	Player* pPlayer = GetPlayer();
	if (pPlayer->nCntPin >= PIN_CONDITION)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	}

	//if (g_nKillCount == PIN_CONDITION)
	//{
	//	SetKillCount(0);
	//}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffStrike->Unlock();
}
//===========
// �`�揈��
//===========
void DrawKillCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKillCount, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureKillCount);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStrike, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStrike);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//================
// �X�R�A�̐ݒ�
//================
void SetKillCount(int nKillCount)
{
	int aPosTexU[MAX_KILLCOUNTER]; //������	
	g_nKillCount = nKillCount;
	if (g_nKillCount <= 0)
	{
		g_nKillCount = 0;
	}

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		aPosTexU[nCnt] = g_nKillCount % nData / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKillCount->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt <  MAX_KILLCOUNTER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffKillCount->Unlock();
}
//===================
// �X�R�A�̉��Z����
//===================
void AddKillCount(int nValue)
{
	int aPosTexU[MAX_KILLCOUNTER];
	g_nKillCount += nValue;
	if (g_nKillCount <= 0)
	{
		g_nKillCount = 0;
	}

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		aPosTexU[nCnt] = g_nKillCount % nData / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKillCount->Lock(0, 0, (void**)&pVtx, 0);
	int nData3 = 0;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f) + 0.1f, 1.0f);

		nData3++;
		pVtx += 4;;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffKillCount->Unlock();
}
//==============
// �X�R�A�̎擾
//==============
int GetKillCount(void)
{
	return g_nKillCount;
}