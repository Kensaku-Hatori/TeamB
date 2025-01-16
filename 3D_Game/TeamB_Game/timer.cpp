//==============================
//
//  �^�C�}�[����[Timer.cpp]
//  Author:kaiti
//
//==============================
#include "timer.h"
#include "player.h"
#include "result.h"
#include "fade.h"
#include "game.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;
D3DXVECTOR3 g_posTimer;
int g_nTimer = 0;
int g_nSeconds = 0;
//=============
//����������
//=============
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureTimer); //1

	g_posTimer = D3DXVECTOR3(550.0f,0.0f,0.0f);
	g_nTimer = 0;

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffTimer,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTimer.x + (50 * nCnt), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + (50 * (nCnt + 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTimer.x + (50 * nCnt), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + (50 * (nCnt + 1)), 100.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}
//==========
//�I������
//==========
void UninitTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdateTimer(void)
{
	GAMESTATE gamestate = GetGameSatate();

	g_nSeconds++;
	//��b�o��
	if (g_nSeconds >= 60)
	{
		AddTimer(1);
		g_nSeconds = 0;
	}
	
	//�^�C�}�[���O�ɂȂ���
	if (g_nTimer <= 0)
	{	
		if (gamestate == GAMESTATE_NORMAL)
		{
			SetGameState(GAMESTATE_TIMEOVER);
		}		
		
		g_nTimer = 0;
	}

}
//===========
//�`�揈��
//===========
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
	
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//=================
//�^�C�}�[�̐ݒ�
//=================
void SetTimer(int nTimer)
{
	int aPosTexU[MAX_TIMER]; //������
	g_nTimer += nTimer;

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}
//==================
//�^�C�}�[�̉��Z����
//==================
void AddTimer(int nValue)
{
	int aPosTexU[MAX_TIMER];
	g_nTimer -= nValue;
	if (g_nTimer <= 0)
	{
		g_nTimer = 0;
	}
	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
 	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}
//==============
//�^�C�}�[�̎擾
//==============
int GetTimer(void)
{
	return g_nTimer;
}