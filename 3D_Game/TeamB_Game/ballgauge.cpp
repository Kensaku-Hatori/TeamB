//==============================
//
//  �^�C�}�[����[BallGauge.cpp]
//  Author:kaiti
//
//==============================
#include "ballgauge.h"
#include "player.h"
#include "balltimer.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBallGauge[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallGauge = NULL;
D3DXVECTOR3 g_posBallGauge;

int g_nBallTime;
//=============
// ����������
//=============
void InitBallGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nBallTime = GetBallTimer() / 2;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.png", &g_pTextureBallGauge[0]); //1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.jpeg", &g_pTextureBallGauge[1]); //0
	
	g_posBallGauge = D3DXVECTOR3(20.0f, BALLTIMER_Y,0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBallGauge,
		                        NULL);
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (nCnt == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y - 75.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y - 75.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
		}
		else
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (nCnt == 0)
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
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallGauge->Unlock();
}
//==========
// �I������
//==========
void UninitBallGauge(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBallGauge[nCnt] != NULL)
		{
			g_pTextureBallGauge[nCnt]->Release();
			g_pTextureBallGauge[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBallGauge != NULL)
	{
		g_pVtxBuffBallGauge->Release();
		g_pVtxBuffBallGauge = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateBallGauge(void)
{
	Player* pPlayer = GetPlayer();

	g_nBallTime = GetBallTimer() / 2;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBallGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posBallGauge.x, g_posBallGauge.y + 8.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime, g_posBallGauge.y + 8.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBallGauge.x, g_posBallGauge.y + GAUGE_Y - 15.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime, g_posBallGauge.y + GAUGE_Y - 15.0f, 0.0f);

	//�X�[�p�[�{�[���̎��̐F
	if (pPlayer->type == PLAYERTYPE_SUPERBALL)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(200, 0, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(200, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(200, 0, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(200, 0, 255, 255);
	}
	//���̑�
	else if (pPlayer->bBall == false)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	else
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 200, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 200, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 200, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 200, 0, 255);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBallGauge->Unlock();
}
//===========
// �`�揈��
//===========
void DrawBallGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBallGauge, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBallGauge[nCnt]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}