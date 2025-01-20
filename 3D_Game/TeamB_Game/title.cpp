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
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "loadstage.h"
//�O���[�o���ϐ�
int g_nTimeTitle; //�^�C�g�����烉���L���O�ւ̎���

//============
//����������
//============
void InitTitle(void)
{
	g_nTimeTitle = 0;

	InitPolygon();

	InitCamera();

	InitLight();

	InitTitleInfo();

	//LoadModelViewer();
}
//==========
//�I������
//==========
void UninitTitle(void)
{
	UninitPolygon();

	UninitCamera();

	UninitLight();


	UninitTitleInfo();
}
//==========
//�X�V����
//==========
void UpdateTitle(void)
{
	Camera* pCamera;
	pCamera = GetCamera();

	UpdatePolygon();

	UpdateCamera();

	pCamera->rot.y += 0.01f;

	UpdateLight();


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
	SetCamera();

	DrawPolygon();


	DrawTitleInfo();
}