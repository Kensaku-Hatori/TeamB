//==============================
//
//  �Q�[�W����[Gauge.cpp]
//  Author:kaiti
//
//==============================
#include "gauge.h"
#include "player.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGaugeBack[GAUGETYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGaugeBack = NULL;

LPDIRECT3DTEXTURE9 g_pTextureGauge = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;

Gauge g_gauge[GAUGETYPE_MAX];
//=============
// ����������
//=============
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		g_gauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_gauge[nCnt].type = GAUGETYPE_HP;
		g_gauge[nCnt].size = D3DXVECTOR2(100.0f, 50.0f);
		g_gauge[nCnt].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\hpgauge.png", &g_pTextureGaugeBack[GAUGETYPE_HP]);	//HP �g
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mpgauge.png", &g_pTextureGaugeBack[GAUGETYPE_MP]);	//MP �g
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge00.jpeg", &g_pTextureGauge);	//

	//�Q�[�W
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffGauge,
		                        NULL);
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (nCnt == GAUGETYPE_HP)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(1, 255, 127, 255);
			pVtx[1].col = D3DCOLOR_RGBA(1, 255, 127, 255);
			pVtx[2].col = D3DCOLOR_RGBA(1, 255, 127, 255);
			pVtx[3].col = D3DCOLOR_RGBA(1, 255, 127, 255);
		}
		if (nCnt == GAUGETYPE_MP)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(1, 127, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(1, 127, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(1, 127, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();


	//�g
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGaugeBack,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGaugeBack->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
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
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGaugeBack->Unlock();

}
//==========
// �I������
//==========
void UninitGauge(void)
{
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureGauge != NULL)
		{
			g_pTextureGauge->Release();
			g_pTextureGauge = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureGaugeBack[nCnt] != NULL)
		{
			g_pTextureGaugeBack[nCnt]->Release();
			g_pTextureGaugeBack[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
	if (g_pVtxBuffGaugeBack != NULL)
	{
		g_pVtxBuffGaugeBack->Release();
		g_pVtxBuffGaugeBack = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateGauge(void)
{
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == true)
		{
			if (g_gauge[nCnt].type == GAUGETYPE_HP)
			{
				g_gauge[nCnt].size.x = pPlayer->Status.fHP / 2.85f;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);

				if (pPlayer->Status.fHP <= PLAYER_HP / 5)
				{//��
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 1, 1, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 1, 1, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 1, 1, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 1, 1, 255);
				}
				else if (pPlayer->Status.fHP <= PLAYER_HP / 1.5)
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
			}
			else if (g_gauge[nCnt].type == GAUGETYPE_MP)
			{
				g_gauge[nCnt].size.x = pPlayer->Status.nMP / 1.65f;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();
}
//===========
// �`�揈��
//===========
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�Q�[�W
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureGauge);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//�g
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGaugeBack, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			if (g_gauge[nCnt].type == GAUGETYPE_HP)
			{
				pDevice->SetTexture(0, g_pTextureGaugeBack[GAUGETYPE_HP]);
			}
			else if (g_gauge[nCnt].type == GAUGETYPE_MP)
			{
				pDevice->SetTexture(0, g_pTextureGaugeBack[GAUGETYPE_MP]);
			}
			pDevice->SetTexture(0, g_pTextureGaugeBack[nCnt]);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//==================
// �Q�[�W�̐ݒ�
//==================
void SetGauge(GAUGETYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGaugeBack->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == false)
		{
			VERTEX_2D* pVtx1;
			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx1, 0);

			g_gauge[nCnt].type = type;
			g_gauge[nCnt].pos = pos;

			if (g_gauge[nCnt].type == GAUGETYPE_HP)
			{
				g_gauge[nCnt].size = D3DXVECTOR2(size.x + PLAYER_HP / 10, size.y);
				//���_���W�̐ݒ�
				pVtx1[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx1[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			}
			else if (g_gauge[nCnt].type == GAUGETYPE_MP)
			{
				pVtx1 += 4;
				g_gauge[nCnt].size = D3DXVECTOR2(size.x + PLAYER_MP / 10, size.y);
				//���_���W�̐ݒ�
				pVtx1[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx1[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			}
			g_gauge[nCnt].bUse = true;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffGauge->Unlock();

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);

			//�T�C�Y����
			g_gauge[nCnt].pos.x += 45.f;
			g_gauge[nCnt].size.y -= 5.0f;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGaugeBack->Unlock();
}