//==============================
//
//  �I������[titleinfo.h]
//  Author:kaiti
//
//==============================
#include "titleinfo.h"
#include "game.h"
#include "input.h"
#include "ranking.h"
#include "fade.h"
//#include "tutorial.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"

#define MAX_TEXTURE (3)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturetitleinfo[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitleinfo = NULL;
D3DXVECTOR3 g_Selectpos;
//���S
LPDIRECT3DTEXTURE9 g_pTexturetitleinfoLogo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitleinfoLogo = NULL;
D3DXVECTOR3 g_Logopos;

TITLEINFO g_titleinfoMenu=TITLE_START;
//============
//����������
//============
void InitTitleInfo(void)
{
	g_titleinfoMenu = TITLE_START;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Selectpos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gamestart.png", &g_pTexturetitleinfo[0]); //START
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\titleranking.png", &g_pTexturetitleinfo[1]); //�����L���O
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\exit.png", &g_pTexturetitleinfo[2]); //�����L���O

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBufftitleinfo,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufftitleinfo->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{//���j���[
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Selectpos.x - TITLESELECT_WIDTH / 2, g_Selectpos.y - TITLESELECT_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Selectpos.x + TITLESELECT_WIDTH / 2, g_Selectpos.y - TITLESELECT_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Selectpos.x - TITLESELECT_WIDTH / 2, g_Selectpos.y + TITLESELECT_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Selectpos.x + TITLESELECT_WIDTH / 2, g_Selectpos.y + TITLESELECT_HEIGHT / 2, 0.0f);
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

		g_Selectpos.y += 120.0f;
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBufftitleinfo->Unlock();


	//���S
	g_Logopos = D3DXVECTOR3(640.0f, 0.0f, 0.0f);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title.png", &g_pTexturetitleinfoLogo); //START
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftitleinfoLogo,
		NULL);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufftitleinfoLogo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);
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
	g_pVtxBufftitleinfoLogo->Unlock();
}
//==========
//�I������
//==========
void UninitTitleInfo(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturetitleinfo[nCnt] != NULL)
		{
			g_pTexturetitleinfo[nCnt]->Release();
			g_pTexturetitleinfo[nCnt] = NULL;
		}
	}
	//�e�N�X�`���̔j��
	if (g_pTexturetitleinfoLogo != NULL)
	{
		g_pTexturetitleinfoLogo->Release();
		g_pTexturetitleinfoLogo = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBufftitleinfo != NULL && g_pVtxBufftitleinfoLogo != NULL)
	{
		g_pVtxBufftitleinfo->Release();
		g_pVtxBufftitleinfo = NULL;
		g_pVtxBufftitleinfoLogo->Release();
		g_pVtxBufftitleinfoLogo = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdateTitleInfo(int zDelta)
{
	FADE g_fade;
	g_fade = GetFade();

	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufftitleinfo->Lock(0, 0, (void**)&pVtx, 0);

	//���j���[�̑I��(�㉺)
	//START�ɂ���ꍇ
	if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_titleinfoMenu==TITLE_START)
	{
		g_titleinfoMenu = TITLE_FIN;
	}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_titleinfoMenu == TITLE_START)
	{
		g_titleinfoMenu = TITLE_RANK;
	}
	//RANK�ɂ���ꍇ
	else if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_titleinfoMenu == TITLE_RANK)
	{
		g_titleinfoMenu = TITLE_START;
	}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_titleinfoMenu == TITLE_RANK)
	{
		g_titleinfoMenu = TITLE_FIN;
	}
	//FIN�ɂ���ꍇ
	else if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_titleinfoMenu == TITLE_FIN)
	{
		g_titleinfoMenu = TITLE_RANK;
	}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_titleinfoMenu == TITLE_FIN)
	{
		g_titleinfoMenu = TITLE_START;
	}

	//���_�J���[�̐ݒ�(���邭)
	if (g_titleinfoMenu == TITLE_START)
	{	//START�ɂ���ꍇ
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (g_titleinfoMenu == TITLE_RANK)
	{	//RULE�ɂ���ꍇ
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	else if (g_titleinfoMenu == TITLE_FIN)
	{	//RULE�ɂ���ꍇ
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufftitleinfo->Unlock();


	if ((KeyboardTrigger(DIK_RETURN) == true|| GetJoypadTrigger(JOYKEY_A) == true || OnMouseDown(0) == true) && g_fade == FADE_NONE)
	{//ENTER�������ꂽ
		if (g_Logopos.y < LOGO_END_Y)
		{//���S������Ă��Ă��鎞
			g_Logopos.y += LOGO_END_Y;
		}
		else
		{//���S������؂����Ƃ�
			StopSound();

			//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
			if (g_titleinfoMenu == TITLE_START)
			{	//START�ɂ���ꍇ
				SetFade(MODE_STAGEONE);
				pPlayer->bfirst = true;

				PlaySound(SOUND_LABEL_GAME);
			}
			else if (g_titleinfoMenu == TITLE_RANK)
			{	//RANK�ɂ���ꍇ
				SetFade(MODE_RANK);
				SetRankMode(RANKMODE_SELECT);

				PlaySound(SOUND_LABEL_RANKING);
			}
			else if (g_titleinfoMenu == TITLE_FIN)
			{	//FIN�ɂ���ꍇ
				SetFade(MODE_END);
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufftitleinfoLogo->Lock(0, 0, (void**)&pVtx, 0);

	//���S��������
	if (g_Logopos.y < LOGO_END_Y)
	{
		g_Logopos.y++;
	}
	//���S��Y����
	if (g_Logopos.y >= LOGO_END_Y)
	{
		g_Logopos.y = LOGO_END_Y;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);


	//���_�o�b�t�@���A�����b�N
	g_pVtxBufftitleinfoLogo->Unlock();
}
//===========
//�`�揈��
//===========
void DrawTitleInfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufftitleinfo, 0, sizeof(VERTEX_2D));

	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturetitleinfo[nCnt]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufftitleinfoLogo, 0, sizeof(VERTEX_2D));
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturetitleinfoLogo);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}