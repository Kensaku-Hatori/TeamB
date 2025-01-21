//================================
//
//  UI�\������[ui.cpp]
//  Author:kaiti
//
//================================
#include "ui.h"
#include "timer.h"
#include "score.h"

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
}
//===========
// �I������
//===========
void UninitUi(void)
{
	UninitTimer();

	UninitScore();
}
//===========
// �X�V����
//===========
void UpdateUi(void)
{
	UpdateTimer();

	UpdateScore();
}
//===========
// �`�揈��
//===========
void DrawUi(void)
{
	DrawTimer();

	DrawScore();
}