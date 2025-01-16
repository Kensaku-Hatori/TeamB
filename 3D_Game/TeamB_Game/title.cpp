//==============================
//
//  �I������[Title.h]
//  Author:kaiti
//
//==============================
#include "title.h"
#include "title.h"
#include "game.h"
#include "input.h"
#include "ranking.h"
#include "fade.h"
//#include "tutorial.h"
#include "sound.h"
#define MAX_TEXTURE (3)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
TITLE g_TitleMenu=TITLE_START;
//============
//����������
//============
void InitTitle(void)
{
	g_TitleMenu = TITLE_START;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title01.jpg", &g_pTextureTitle[0]); //�w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stage.png", &g_pTextureTitle[1]); //START
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rank.png", &g_pTextureTitle[2]); //�����L���O

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffTitle,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	int nData=0;
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{//�|�[�Y���j���[
		if (nCnt == 0)
		{//�w�i
            //���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
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
		else if (nCnt > 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(400.0f, 300.0f + (nData * 150), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 300.0f + (nData * 150), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 400.0f + (nData * 150), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 400.0f + (nData * 150), 0.0f);
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
			nData++;
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}
//==========
//�I������
//==========
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdateTitle(void)
{
	FADE g_fade;
	g_fade = GetFade();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���j���[�̑I��(�㉺)
	//START�ɂ���ꍇ
	if ((KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true) && g_TitleMenu==TITLE_START)
	{
		g_TitleMenu = TITLE_RANK;
	}
	else if ((KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true) && g_TitleMenu == TITLE_START)
	{
		g_TitleMenu = TITLE_RANK;
	}
	//RANK�ɂ���ꍇ
	else if ((KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true) && g_TitleMenu == TITLE_RANK)
	{
		g_TitleMenu = TITLE_START;
	}
	else if ((KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true) && g_TitleMenu == TITLE_RANK)
	{
		g_TitleMenu = TITLE_START;
	}

	//���_�J���[�̐ݒ�(���邭)
	if (g_TitleMenu == TITLE_START)
	{	//START�ɂ���ꍇ
		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		
		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (g_TitleMenu == TITLE_RANK)
	{	//RULE�ɂ���ꍇ
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	if ((KeyboardTrigger(DIK_RETURN) == true|| GetJoypadTrigger(JOYKEY_A) == true) && g_fade == FADE_NONE)
	{
		//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
		if (g_TitleMenu == TITLE_START)
		{	//START�ɂ���ꍇ
			SetFade(MODE_GAME);
		}
		else if (g_TitleMenu == TITLE_RANK)
		{	//RANK�ɂ���ꍇ
			SetFade(MODE_RANK);
			SetRankMode(RANKMODE_TITLE);
		}
	}
}
//===========
//�`�揈��
//===========
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}