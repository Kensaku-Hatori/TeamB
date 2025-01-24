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
#include "sound.h"
#include "loadstage.h"
#include "model.h"

//�O���[�o���ϐ��錾

//===========
//����������
//===========
void InitResult(void)
{
	InitStageModel();

	LoadModelViewer();

	InitCamera();

	InitLight();

	InitResultInfo();

}
//==========
//�I������
//==========
void UninitResult(void)
{
	UninitStageModel();

	UninitCamera();

	UninitLight();

	UninitResultInfo();
}
//==========
//�X�V����
//==========
void UpdateResult(void)
{
	UpdateStageModel();

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

	DrawStageModel();

	DrawResultInfo();
}
