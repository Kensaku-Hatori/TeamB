//================================
//
//  UI�\������[ui.cpp]
//  Author:kaiti
//
//================================
#include "ui.h"
#include "timer.h"
#include "score.h"
#include "gauge.h"
#include "itemui.h"
#include "minimap.h"
#include "lockon.h"
#include "skillui.h"
#include "mission.h"
#include "player.h"
#include "bossgauge.h"
#include "ButtonUi.h"

//�O���[�o���ϐ�

//=============
// ����������
//=============
void InitUi(void)
{
	Player* pPlayer = GetPlayer();

	InitButtonUi();

	InitTimer();
	SetTimer(0,0);
	
	InitScore();
	SetScore(pPlayer->nScore);

	InitGauge();
	SetGauge(GAUGETYPE_HP, D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR2(300.0f, 20.0f));
	SetGauge(GAUGETYPE_MP, D3DXVECTOR3(30.0f, 80.0f, 0.0f), D3DXVECTOR2(300.0f, 20.0f));

	InitItemUI();

	//InitMiniMap();
	//SetMapPlayer(MODE_STAGEONE);

	InitSkillUI();

	InitMission();

	InitBossGauge();

	InitLockon();
}
//===========
// �I������
//===========
void UninitUi(void)
{
	UninitTimer();

	UninitScore();

	UninitGauge();

	UninitItemUI();

	//UninitMiniMap();

	UninitSkillUI();

	UninitMission();

	UninitBossGauge();

	UninitButtonUi();

	UninitLockon();
}
//===========
// �X�V����
//===========
void UpdateUi(void)
{
	MODE nMode = GetMode();

	UpdateTimer();

	UpdateScore();

	UpdateGauge();

	UpdateItemUI();

	//UpdateMiniMap();

	UpdateSkillUI();

	UpdateMission();

	if (nMode == MODE_STAGEFOUR)
	{
		UpdateBossGauge();
	}

	UpdateButtonUi();

	UpdateLockon();
}
//===========
// �`�揈��
//===========
void DrawUi(void)
{
	MODE nMode = GetMode();

	DrawTimer();

	DrawScore();

	DrawGauge();

	DrawItemUI();

	//DrawMiniMap();

	DrawSkillUI();

	DrawMission();

	if (nMode == MODE_STAGEFOUR)
	{
		DrawBossGauge();
	}

	DrawButtonUi();

	DrawLockon();
}