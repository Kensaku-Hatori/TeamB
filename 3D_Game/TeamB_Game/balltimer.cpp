//==============================
//
//  �^�C�}�[����[BallTimer.cpp]
//  Author:kaiti
//
//==============================
#include "balltimer.h"
#include "player.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBallTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallTimer = NULL;
D3DXVECTOR3 g_posBallTimer;
int g_nBallTimer = 0;
bool g_bPuls;
//=============
// ����������
//=============
void InitBallTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureBallTimer); //1

	g_posBallTimer = D3DXVECTOR3(30.0f, BALLTIMER_Y,0.0f);
	g_nBallTimer = 0;
	g_bPuls = false;

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BALLTIMER,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBallTimer,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallTimer->Lock(0, 0, (void**)&pVtx, 0);
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * nCnt), g_posBallTimer.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * (nCnt + 1)), g_posBallTimer.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * nCnt), g_posBallTimer.y + 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * (nCnt + 1)), g_posBallTimer.y + 100.0f, 0.0f);
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
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallTimer->Unlock();
}
//==========
// �I������
//==========
void UninitBallTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBallTimer != NULL)
	{
		g_pTextureBallTimer->Release();
		g_pTextureBallTimer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBallTimer != NULL)
	{
		g_pVtxBuffBallTimer->Release();
		g_pVtxBuffBallTimer = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateBallTimer(void)
{
	Player* pPlayer = GetPlayer();

	if (pPlayer->type == PLAYERTYPE_BALL || pPlayer->type == PLAYERTYPE_SUPERBALL)
	{
		if (g_nBallTimer > 0)
		{//�^�C�}�[���O���傫���ꍇ
			AddBallTimer(-1);
		}
	}
	if (pPlayer->type == PLAYERTYPE_HITO)
	{//�v���C���[���l�̎�
		if (g_nBallTimer < MAX_BALLTIME && g_bPuls == true)
		{//�^�C�}�[���ő��菬�����ꍇ
			AddBallTimer(1);
		}
		else if (g_nBallTimer >= MAX_BALLTIME)
		{//�^�C�}�[���ő�l�܂ł�������
			g_nBallTimer = MAX_BALLTIME;
			g_bPuls = false;
			if (pPlayer->bBall == false)
			{
				pPlayer->bBall = true;
			}
		}
	}
	if (g_nBallTimer <= 0 && g_bPuls == false)
	{
		g_bPuls = true;
	}
	pPlayer->nBallTime = g_nBallTimer;
}
//===========
// �`�揈��
//===========
void DrawBallTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBallTimer, 0, sizeof(VERTEX_2D));
	
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIME; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBallTimer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//=================
// �^�C�}�[�̐ݒ�
//=================
void SetBallTimer(int nBallTimer)
{
	int aPosTexU[MAX_BALLTIMER]; //������
	g_nBallTimer += nBallTimer;

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nBallTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallTimer->Unlock();
}
//==================
// �^�C�}�[�̉��Z����
//==================
void AddBallTimer(int nValue)
{
	int aPosTexU[MAX_BALLTIMER];
	g_nBallTimer += nValue;
	if (g_nBallTimer <= 0)
	{
		g_nBallTimer = 0;
	}
	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nBallTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
 	g_pVtxBuffBallTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallTimer->Unlock();
}
//==============
// �^�C�}�[�̎擾
//==============
int GetBallTimer(void)
{
	return g_nBallTimer;
}