//==============================
//
//  �|�[�Y����[Tutorial.h]
//  Author:kaiti
//
//==============================
#include "Tutorial.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"
#include "buttonUI.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TUTORIAL_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;

LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTutoMAX = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutoMAX = NULL;

LPDIRECT3DTEXTURE9 g_pTextureSlash = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSlash = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTutoNo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutoNo = NULL;

TUTORIAL g_TutorialType = TUTORIAL_MOVE;
int g_CntTutorialState = 0;
D3DXVECTOR3 g_ButtonSize;
float ButtonY;
//============
// ����������
//============
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial001.jpg", &g_pTextureTutorial[TUTORIAL_MOVE]);		 //
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial004.jpg", &g_pTextureTutorial[TUTORIAL_ROLL]);		 //
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial002.jpg", &g_pTextureTutorial[TUTORIAL_SKILL]);		 //
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial006.jpg", &g_pTextureTutorial[TUTORIAL_SKILLCHENGE]); //
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial003.jpg", &g_pTextureTutorial[TUTORIAL_ITEM]);		 //
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial005.jpg", &g_pTextureTutorial[TUTORIAL_LOCKON]);		 //
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sirusi.png", &g_pTextureArrow);		 //

	g_TutorialType = TUTORIAL_MOVE;
	g_ButtonSize = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
	ButtonY = 50.0f;

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	
	//�`���[�g���A��
	{
		D3DXVECTOR3 Tutorialpos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTutorial,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(Tutorialpos.x - TUTO_X, Tutorialpos.y - TUTO_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Tutorialpos.x + TUTO_X, Tutorialpos.y - TUTO_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Tutorialpos.x - TUTO_X, Tutorialpos.y + TUTO_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Tutorialpos.x + TUTO_X, Tutorialpos.y + TUTO_Y, 0.0f);

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
		g_pVtxBuffTutorial->Unlock();
	}

	//���
	{
		D3DXVECTOR3 Arrowpos = D3DXVECTOR3(120.0f, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffArrow,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(Arrowpos.x - YAJIRUSI_SIZE, Arrowpos.y - YAJIRUSI_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Arrowpos.x + YAJIRUSI_SIZE, Arrowpos.y - YAJIRUSI_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Arrowpos.x - YAJIRUSI_SIZE, Arrowpos.y + YAJIRUSI_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Arrowpos.x + YAJIRUSI_SIZE, Arrowpos.y + YAJIRUSI_SIZE, 0.0f);

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
			if (nCnt == 0)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

				SetButtonUi(BUTTONUI_AKEY, D3DXVECTOR3(Arrowpos.x - g_ButtonSize.x, Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
				SetButtonUi(BUTTONUI_L1, D3DXVECTOR3(Arrowpos.x + g_ButtonSize.x, Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
			}
			else if (nCnt == 1)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				SetButtonUi(BUTTONUI_DKEY, D3DXVECTOR3(Arrowpos.x - g_ButtonSize.x, Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
				SetButtonUi(BUTTONUI_R1, D3DXVECTOR3(Arrowpos.x + g_ButtonSize.x, Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
			}

			Arrowpos.x += 1030.0f;
			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffArrow->Unlock();
	}


}
//==========
//�I������
//==========
void UninitTutorial(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdateTutorial(void)
{
	ChangeTutorial();	
	//ChangeTutorialArrow();
	
	//VERTEX_2D* pVtx;
}
//===========
//�`�揈��
//===========
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�`���[�g���A��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial[g_TutorialType]);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureArrow);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//
//
//
void ChangeTutorial(void)
{
	if (KeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_R1) == true)
	{
		switch (g_TutorialType)
		{
		case TUTORIAL_MOVE:
			g_TutorialType = TUTORIAL_ROLL;
			break;
		case TUTORIAL_ROLL:
			g_TutorialType = TUTORIAL_SKILL;
			break;
		case TUTORIAL_SKILL:
			g_TutorialType = TUTORIAL_SKILLCHENGE;
			break;
		case TUTORIAL_SKILLCHENGE:
			g_TutorialType = TUTORIAL_ITEM;
			break;
		case TUTORIAL_ITEM:
			g_TutorialType = TUTORIAL_LOCKON;
			break;
		case TUTORIAL_LOCKON:
			SetEnableTutorial(false);
			DeleteTutorialUI();
			break;

		default:
			break;
		}
	}
	else if (KeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_L1) == true)
	{
		switch (g_TutorialType)
		{
		case TUTORIAL_MOVE:
			break;
		case TUTORIAL_ROLL:
			g_TutorialType = TUTORIAL_MOVE;
			break;
		case TUTORIAL_SKILL:
			g_TutorialType = TUTORIAL_ROLL;
			break;
		case TUTORIAL_SKILLCHENGE:
			g_TutorialType = TUTORIAL_SKILL;
			break;
		case TUTORIAL_ITEM:
			g_TutorialType = TUTORIAL_SKILLCHENGE;
			break;
		case TUTORIAL_LOCKON:
			g_TutorialType = TUTORIAL_ITEM;
			break;

		default:
			break;
		}
	}
}

//
//
//
void ChangeTutorialArrow(void)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	
	
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffArrow->Unlock();
}

//
//
//
void SetTutorial(TUTORIAL type)
{
	g_TutorialType = type;

	SetButtonUi(BUTTONUI_AKEY, D3DXVECTOR3(120.0f - g_ButtonSize.x, SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
	SetButtonUi(BUTTONUI_L1, D3DXVECTOR3(120.0f + g_ButtonSize.x, SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);

	SetButtonUi(BUTTONUI_DKEY, D3DXVECTOR3(1150.0f - g_ButtonSize.x, SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
	SetButtonUi(BUTTONUI_R1, D3DXVECTOR3(1150.0f + g_ButtonSize.x, SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
}

//
//
//
void SetTutorialNo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	VERTEX_2D* pVtx;

	//
	{
		D3DXVECTOR3 Arrowpos = D3DXVECTOR3(120.0f, SCREEN_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffArrow,
			NULL);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);
		
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(Arrowpos.x - YAJIRUSI_SIZE, Arrowpos.y - YAJIRUSI_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Arrowpos.x + YAJIRUSI_SIZE, Arrowpos.y - YAJIRUSI_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Arrowpos.x - YAJIRUSI_SIZE, Arrowpos.y + YAJIRUSI_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Arrowpos.x + YAJIRUSI_SIZE, Arrowpos.y + YAJIRUSI_SIZE, 0.0f);
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
		g_pVtxBuffArrow->Unlock();
	}

}