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
//#include "meshcylinder.h"
#include "meshfield.h"
#include "fade.h"
#include "pause.h"
//#include "sound.h"
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

//�O���[�o���ϐ�
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //�|�[�Y�����ǂ���

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

	////�u���b�N�̏�����
	//InitBlock();

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

	////�����̏�����
	//InitExplosion();

	//���b�V���V�����_�[�̏�����
	//InitMeshCylinder();

	////�ǂ̏�����
	//InitWall();

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

	//�e������
	g_gamestate = GAMESTATE_NORMAL;		//�Q�[���X�e�[�g
	g_nCounterGameState = 0;			//�X�e�[�g�J�E���^�[
	srand((int)time(0));				//�V�[�h�l(�A�C�e��rand)

	g_bPause = false;					//�|�[�Y���Ă��Ȃ���Ԃ�
}

//===========
// �I������
//===========
void UninitGame(void)
{
	//�|�[�Y�̏I������
	UninitPause();

	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	//�T�[�N���̏I������
	UninitCircle();

	//���̏I������
	UninitArrow();

	//�e�̏I������
	UninitShadow();

	//�Ռ��g�̏I������
	UninitImpact();

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

	//UninitBlock();

	//UninitExplosion();

	//UninitMeshCylinder();

	//UninitWall();

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
}

//===========
// �X�V����
//===========
void UpdateGame(void)
{
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//�|�[�Y�L�[�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		if (g_bPause == true)
		{//�|�[�Y��
			//�|�[�Y�̍X�V����
			UpdatePause();
		}
		else if (g_bPause == false)
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

	////�u���b�N�̕`�揈��
	//DrawBlock();

	////�G�̕`�揈��
	//DrawEnemy();

	//�����̕`�揈��
	//DrawExplosion();

	//���@�̕`�揈��
	DrawSkill();

	//���b�V���V�����_�[�̕`�揈��
	//DrawMeshCylinder();

	////�ǂ̕`�揈��
	//DrawWall();

	//���b�V���ǂ̕`�揈��
	DrawMeshWall();

	//�X�e�[�W�̕`�揈��
	DrawStageModel();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�A�C�e���̕`�揈��
	DrawItemBillboard();

	//�G�f�B�^�[�ł͂Ȃ��Ȃ�
	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�G�̕`�揈��
		DrawEnemy();

		//�G�̕`�揈��
		DrawBoss();

		//���̕`�揈��
		DrawArrow();

		//�T�[�N���̕`�揈��
		DrawCircle();

		//UI�̕`�揈��
		DrawUi();

		//�Ռ��g�̕`�揈��
		DrawImpact();
	}

	//�|�[�Y���Ă���Ȃ�
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
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