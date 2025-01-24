//==============================
//
//  �^�C�}�[����[ItemUI.cpp]
//  Author:kaiti
//
//==============================
#include "itemui.h"
#include "player.h"
//�O���[�o���ϐ�

LPDIRECT3DTEXTURE9 g_pTextureItemUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;

D3DXVECTOR3 g_ItemUIpos;
//=============
// ����������
//=============
void InitItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UIfram.jpg", &g_pTextureItemUI);	//HP �g
	
	g_ItemUIpos = D3DXVECTOR3(25.0f, 150.0f, 0.0f);

	//�Q�[�W
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffItemUI,
		                        NULL);
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_ItemUIpos.x, g_ItemUIpos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_ItemUIpos.x + ITEMUI_X, g_ItemUIpos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_ItemUIpos.x, g_ItemUIpos.y + ITEMUI_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_ItemUIpos.x + ITEMUI_X, g_ItemUIpos.y + ITEMUI_Y, 0.0f);
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
	g_pVtxBuffItemUI->Unlock();
}
//==========
// �I������
//==========
void UninitItemUI(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureItemUI != NULL)
	{
		g_pTextureItemUI->Release();
		g_pTextureItemUI = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItemUI != NULL)
	{
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateItemUI(void)
{

}
//===========
// �`�揈��
//===========
void DrawItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�Q�[�W
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItemUI);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}