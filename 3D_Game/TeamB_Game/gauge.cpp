////==============================
////
////  �^�C�}�[����[Gauge.cpp]
////  Author:kaiti
////
////==============================
//#include "gauge.h"
//#include "player.h"
////�O���[�o���ϐ�
//LPDIRECT3DTEXTURE9 g_pTextureGaugeBack = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGaugeBack = NULL;
//
//LPDIRECT3DTEXTURE9 g_pTextureGauge[GAUGETYPE_MAX] = {};
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;
//
//Gauge g_gauge[GAUGETYPE_MAX];
////=============
//// ����������
////=============
//void InitGauge(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		g_gauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_gauge[nCnt].type = GAUGETYPE_HP;
//		g_gauge[nCnt].size = D3DXVECTOR2(100.0f, 50.0f);
//		g_gauge[nCnt].bUse = false;
//	}
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.png", &g_pTextureGaugeBack);	//�g
//
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.png", &g_pTextureGauge[GAUGETYPE_HP]);	//HP
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.jpeg", &g_pTextureGauge[GAUGETYPE_MP]); //MP
//	
//	//�Q�[�W
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
//		                        D3DUSAGE_WRITEONLY,
//		                        FVF_VERTEX_2D,
//		                        D3DPOOL_MANAGED,
//		                        &g_pVtxBuffGauge,
//		                        NULL);
//	//���_�o�b�t�@�̐����E���_���̐ݒ�
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//		
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffGauge->Unlock();
//
//
//	//�g
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffGauge,
//		NULL);
//	//���_�o�b�t�@�̐����E���_���̐ݒ�
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffGauge->Unlock();
//
//}
////==========
//// �I������
////==========
//void UninitGauge(void)
//{
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//�e�N�X�`���̔j��
//		if (g_pTextureGauge[nCnt] != NULL)
//		{
//			g_pTextureGauge[nCnt]->Release();
//			g_pTextureGauge[nCnt] = NULL;
//		}
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffGauge != NULL)
//	{
//		g_pVtxBuffGauge->Release();
//		g_pVtxBuffGauge = NULL;
//	}
//}
////==========
//// �X�V����
////==========
//void UpdateGauge(void)
//{
//	Player* pPlayer = GetPlayer();
//
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//	}
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffGauge->Unlock();
//}
////===========
//// �`�揈��
////===========
//void DrawGauge(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));
//	
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		if (g_gauge[nCnt].bUse == true)
//		{
//			//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, g_pTextureGauge[nCnt]);
//			//�v���C���[�̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
//		}
//	}
//}
////==================
//// �Q�[�W�̐ݒ�
////==================
//void SetGauge(GAUGETYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size)
//{
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		if (g_gauge[nCnt].bUse == false)
//		{
//			g_gauge[nCnt].type = type;
//			g_gauge[nCnt].pos = pos;
//			g_gauge[nCnt].size = size;
//			g_gauge[nCnt].bUse = true;
//		}
//	}
//}