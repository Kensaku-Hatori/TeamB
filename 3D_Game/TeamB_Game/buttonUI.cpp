//==============================
//
//  �~�j�}�b�v����[ButtonUi.cpp]
//  Author:kaiti
//
//==============================
#include "ButtonUi.h"
#include "player.h"
//�O���[�o���ϐ�
//�~�b�V����
LPDIRECT3DTEXTURE9 g_pTextureButtonUi[BUTTONUI_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffButtonUi = NULL;

ButtonUi g_ButtonUi[MAX_BUTTONUI];

//=============
// ����������
//=============
void InitButtonUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ENTERkey.png", &g_pTextureButtonUi[BUTTONUI_WHEEL]);	//�g
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ESCkey.png", &g_pTextureButtonUi[BUTTONUI_SAYU]);	//�g

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BUTTONUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffButtonUi,
		NULL);
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		g_ButtonUi[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ButtonUi[nCnt].size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		g_ButtonUi[nCnt].ButtonUi = BUTTONUI_WHEEL;
		g_ButtonUi[nCnt].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
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
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffButtonUi->Unlock();
}
//==========
// �I������
//==========
void UninitButtonUi(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_pTextureButtonUi[nCnt] != NULL)
		{
			g_pTextureButtonUi[nCnt]->Release();
			g_pTextureButtonUi[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffButtonUi != NULL)
	{
		g_pVtxBuffButtonUi->Release();
		g_pVtxBuffButtonUi = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateButtonUi(void)
{
}
//===========
// �`�揈��
//===========
void DrawButtonUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�g
	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUi[nCnt].bUse == true)
		{
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffButtonUi, 0, sizeof(VERTEX_2D));
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureButtonUi[g_ButtonUi[nCnt].ButtonUi]);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//===========
// UI�̐ݒ�
//===========
void SetButtonUi(BUTTONUI type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUi[nCnt].bUse == false)
		{
			g_ButtonUi[nCnt].pos = pos;
			g_ButtonUi[nCnt].size = size;
			g_ButtonUi[nCnt].ButtonUi = type;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
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


			g_ButtonUi[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffButtonUi->Unlock();
}