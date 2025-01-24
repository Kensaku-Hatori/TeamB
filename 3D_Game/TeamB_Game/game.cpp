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
//#include "wall.h"
//#include "explosion.h"
//#include "effect.h"
//#include "block.h"
#include "meshwall.h"
//#include "meshcylinder.h"
#include "meshfield.h"
#include "fade.h"
#include "pause.h"
//#include "sound.h"
//#include "enemy.h"
#include "particle.h"
#include "skill.h"
#include "ui.h"
#include "particleEditer.h"
#include "loadstage.h"
#include "model.h"

//�O���[�o���ϐ�
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //�|�[�Y�����ǂ���

//=============
// ����������
//=============
void InitGame(void)
{
	InitMeshfield();

	InitShadow();

	//InitBlock();

	InitPlayer();

	//InitEnemy();

	InitSkill();

	InitEffect();

	InitParticle();

	//InitExplosion();

	//InitMeshCylinder();

	//InitWall();

	InitMeshWall();
	
	InitCamera();

	InitLight();

	InitUi();

	InitPause();

	InitStageModel();

	LoadModelViewer();

	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;

	g_bPause = false;  //�|�[�Y����
}
//===========
// �I������
//===========
void UninitGame(void)
{
	UninitPause();

	UninitShadow();

	UninitPlayer();

	//UninitEnemy();

	UninitSkill();

	UninitEffect();

	//UninitBlock();

	UninitMeshfield();

	//UninitExplosion();

	//UninitMeshCylinder();

	//UninitWall();

	UninitMeshWall();

	UninitCamera();

	UninitLight();

	UninitUi();

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
			UpdateMeshfield();

			UpdateShadow();

			UpdatePlayer();

			//UpdateEnemy();

			UpdateSkill();

			UpdateEffect();

			UpdateParticle(true);

			if (GetKeyboardPress(DIK_E) && GetKeyboardPress(DIK_F2))
			{
				InitParticleEditer();
				SetGameState(GAMESTATE_EFFECTEDITER);
			}

			//UpdateBlock();

			//UpdateExplosion();

			//UpdateMeshCylinder();

			//UpdateWall();

			UpdateMeshWall();

			UpdateCamera();

			UpdateLight();

			UpdateUi();

			UpdateStageModel();

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

			//���U���g�ɔ��
			if (KeyboardTrigger(DIK_1) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{
				SetFade(MODE_RESULT);
				SetResult(RESULT_CLEAR);
			}
			if (KeyboardTrigger(DIK_2) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{
				SetFade(MODE_RESULT);
				SetResult(RESULT_GAMEOVER);
			}
		}
	}
	else
	{
		UpdateParticleEditer();
	}
}
//===========
// �`�揈��
//===========
void DrawGame(void)
{
	SetCamera();

	DrawMeshfield();

	DrawShadow();

	//DrawBlock();


	//DrawEnemy();

	//DrawExplosion();

	DrawSkill();

	DrawEffect();

	//DrawMeshCylinder();

	//DrawWall();

	DrawMeshWall();

	DrawStageModel();

	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		DrawPlayer();
		DrawUi();
	}

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y
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