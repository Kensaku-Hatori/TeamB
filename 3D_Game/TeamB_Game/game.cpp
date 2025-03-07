//================================
//
//  �Q�[����ʕ\������[game.cpp]
//  Author:kaiti
//
//================================

#include "game.h"
#include "result.h"
#include "resultinfo.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "shadow.h"
#include "meshwall.h"
#include "meshfield.h"
#include "fade.h"
#include "pause.h"
#include "sound.h"
#include "particle.h"
#include "skill.h"
#include "ui.h"
#include "particleEditer.h"
#include "loadstage.h"
#include "model.h"
#include "enemy.h"
#include "Item.h"
#include "loadmotion.h"
#include "wave.h"
#include "impact.h"
#include "invisiblewall.h"
#include "Item.h"
#include "circle.h"
#include "arrow.h"
#include "boss.h"
#include <time.h>
#include "HPgauge.h"
#include "mouse.h"
#include "billboard.h"
#include "tutorial.h"
#include "buttonUI.h"

//�O���[�o���ϐ�
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //�|�[�Y�����ǂ���
bool bAbo = false;//�S�Ńt���O
bool g_bTutorial = true;

//=============
// ����������
//=============
void InitGame(void)
{
	MODE Mode = GetMode();
	//���b�V���t�B�[���h�̏�����
	InitMeshfield();

	//�T�[�N���̏�����
	InitCircle();

	//���̏�����
	InitArrow();

	//�e�̏�����
	InitShadow();

	//�Ռ��g�̏�����
	InitImpact();

	//HP�Q�[�W�̏�����
	InitHPgauge();

	//�v���C���[�̏�����
	InitPlayer();

	//�G�̏�����
	InitBoss();

	//�G�̏�����
	InitEnemy();

	//���@�̏�����
	InitSkill();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//���b�V���ǂ̏�����
	InitMeshWall();

	//�A�C�e��������
	InitItem();

	//�J�����̏�����
	InitCamera();

	//���C�g�̏�����
	InitLight();

	//UI�̏�����
	InitUi();

	//�|�[�Y�̏�����
	InitPause();

	//�X�e�[�W�̏�����
	InitStageModel();

	InitBiillboard();

	//���[�V�����̏�����
	InitMotion();

	//���f���r���[���[�̓Ǎ�
	LoadModelViewer(Mode);

	//�E�F�[�u�̏���������
	InitWave(Mode);

	//�E�F�[�u�̓Ǎ�����
	LoadWave();

	// �����Ȃ��ǂ̏���������
	InitInvisibleWall();

	InitTutorial();

	//�e������
	g_gamestate = GAMESTATE_NORMAL;		//�Q�[���X�e�[�g
	g_nCounterGameState = 0;			//�X�e�[�g�J�E���^�[
	srand((int)time(0));				//�V�[�h�l(�A�C�e��rand)

	g_bPause = false;					//�|�[�Y���Ă��Ȃ���Ԃ�
	bAbo = false;						//�S�ł��Ă��Ȃ���Ԃ�

	if (Mode == MODE_STAGEONE)
	{
		g_bTutorial = true;
	}
	else
	{
		g_bTutorial = false;
	}
}

//===========
// �I������
//===========
void UninitGame(void)
{
	//�|�[�Y�̏I������
	UninitPause();

	//�T�[�N���̏I������
	UninitCircle();

	//���̏I������
	UninitArrow();

	//�e�̏I������
	UninitShadow();

	//�Ռ��g�̏I������
	UninitImpact();

	//HO�Q�[�W�̏I������
	UninitHPgauge();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	//�G�̏I������
	UninitBoss();

	//���@�̏I������
	UninitSkill();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//���b�V���ǂ̏I������
	UninitMeshWall();

	//�A�C�e���̏I������
	UninitItem();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//UI�̏I������
	UninitUi();

	//�X�e�[�W�̏I������
	UninitStageModel();

	UninitBiillboard();

	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	UninitTutorial();
}

