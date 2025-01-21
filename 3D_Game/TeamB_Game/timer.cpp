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

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimerMinutes = NULL;

LPDIRECT3DTEXTURE9 g_pTextureColon = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffColon = NULL;

D3DXVECTOR3 g_posTimer;

int g_nTimer = 0;
int g_nSeconds = 0;
int g_nMinutes = 0;

//=============
//����������
//=============
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number001.png", &g_pTextureTimer); //�b
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\timerkyouki.png", &g_pTextureColon); //�R����


	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	g_posTimer = D3DXVECTOR3(500.0f, 0.0f, 0.0f);

	//���^�C�}�[
	g_nMinutes = 0;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimerMinutes,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimerMinutes->Lock(0, 0, (void**)&pVtx, 0);
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTimer.x - TIMER_SIZE, g_posTimer.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + TIMER_SIZE, g_posTimer.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTimer.x - TIMER_SIZE, g_posTimer.y + 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + TIMER_SIZE, g_posTimer.y + 100.0f, 0.0f);
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

		g_posTimer.x += TIMER_SIZE * 2;
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimerMinutes->Unlock();


	//�R����
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffColon,
		NULL);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffColon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posTimer.x - TIMER_SIZE, g_posTimer.y - 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + TIMER_SIZE, g_posTimer.y - 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTimer.x - TIMER_SIZE, g_posTimer.y + 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + TIMER_SIZE, g_posTimer.y + 100.0f, 0.0f);
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

	g_posTimer.x += TIMER_SIZE * 2;
	
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffColon->Unlock();


	//�b�^�C�}�[
	g_nTimer = 0;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffTimer,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTimer.x - TIMER_SIZE, g_posTimer.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + TIMER_SIZE, g_posTimer.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTimer.x - TIMER_SIZE, g_posTimer.y + 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + TIMER_SIZE, g_posTimer.y + 100.0f, 0.0f);
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

		g_posTimer.x += TIMER_SIZE * 2;
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
	if (g_nTimer >= 60)
	{
		AddTimerMinutes(1);
		AddTimer(-60);
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

	
	//��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimerMinutes, 0, sizeof(VERTEX_2D));
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}


	//�R����
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffColon, 0, sizeof(VERTEX_2D));
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureColon);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//�b
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
	
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
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
void SetTimer(int nTimer, int nMinutes)
{
	int aPosTexU[MAX_TIMER]; //������
	g_nTimer += nTimer;

	int nData = 100;
	int nData2 = 10;
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

	
	//��
	int aPosTexUM[MAX_TIMER]; //������
	g_nMinutes += nMinutes;

	int nDataM = 100;
	int nDataM2 = 10;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aPosTexUM[nCnt] = (g_nMinutes % nDataM) / nDataM2;
		nDataM /= 10;
		nDataM2 /= 10;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimerMinutes->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexUM[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexUM[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexUM[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexUM[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimerMinutes->Unlock();

}
//======================
//�b�^�C�}�[�̉��Z����
//======================
void AddTimer(int nValue)
{
	int aPosTexU[MAX_TIMER];
	g_nTimer += nValue;
	if (g_nTimer <= 0)
	{
		g_nTimer = 0;
	}
	int nData = 100;
	int nData2 = 10;
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
//======================
//���^�C�}�[�̉��Z����
//======================
void AddTimerMinutes(int nValue)
{
	int aPosTexU[MAX_TIMER];
	g_nMinutes += nValue;
	if (g_nMinutes <= 0)
	{
		g_nMinutes = 0;
	}
	int nData = 100;
	int nData2 = 10;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nMinutes % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimerMinutes->Lock(0, 0, (void**)&pVtx, 0);
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
	g_pVtxBuffTimerMinutes->Unlock();

}