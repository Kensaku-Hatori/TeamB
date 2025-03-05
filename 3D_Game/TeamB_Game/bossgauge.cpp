//==============================
//
//  �Q�[�W����[BossGauge.cpp]
//  Author:kaiti
//
//==============================
#include "BossGauge.h"
#include "player.h"
#include "boss.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBossGaugeBack = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossGaugeBack = NULL;

LPDIRECT3DTEXTURE9 g_pTextureBossGauge = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossGauge = NULL;

LPDIRECT3DTEXTURE9 g_pTextureBossName = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossName = NULL;

D3DXVECTOR3 g_BossGauge;
D3DXVECTOR3 g_BossGaugeSize;
D3DXVECTOR3 g_BossName;

//=============
// ����������
//=============
void InitBossGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossgage.png", &g_pTextureBossGaugeBack);	//HP �g	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GUAGE.png", &g_pTextureBossGauge);	//
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossname.png", &g_pTextureBossName);	//

	g_BossGauge = D3DXVECTOR3(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 100.0f, 0.0f);
	g_BossGaugeSize = D3DXVECTOR3(BOSSGAUGE_FRAME_X, BOSSGAUGE_FRAME_Y, 0.0f);
	g_BossName = D3DXVECTOR3(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 150.0f, 0.0f);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	//�Q�[�W
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBossGauge,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBossGauge->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffBossGauge->Unlock();
	}

	//�g
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBossGaugeBack,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBossGaugeBack->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_BossGauge.x + 10.0f, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x - 15.0f, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossGauge.x + 10.0f, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x - 15.0f, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
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
		g_pVtxBuffBossGaugeBack->Unlock();
	}

	//���O
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBossName,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossName->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_BossName.x - BOSSNAME_X, g_BossName.y - BOSSNAME_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_BossName.x + BOSSNAME_X, g_BossName.y - BOSSNAME_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_BossName.x - BOSSNAME_X, g_BossName.y + BOSSNAME_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_BossName.x + BOSSNAME_X, g_BossName.y + BOSSNAME_Y, 0.0f);
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
	g_pVtxBuffBossName->Unlock();

}
//==========
// �I������
//==========
void UninitBossGauge(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBossGauge != NULL && g_pTextureBossGaugeBack != NULL && g_pTextureBossName != NULL)
	{
		g_pTextureBossGauge->Release();
		g_pTextureBossGauge = NULL;
		g_pTextureBossGaugeBack->Release();
		g_pTextureBossGaugeBack = NULL;
		g_pTextureBossName->Release();
		g_pTextureBossName = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBossGauge != NULL && g_pVtxBuffBossGaugeBack != NULL && g_pVtxBuffBossName != NULL)
	{
		g_pVtxBuffBossGauge->Release();
		g_pVtxBuffBossGauge = NULL;
		g_pVtxBuffBossGaugeBack->Release();
		g_pVtxBuffBossGaugeBack = NULL;
		g_pVtxBuffBossName->Release();
		g_pVtxBuffBossName = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateBossGauge(void)
{
	BOSS* pBoss = GetBoss();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossGauge->Lock(0, 0, (void**)&pVtx, 0);
	g_BossGaugeSize.x = pBoss->Status.fHP / BOSSGAUGE_DIVISION;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);

	if (pBoss->Status.fHP <= BOSS_HP / 5)
	{//��
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 1, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 1, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 1, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 1, 1, 255);
	}
	else if (pBoss->Status.fHP <= BOSS_HP / 1.5)
	{//���F
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 1, 255);
	}
	else
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(1, 255, 127, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 255, 127, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 255, 127, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 255, 127, 255);
	}
		
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBossGauge->Unlock();
}
//===========
// �`�揈��
//===========
void DrawBossGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�Q�[�W
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBossGauge, 0, sizeof(VERTEX_2D));
	
	pDevice->SetTexture(0, g_pTextureBossGauge);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//�g
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBossGaugeBack, 0, sizeof(VERTEX_2D));
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBossGaugeBack);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���O
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBossName, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTextureBossName);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}