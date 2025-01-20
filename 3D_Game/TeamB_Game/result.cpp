//================================
//
//  ���U���g�\������[result.cpp]
//  Author:kaiti
//
//================================
#include "result.h"
#include "resultinfo.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "sound.h"

//�O���[�o���ϐ��錾

//===========
//����������
//===========
void InitResult(void)
{

	InitPolygon();

	InitCamera();

	InitLight();

	InitResultInfo();

}
//==========
//�I������
//==========
void UninitResult(void)
{
	UninitPolygon();

	UninitCamera();

	UninitLight();

	UninitResultInfo();
}
//==========
//�X�V����
//==========
void UpdateResult(void)
{
	UpdatePolygon();

	UpdateCamera();

	UpdateLight();

	UpdateResultInfo();
}
//==========
//�`�揈��
//==========
void DrawResult(void)
{
	SetCamera();

	DrawPolygon();


	DrawResultInfo();
}
