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
#include "balltimer.h"
#include "ballgauge.h"
#include "particle.h"
#include "killcount.h"

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
	SetBlock(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);

	InitPlayer();

	InitEnemy();
	SetEnemy(D3DXVECTOR3(150.0f, 300.0f, 150.0f));

	InitBiillboard();
	SetBiillboard(D3DXVECTOR3(0.0f, 50.0f, 100.0f));	// �ړ�
	SetBiillboard(D3DXVECTOR3(-350.0f, 50.0f, -50.0f)); // �W�����v
	SetBiillboard(D3DXVECTOR3(130.0f, 50.0f, 100.0f));	// �A�N�V����
	SetBiillboard(D3DXVECTOR3(0.0f, 150.0f, 100.0f));	// �^�C�g���ɖ߂�
	SetBiillboard(D3DXVECTOR3(-130.0f, 50.0f, 100.0f));	// ���_�ړ�
	SetBiillboard(D3DXVECTOR3(0.0f, 50.0f, -300.0f));	// �X�g���C�N

	InitEffect();

	InitParticle();

	InitExplosion();

	InitMeshCylinder();

	InitWall();

	SetWall(D3DXVECTOR3(0.0f, -WALL_HEIGHT, POLYGON_Y), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1.0f);//�O 0
	SetWall(D3DXVECTOR3(0.0f, -WALL_HEIGHT, -POLYGON_Y), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);//�O 1
	SetWall(D3DXVECTOR3(POLYGON_X, -WALL_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1.0f);//�O 2
	SetWall(D3DXVECTOR3(-POLYGON_X, -WALL_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1.0f);//�O 3

	InitMeshWall();

	SetMeshWall(D3DXVECTOR3(-3000.0f, -500.0f, 3000.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f));// ��
	SetMeshWall(D3DXVECTOR3(-3000.0f, 1500.0f, -3000.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f));// �V��

	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(MAX_TUTORIALTIME);

	InitScore();
	SetScore(0);

	InitBallTimer();
	SetBallTimer(MAX_BALLTIME);

	InitBallGauge();

	InitKillCount();
	SetKillCount(0);

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

	UninitBallGauge();

	UninitBallTimer();

	UninitKillCount();
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

	UpdateBallGauge();

	UpdateBallTimer();

	UpdateKillCount();

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
		StopSound(SOUND_LABEL_GAME);
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

	DrawBallGauge();

#ifdef _DEBUG
	DrawBallTimer();
#endif

	DrawKillCount();
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