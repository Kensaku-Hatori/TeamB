//==============================
//
//  �|�[�Y����[Option.h]
//  Author:kaiti
//
//==============================
#include "option.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"
#include "buttonUI.h"

//�O���[�o���ϐ�
//�ݒ�
LPDIRECT3DTEXTURE9 g_pTextureOption[OPTION_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOption = NULL;
//�w�i
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionBack = NULL;
//���
LPDIRECT3DTEXTURE9 g_pTextureOptionArrow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionArrow = NULL;
//����
LPDIRECT3DTEXTURE9 g_pTextureOptionNo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionNo = NULL;

Option g_Option;
bool g_bRight;
//============
// ����������
//============
void InitOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();
	MODE mode = GetMode();


	//�e�N�X�`���̓ǂݍ���
	{
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\setting.png", &g_pTextureOption[OPTION_KANDO]);	 // �ݒ荀��
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\setting01.png", &g_pTextureOption[OPTION_SOUND]);	 // �ݒ荀��
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sirusi.png", &g_pTextureOptionArrow);			 // ���
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number002.png", &g_pTextureOptionNo);			 // ����
	}

	if (pPlayer->bfirst == true || mode == MODE_STAGEONE)
	{
		g_Option.cameraSP = 0.5f;
		g_Option.Sound = 0.5f;
	}

	g_Option.type = OPTION_KANDO;
	g_bRight = true;

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
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 190);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 190);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 190);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 190);
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

	//�ݒ�
	{
		D3DXVECTOR3 Optionpos = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * OPTION_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOption,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(Optionpos.x - OPTION_X, Optionpos.y - OPTION_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Optionpos.x + OPTION_X, Optionpos.y - OPTION_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Optionpos.x - OPTION_X, Optionpos.y + OPTION_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Optionpos.x + OPTION_X, Optionpos.y + OPTION_Y, 0.0f);
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

			Optionpos.y += OPTION_Y * 2;
			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffOption->Unlock();
	}

	//���
	{
		D3DXVECTOR3 Arrowpos = D3DXVECTOR3(SCREEN_WIDTH / 4 + 200.0f, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2 * OPTION_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOptionArrow,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffOptionArrow->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(Arrowpos.x - OPTION_YAJIRUSI_SIZE, Arrowpos.y - OPTION_YAJIRUSI_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Arrowpos.x + OPTION_YAJIRUSI_SIZE, Arrowpos.y - OPTION_YAJIRUSI_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Arrowpos.x - OPTION_YAJIRUSI_SIZE, Arrowpos.y + OPTION_YAJIRUSI_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Arrowpos.x + OPTION_YAJIRUSI_SIZE, Arrowpos.y + OPTION_YAJIRUSI_SIZE, 0.0f);

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

			Arrowpos.x += 300.0f;

			if (nCnt == 0 || nCnt == 2)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			}
			else if (nCnt == 1 || nCnt == 3)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
				Arrowpos.y += OPTION_Y * 2;
				Arrowpos.x = SCREEN_WIDTH / 4 + 200.0f;
			}

			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffOptionArrow->Unlock();
	}

	//����
	{
		D3DXVECTOR3 NoPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2 * OPTION_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOptionNo,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffOptionNo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(NoPos.x - OPTION_NO_SIZE, NoPos.y - OPTION_NO_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(NoPos.x + OPTION_NO_SIZE, NoPos.y - OPTION_NO_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(NoPos.x - OPTION_NO_SIZE, NoPos.y + OPTION_NO_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(NoPos.x + OPTION_NO_SIZE, NoPos.y + OPTION_NO_SIZE, 0.0f);
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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;

			NoPos.x += OPTION_NO_SIZE * 2;

			if (nCnt == 1)
			{
				NoPos.x = SCREEN_WIDTH / 2;
				NoPos.y += OPTION_Y * 2;
			}
		}
		SetOptionSound();
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffOptionNo->Unlock();
	}
}
//==========
//�I������
//==========
void UninitOption(void)
{
	for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		UninitTexture(g_pTextureOption[nCnt]);
	}
	// �e�N�X�`���̔j��
	UninitTexture(g_pTextureOptionArrow);
	UninitTexture(g_pTextureOptionNo);

	// ���_�o�b�t�@�̔j��
	UninitBuffer(g_pVtxBuffOption);
	UninitBuffer(g_pVtxBuffOptionBack);
	UninitBuffer(g_pVtxBuffOptionArrow);
	UninitBuffer(g_pVtxBuffOptionNo);

}
//==========
//�X�V����
//==========
void UpdateOption(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player* pPlayer = GetPlayer();

	SelectOption(0);

	switch (g_Option.type)
	{
	case OPTION_KANDO:
		OptionKando();
		break;
	case OPTION_SOUND:
		OptionSound();
		break;

	default:
		break;
	}

	if (OnMouseDown(0) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{
		SetEnableOption(false);
	}

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
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�`���[�g���A��
	for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffOption, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureOption[nCnt]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
	//���
	for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffOptionArrow, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureOptionArrow);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
	//����
	for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffOptionNo, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureOptionNo);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

}
//
//
//
Option* GetOption(void)
{
	return &g_Option;
}
//===========
// ���x�ݒ�
//===========
void OptionKando(void)
{
	if (KeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
	{
		g_Option.cameraSP += 0.1f;
		if (g_Option.cameraSP >= 1.0f)
		{
			g_Option.cameraSP = 1.0f;
		}
		g_bRight = true;
	}
	else if (KeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
	{
		g_Option.cameraSP -= 0.1f;
		if (g_Option.cameraSP <= 0.1f)
		{
			g_Option.cameraSP = 0.1f;
		}
		g_bRight = false;
	}

	SetOptionKando();
}
//===========
// ���x�ݒ�
//===========
void SetOptionKando(void)
{
	int aPosTexU[2];
	float nkando = g_Option.cameraSP * 10;

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOptionNo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		aPosTexU[nCnt] = ((int)nkando % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffOptionNo->Unlock();
}
void OptionSound(void)
{
	if (KeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
	{
		g_Option.Sound += 0.1f;
		if (g_Option.Sound >= 1.0f)
		{
			g_Option.Sound = 1.0f;
		}
		g_bRight = true;
	}
	else if (KeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
	{
		g_Option.Sound -= 0.1f;
		if (g_Option.Sound <= 0.1f)
		{
			g_Option.Sound = 0.1f;
		}
		g_bRight = false;
	}

	SetOptionSound();

}
void SetOptionSound(void)
{
	int aPosTexU[2];
	float nkando = g_Option.Sound * 10;

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOptionNo->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * 2;

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		aPosTexU[nCnt] = ((int)nkando % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffOptionNo->Unlock();

}
//=================
// �ݒ荀�ڂ̑I��
//=================
void SelectOption(int zDelta)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

	//���j���[�̑I��(�㉺)
	//Contnue�ɂ���ꍇ
	if (KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0)
	{
		PlaySound(SOUND_LABEL_SELECT);
		switch (g_Option.type)
		{
		case OPTION_KANDO:
			g_Option.type = OPTION_SOUND;
			break;
		case OPTION_SOUND:
			g_Option.type = OPTION_KANDO;

			break;
		default:
			break;
		}
	}
	else if (KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0)
	{
		PlaySound(SOUND_LABEL_SELECT);
		switch (g_Option.type)
		{
		case OPTION_KANDO:
			g_Option.type = OPTION_SOUND;
			break;
		case OPTION_SOUND:
			g_Option.type = OPTION_KANDO;
			break;
		default:
			break;
		}
	}

	//���_�J���[�̐ݒ�(���邭)
	for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
	{
		if (g_Option.type == OPTION_KANDO)
		{	//Contnue�ɂ���ꍇ
			if (nCnt == OPTION_KANDO)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 127);
			}
		}
		else if (g_Option.type == OPTION_SOUND)
		{	//Contnue�ɂ���ꍇ
			if (nCnt == OPTION_SOUND)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 127);
			}
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffOption->Unlock();
}