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

//�O���[�o���ϐ�

//=============
// ����������
//=============
void InitUi(void)
{
	InitTimer();
	SetTimer(0,0);

	InitScore();
	SetScore(0);

	InitGauge();
	SetGauge(GAUGETYPE_HP, D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR2(300.0f, 20.0f));
	SetGauge(GAUGETYPE_MP, D3DXVECTOR3(30.0f, 80.0f, 0.0f), D3DXVECTOR2(300.0f, 20.0f));

	InitItemUI();

	InitMiniMap();
	SetMapPlayer(MODE_STAGEONE);

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

	UninitMiniMap();

	UninitLockon();
}
//===========
// �X�V����
//===========
void UpdateUi(void)
{
	UpdateTimer();

	UpdateScore();

	UpdateGauge();

	UpdateItemUI();

	UpdateMiniMap();

	UpdateLockon();
}
//===========
// �`�揈��
//===========
void DrawUi(void)
{
	DrawTimer();

	DrawScore();

	DrawGauge();

	DrawItemUI();

	DrawMiniMap();

	DrawLockon();
}