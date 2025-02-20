//================================
//
// �v���C���[�\������[player.h]
// Author:kaiti
//
//================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"
#include "status.h"
#include "key.h"
#include "loadmotion.h"
#include "skill.h"

#define PLAYER_RADIUS (3)			// �v���C���[�̔��a

#define PLAYER_MP (500)				// MP
#define PLAYER_HP (float)(1000)		// HP
#define PLAYER_SPEED (float) (2.0f)	// ���x
#define PLAYER_AP (100)				// �U����

// �v���C���[�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_KNOCKUP,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 posOld;				// �ʒu
	D3DXVECTOR3 size;				// �T�C�Y
	D3DXVECTOR3 move;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 rotDest;			// ����
	D3DXVECTOR3 NextPosition;		// �����ʒu
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxWand;				// ���̃}�g���b�N�X
	OBJECTINFO PlayerMotion;		// �p�[�c���ƃ��[�V�������
	int nIdxShadow;					// �e�̃C���f�b�N�X
	int nIndxCircle;				// �T�[�N���̃C���f�b�N�X
	int nCntState;
	bool bUse;						// �g�p��
	bool bLanding;					// �n�ʂɒ��n���Ă��邩�ǂ���
	bool bfirst;					// �ŏ����ǂ���
	bool bHit;
	PlayerStatus Status;			// �X�e�[�^�X
	SKILLTYPE Skilltype;
	PLAYERSTATE state;
	
	int nNumModel;					// �p�[�c�̑���
	int nNumMotion;					// ���[�V�����̑���
	MOTIONTYPE motionType;			// ���[�V�����̎��
	bool bLoopMotion;				// ���[�v���邩�ǂ���
	int nNumKey;					// �L�[�̑���
	int nKey;						// ���݂̃L�[No
	int nCntMotion;					// ���[�V�����̃J�E���^�[

	bool btest;
	bool bAbolition;				// �S�Ńt���O(true�őS��)

	float fSightRange;
	float fSightAngle;
	float fDistance;
	bool bLockOn;
	bool bWantLockOn;
	int nLockOnEnemy;

}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void PlayerMove(void);
void SkillChange(void);
Player* GetPlayer(void);
void HitPlayer(float Atack, D3DXVECTOR3 Pos);
void SetMesh(char* pFilePath, int Indx);
void SetPartsInfo(LoadInfo PartsInfo);
void PlayerMotion(MOTIONINFO *pMotionInfo);
void MatrixWand(void);

#endif