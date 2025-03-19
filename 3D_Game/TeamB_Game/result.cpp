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
#include "player.h"

bool isMode(ANIMTYPE *SetAnim,MODE DeadStage);
//===========
//����������
//===========
void InitResult(MODE OldMode)
{
	InitMeshfield();

	InitCamera();

	InitLight();

	InitResultInfo();

	InitMotion();

	InitStageModel();

	LoadModelViewer(OldMode);

	ANIMTYPE AnimInfo;
	Camera* pCamera = GetCamera();
	if (isMode(&AnimInfo, OldMode) == true)
	{
		SetCameraWork(&pCamera->Anim, AnimInfo);
	}
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

bool isMode(ANIMTYPE *SetAnim,MODE DeadStage)
{
	switch (DeadStage)
	{
	case MODE_STAGEONE:
		*SetAnim = ANIMTYPE_THREE;
		return true;
		break;
	case MODE_STAGETWO:
		*SetAnim = ANIMTYPE_FOUR;
		return true;
		break;
	case MODE_STAGETHREE:
		*SetAnim = ANIMTYPE_FIVE;
		return true;
		break;
	case MODE_STAGEFOUR:
		*SetAnim = ANIMTYPE_SIX;
		return true;
		break;
	default:
		return false;
		break;
	}
}