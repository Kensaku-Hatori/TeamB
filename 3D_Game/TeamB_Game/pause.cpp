//==============================
//
//  �|�[�Y����[pause.h]
//  Author:kaiti
//
//==============================
#include "pause.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"

#define MAX_TEXTURE (4)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
PAUSE_MENU g_pauseMenu=PAUSE_MENU_CONTNUE;
D3DXVECTOR3 g_Pausepos;
//============
//����������
//============
void InitPause(void)
{
	g_pauseMenu = PAUSE_MENU_CONTNUE;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause.jpg", &g_pTexturePause[0]); //�|�[�Y�̔w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\continue.png", &g_pTexturePause[1]); //�߂�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\retry.png", &g_pTexturePause[2]); //��蒼��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\quit.png", &g_pTexturePause[3]); //�^�C�g���ɖ߂�

	g_Pausepos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSESELECT_HEIGHT, 0.0f);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffPause,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TEXTURE ; nCnt++)
	{//�|�[�Y���j���[
		if (nCnt == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 127);
			pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 127);
			pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 127);
			pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 127);

		}
		else
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Pausepos.x - (PAUSESELECT_WIDTH / 2), g_Pausepos.y - (PAUSESELECT_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Pausepos.x + (PAUSESELECT_WIDTH / 2), g_Pausepos.y - (PAUSESELECT_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Pausepos.x - (PAUSESELECT_WIDTH / 2), g_Pausepos.y + (PAUSESELECT_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Pausepos.x + (PAUSESELECT_WIDTH / 2), g_Pausepos.y + (PAUSESELECT_HEIGHT / 2), 0.0f);
			g_Pausepos.y += PAUSESELECT_HEIGHT * 1.25;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}
//==========
//�I������
//==========
void UninitPause(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdatePause(int zDelta)
{
	FADE g_fade;
	g_fade = GetFade();

	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
		
	//���j���[�̑I��(�㉺)
	//Contnue�ɂ���ꍇ
	if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_pauseMenu == PAUSE_MENU_CONTNUE)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_pauseMenu == PAUSE_MENU_CONTNUE)
		{
			g_pauseMenu = PAUSE_MENU_RETRY;
		}
	//RETRY�ɂ���ꍇ
	else if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_pauseMenu == PAUSE_MENU_RETRY)
		{
			g_pauseMenu = PAUSE_MENU_CONTNUE;
		}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_pauseMenu == PAUSE_MENU_RETRY)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
	//QUIT�ɂ���ꍇ
	else if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_pauseMenu == PAUSE_MENU_QUIT)
		{
			g_pauseMenu = PAUSE_MENU_RETRY;
		}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_pauseMenu == PAUSE_MENU_QUIT)
		{
			g_pauseMenu = PAUSE_MENU_CONTNUE;
		}

	//���_�J���[�̐ݒ�(���邭)
	if (g_pauseMenu == PAUSE_MENU_CONTNUE)
		{	//Contnue�ɂ���ꍇ
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 0, 255);

			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}
	else if (g_pauseMenu == PAUSE_MENU_RETRY)
		{	//RETRY�ɂ���ꍇ
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 0, 255);

			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	else if (g_pauseMenu == PAUSE_MENU_QUIT)
		{	//QUIT�ɂ���ꍇ
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();

	if ((KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true || OnMouseDown(0) == true) && g_fade == FADE_NONE)
		{
			//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
			if (g_pauseMenu == PAUSE_MENU_CONTNUE)
			{	//Contnue�ɂ���ꍇ
				SetEnablePause(false);
				SetGameState(GAMESTATE_NORMAL);
			}
			else if (g_pauseMenu == PAUSE_MENU_RETRY)
			{	//RETRY�ɂ���ꍇ
				SetFade(MODE_STAGEONE);
				pPlayer->bfirst = true;

				StopSound();
				PlaySound(SOUND_LABEL_GAME);
			}
			else if (g_pauseMenu == PAUSE_MENU_QUIT)
			{	//QUIT�ɂ���ꍇ
				SetFade(MODE_TITLE);

				StopSound();
				PlaySound(SOUND_LABEL_TITLE);
			}
		}
}
//===========
//�`�揈��
//===========
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}