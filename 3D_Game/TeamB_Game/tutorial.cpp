//======================================
//
//  �Q�[����ʕ\������[Tutorial.cpp]
//  Author:kaiti
//
//======================================
#include "tutorial.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "explosion.h"
#include "effect.h"
#include "block.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "fade.h"
#include "timer.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "particle.h"

//�O���[�o���ϐ�
TUTORIAL g_tutorial = TUTORIAL_NONE;
int g_nCounterTUTORIAL = 0;

//=============
// ����������
//=============
void InitTutorial(void)
{
	InitPolygon();

	InitShadow();

	InitBlock();

	InitPlayer();

	InitEnemy();

	InitBiillboard();

	InitEffect();

	InitParticle();

	InitExplosion();

	InitMeshCylinder();

	InitWall();


	InitMeshWall();

	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(MAX_TUTORIALTIME);

	InitScore();
	SetScore(0);

	g_tutorial = TUTORIAL_NORMAL;
	g_nCounterTUTORIAL = 0;
}
//===========
// �I������
//===========
void UninitTutorial(void)
{
	UninitShadow();

	UninitPlayer();

	UninitEnemy();

	UninitBiillboard();

	UninitEffect();

	UninitParticle();

	UninitBlock();

	UninitPolygon();

	UninitExplosion();

	UninitMeshCylinder();

	UninitWall();

	UninitMeshWall();

	UninitCamera();

	UninitLight();

	UninitTimer();

	UninitScore();
}
//===========
// �X�V����
//===========
void UpdateTutorial(void)
{
	int nTime = GetTimer();
	Enemy *pEnemy = GetEnemy();

	UpdatePolygon();

	UpdateShadow();

	UpdatePlayer();

	UpdateEnemy();
	//�G�̖����N��
	if (pEnemy->bUse == false)
	{
		SetEnemy(D3DXVECTOR3(150.0f, 300.0f, 150.0f));
	}

	UpdateBiillboard();

	UpdateEffect();

	UpdateParticle();

	UpdateBlock();

	UpdateExplosion();

	UpdateMeshCylinder();

	UpdateWall();

	UpdateMeshWall();

	UpdateCamera();

	UpdateLight();

	UpdateTimer();

	UpdateScore();

	switch (g_tutorial)
	{
	case TUTORIAL_NORMAL:
		break;
	case TUTORIAL_TIMEOVER:
		g_nCounterTUTORIAL++;
		if (g_nCounterTUTORIAL >= 30)
		{
			g_tutorial = TUTORIAL_NONE;
			//���[�h�����U���g�ɂ���
			SetFade(MODE_TITLE);
		}
		break;
	}
	//�^�C�g���ɔ��
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{
		SetFade(MODE_TITLE);
	}
}
//===========
// �`�揈��
//===========
void DrawTutorial(void)
{
	SetCamera();

	DrawPolygon();

	DrawMeshCylinder();

	DrawWall();

	DrawMeshWall();

	DrawShadow();

	DrawBlock();

	DrawBiillboard();

	DrawPlayer();

	DrawEnemy();

	DrawExplosion();

	DrawEffect();

	DrawParticle();

	DrawTimer();

	DrawScore();
}
//===============
// �Q�[���̏��
//===============
void SetTutorialState(TUTORIAL state)
{
	g_tutorial = state;
}
//=====================
// �Q�[���̏�Ԃ̎擾
//=====================
TUTORIAL GetTutorialSatate(void)
{
	return g_tutorial;
}