//===========
// �X�V����
//===========
void UpdateGame(void)
{
	MODE Mode = GetMode();

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//�|�[�Y�L�[�������ꂽ
		g_bPause = g_bPause ? false : true;
	}
	else if ((KeyboardTrigger(DIK_TAB) == true || GetJoypadTrigger(JOYKEY_BACK) == true) && g_bPause == false)
	{
		if (Mode == MODE_STAGEONE)
		{
			g_bTutorial = g_bTutorial ? false : true;
			if (g_bTutorial == true)
			{
				SetTutorial(TUTORIAL_MOVE);
			}
		}
	}

	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		if (g_bPause == true)
		{//�|�[�Y��
			//�|�[�Y�̍X�V����
			g_gamestate = GAMESTATE_PAUSE;
			UpdatePause(0);
			g_bTutorial = false;
		}
		else if (g_bTutorial == true && g_bPause == false)
		{//�|�[�Y��
			//�|�[�Y�̍X�V����
			UpdateTutorial();
		}
		else if (g_bPause == false && g_bTutorial == false)
		{
			//���b�V���t�B�[���h�̍X�V����
			UpdateMeshfield();

			//�T�[�N���̍X�V����
			UpdateCircle();

			//���̍X�V����
			UpdateArrow();

			//�e�̍X�V����
			UpdateShadow();

			//�Ռ��g�̍X�V����
			UpdateImpact();

			//HP�Q�[�W�̍X�V����
			UpdateHPgauge();

			//�v���C���[�̍X�V����
			UpdatePlayer();

			// �����Ȃ��ǂ̍X�V����
			UpdateInvisibleWall();

			//�G�̍X�V����
			UpdateEnemy();

			//�G�̍X�V����
			UpdateBoss();

			//���@�̍X�V����
			UpdateSkill();

			//�G�t�F�N�g�̍X�V����
			UpdateEffect();

			//�p�[�e�B�N���̍X�V����
			UpdateParticle(true);

#ifdef _DEBUG

			//�G�f�B�^�[�̐؂�ւ�
			if (GetKeyboardPress(DIK_E) && GetKeyboardPress(DIK_F2))
			{
				InitParticleEditer();
				SetGameState(GAMESTATE_EFFECTEDITER);
			}
			//���U���g�ɔ��
			if (KeyboardTrigger(DIK_1) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{//Clear
				SetFade(MODE_RESULT);
				SetResult(RESULT_CLEAR);
			}
			if (KeyboardTrigger(DIK_2) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{//over
				SetFade(MODE_RESULT);
				SetResult(RESULT_GAMEOVER);
			}

#endif // DEBUG

			////�u���b�N�̍X�V����
			//UpdateBlock();

			////�����̍X�V����
			//UpdateExplosion();

			////���b�V���V�����_�[�̍X�V����
			//UpdateMeshCylinder();

			////�ǂ̍X�V����
			//UpdateWall();

			//���b�V���ǂ̍X�V����
			UpdateMeshWall();

			//�A�C�e���̍X�V
			UpdateItem();

			//�J�����̍X�V����
			UpdateCamera();

			//���C�g�̍X�V����
			UpdateLight();

			//UI�̍X�V����
			UpdateUi();

			//�X�e�[�W�̍X�V����
			UpdateStageModel();

			//�G�̐����擾����
			int* NumEnemy = GetNumEnemy();
			Player* pPlayer = GetPlayer();
			MODE mode = GetMode();

			if (*NumEnemy <= 0)
			{
				int i = (int)*NumEnemy;
				if (bAbo != true)
				{
					if (mode != MODE_STAGEFOUR)
					{
						//�G���A�ړ��ꏊ�擾
						D3DXVECTOR3 pos = GetBottom();

						//�T�[�N�����o��
						SetCircle(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 150, 150), 8, 0, 200.0f, 100.0f, true, false);
					}
				}
				bAbo = true;
			}

			//�S�Ă�wave���I������Ȃ�
			if (GetFinish() == true)
			{
				g_gamestate = GAMESTATE_CLEAR;
			}

			//�Q�[���X�e�[�g�Ǘ�
			switch (g_gamestate)
			{
			case GAMESTATE_NORMAL:

				break;

			case GAMESTATE_CLEAR:

				g_nCounterGameState++;
				if (g_nCounterGameState >= 30)
				{
					g_gamestate = GAMESTATE_NONE;
					//���[�h�����U���g�ɂ���
					SetFade(MODE_RESULT);
					SetResult(RESULT_CLEAR);

					StopSound();
					PlaySound(SOUND_LABEL_GAMECLEAR);
				}
				break;

			case GAMESTATE_GAMEOVER:

				g_nCounterGameState++;
				if (g_nCounterGameState >= 30)
				{
					g_gamestate = GAMESTATE_NONE;
					//���[�h�����U���g�ɂ���
					SetFade(MODE_RESULT);
					SetResult(RESULT_GAMEOVER);

					StopSound();
					PlaySound(SOUND_LABEL_GAMEOVER);
				}
				break;

			case GAMESTATE_EFFECTEDITER:

				break;
			}
		}
	}
	else
	{
		//�p�[�e�B�N���G�f�B�^�[�̍X�V����
		UpdateParticleEditer();
	}
}

//===========
// �`�揈��
//===========
void DrawGame(void)
{
	//�J�����̐ݒ菈��
	SetCamera();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();

	//�e�̕`�揈��
	DrawShadow();

	//���@�̕`�揈��
	DrawSkill();

	//���b�V���ǂ̕`�揈��
	DrawMeshWall();

	//�A�C�e���̕`�揈��
	DrawItemBillboard();

	//�G�f�B�^�[�ł͂Ȃ��Ȃ�
	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�X�e�[�W�̕`�揈��
		DrawStageModel();

		//�r���{�[�h�̕`�揈��
		DrawBiillboard();

		//�G�̕`�揈��
		DrawEnemy();

		//�G�̕`�揈��
		DrawBoss();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//HP�Q�[�W�̕`�揈��
		DrawHPgauge();

		//���̕`�揈��
		DrawArrow();

		//�T�[�N���̕`�揈��
		DrawCircle();

		//UI�̕`�揈��
		DrawUi();

		//�Ռ��g�̕`�揈��
		DrawImpact();
	}
	//�G�f�B�^�[�Ȃ�
	else
	{
		//�G�t�F�N�g�̕`�揈��
		DrawEffect();
	}

	//�|�[�Y���Ă���Ȃ�
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
	//�|�[�Y���Ă���Ȃ�
	else if (g_bTutorial == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawTutorial();
		DrawTutorialButtonUi();
	}
}

//===============
// �Q�[���̏��
//===============
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
}

//=====================
// �Q�[���̏�Ԃ̎擾
//=====================
GAMESTATE GetGameSatate(void)
{
	return g_gamestate;
}

//=======================
// �|�[�Y�̗L�������ݒ�
//=======================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//
//
//
void SetEnableTutorial(bool bTutorial)
{
	g_bTutorial = bTutorial;
}