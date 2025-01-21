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
//#include "meshwall.h"
//#include "meshcylinder.h"
#include "fade.h"
#include "timer.h"
#include "pause.h"
//#include "sound.h"
//#include "enemy.h"
#include "score.h"
//#include "particle.h"

//�O���[�o���ϐ�
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //�|�[�Y�����ǂ���

//=============
// ����������
//=============
void InitGame(void)
{
	InitPolygon();

	InitShadow();

	//InitBlock();

	InitPlayer();

	//InitEnemy();

	//InitEffect();

	//InitParticle();

	//InitExplosion();

	//InitMeshCylinder();

	//InitWall();

	//InitMeshWall();
	
	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(0);

	InitScore();
	SetScore(0);

	InitPause();

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

	//UninitEffect();

	//UninitParticle();

	//UninitBlock();

	UninitPolygon();

	//UninitExplosion();

	//UninitMeshCylinder();

	//UninitWall();

	//UninitMeshWall();

	UninitCamera();

	UninitLight();

	UninitTimer();

	UninitScore();

}
//===========
// �X�V����
//===========
void UpdateGame(void)
{
	int nTime = GetTimer();

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//�|�[�Y�L�[�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	else if (g_bPause == false)
	{
		UpdatePolygon();

		UpdateShadow();

		UpdatePlayer();

		//UpdateEnemy();

		//UpdateEffect();

		//UpdateParticle();

		//UpdateBlock();

		//UpdateExplosion();

		//UpdateMeshCylinder();

		//UpdateWall();

		//UpdateMeshWall();

		UpdateCamera();

		UpdateLight();

		UpdateTimer();

		UpdateScore();


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
//===========
// �`�揈��
//===========
void DrawGame(void)
{
	SetCamera();

	DrawPolygon();

	DrawShadow();

	//DrawBlock();

	DrawPlayer();

	//DrawEnemy();

	//DrawExplosion();

	//DrawEffect();

	//DrawParticle();

	//DrawMeshCylinder();

	//DrawWall();

	//DrawMeshWall();

	DrawTimer();

	DrawScore();

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