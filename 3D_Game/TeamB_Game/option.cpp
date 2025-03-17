//==============================
//
//  �|�[�Y����[Option.h]
//  Author:kaiti
//
//==============================
#include "Option.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"
#include "buttonUI.h"

//�O���[�o���ϐ�
//�`���[�g���A���摜
LPDIRECT3DTEXTURE9 g_pTextureOption = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOption = NULL;
//�w�i
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionBack = NULL;


OPTION g_OptionType = OPTION_KANDO;
//============
// ����������
//============
void InitOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	{
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Option001.jpg", &g_pTextureOption);		 //
		
	}

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//�w�i
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOptionBack,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffOptionBack->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffOptionBack->Unlock();
	}


	//�`���[�g���A��
	{
		D3DXVECTOR3 Optionpos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOption,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(Optionpos.x - TUTO_X, Optionpos.y - TUTO_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Optionpos.x + TUTO_X, Optionpos.y - TUTO_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Optionpos.x - TUTO_X, Optionpos.y + TUTO_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Optionpos.x + TUTO_X, Optionpos.y + TUTO_Y, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffOption->Unlock();
	}

}
//==========
//�I������
//==========
void UninitOption(void)
{
	// �e�N�X�`���̔j��
	UninitTexture(g_pTextureOption);

	// ���_�o�b�t�@�̔j��
	UninitBuffer(g_pVtxBuffOption);
	UninitBuffer(g_pVtxBuffOptionBack);
}
//==========
//�X�V����
//==========
void UpdateOption(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player* pPlayer = GetPlayer();

}
//===========
//�`�揈��
//===========
void DrawOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOptionBack, 0, sizeof(VERTEX_2D));
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�`���[�g���A��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOption, 0, sizeof(VERTEX_2D));
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureOption);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}