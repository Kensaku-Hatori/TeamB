//==============================
//
//  �I������[Title.h]
//  Author:kaiti
//
//==============================
#include "title.h"
#include "titleinfo.h"
#include "ranking.h"
#include "fade.h"
#include "sound.h"
//�O���[�o���ϐ�
int g_nTimeTitle; //�^�C�g�����烉���L���O�ւ̎���

//============
//����������
//============
void InitTitle(void)
{
	g_nTimeTitle = 0;

	InitTitleInfo();

}
//==========
//�I������
//==========
void UninitTitle(void)
{
	UninitTitleInfo();

}
//==========
//�X�V����
//==========
void UpdateTitle(void)
{
	UpdateTitleInfo();

	g_nTimeTitle++;
	if (g_nTimeTitle >= MAX_TITLE)
	{
		SetRankMode(RANKMODE_TITLE);
		SetFade(MODE_RANK);
		g_nTimeTitle = 0;
	}

}
//===========
//�`�揈��
//===========
void DrawTitle(void)
{
	DrawTitleInfo();

}