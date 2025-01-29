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
#include "loadmotion.h"
#include "model.h"
#include "meshfield.h"

//�O���[�o���ϐ��錾

//===========
//����������
//===========
void InitResult(void)
{
	InitMeshfield();

	InitCamera();

	InitLight();

	InitResultInfo();

	InitMotion();
	InitStageModel();

	LoadModelViewer();
}
//==========
//�I������
//==========
void UninitResult(void)
{
	UninitMeshfield();

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
	UpdateMeshfield();

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

	DrawMeshfield();

	DrawStageModel();

	DrawResultInfo();
}
