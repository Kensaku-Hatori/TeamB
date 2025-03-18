#include "bossmovie.h"
#include "meshfield.h"
#include "boss.h"
#include "camera.h"
#include "light.h"
#include "pause.h"
#include "wave.h"
#include "invisiblewall.h"
#include "shadow.h"

void InitBossMovie()
{
	Camera* pCamera = GetCamera();
	MODE Mode = GetMode();

	//���b�V���t�B�[���h�̏�����
	InitMeshfield();

	//�G�̏�����
	InitBoss();

	//�J�����̏�����
	InitCamera();

	//���C�g�̏�����
	InitLight();

	//�|�[�Y�̏�����
	InitPause();

	//�X�e�[�W�̏�����
	InitStageModel();

	//���[�V�����̏�����
	InitMotion();

	InitShadow();

	//���f���r���[���[�̓Ǎ�
	LoadModelViewer(MODE_STAGEFOUR);

	//�E�F�[�u�̏���������
	InitWave(MODE_STAGEFOUR);

	//�E�F�[�u�̓Ǎ�����
	LoadWave();

	// �����Ȃ��ǂ̏���������
	InitInvisibleWall();

	//�J�����̈ʒu�ݒ�
	D3DXVECTOR3 CameraPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ResetCameraPos(CameraPos, D3DXVECTOR3(0.0f,100.0f,300.0f));

	SetCameraWork(&pCamera->Anim, ANIMTYPE_TWO);
}
void UninitBossMovie()
{
	UninitMeshfield();
	UninitBoss();
	UninitCamera();
	UninitLight();
	UninitPause();
	UninitStageModel();
	UninitShadow();
}
void UpdateBossMovie()
{
	UpdateBoss();
	UpdateMovie();
}
void DrawBossMovie()
{
	//�J�����̐ݒ菈��
	SetCamera();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();

	DrawShadow();

	//�G�̕`�揈��
	DrawBoss();

	//�X�e�[�W�̕`�揈��
	DrawStageModel();
}