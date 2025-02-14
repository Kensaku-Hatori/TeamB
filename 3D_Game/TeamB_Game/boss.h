//************************
// 
// �G�Ɋւ��鏈��[enemy.h]
// Hatori Kensaku
//
//************************
#ifndef BOSS_H_
#define BOSS_H_

#define BOSS_AP (10)
#define BOSS_HP (100)
#define BOSS_SPEED (1)
#define	BOSSATTACK_DIST (50)
#define BOSSHORMING_DIST (300)
#define BOSSHORMING_MOVE (float)(-2.0f)

#include "main.h"
#include "key.h"
#include "Object.h"
#include "status.h"
#include "loadmotion.h"

// �G�̏��
typedef enum
{
	BOSSSTATE_NORMAL = 0,
	BOSSSTATE_KNOCKUP,
	BOSSSTATE_MAX
}BOSSSTATE;

// �G�̍s���p�^�[��
typedef enum
{
	BOSSACTION_WELL,
	BOSSACTION_RUN,
	BOSSACTION_ATTACK,
	BOSSACTION_MAX
}BOSSACTION;

typedef struct
{
	BOSSACTION Action;
	float primary[BOSSACTION_MAX];
	int routine, routinecount;
	bool fFinishAction;
}BossAi;

// �G�̃o�b�t�@�E���[�V�����i�[
typedef struct
{
	OBJECTINFO BossMotion;
	int nNumParts;
}BossOrigin;

// �G�̍\����
typedef struct
{
	BOSSSTATE state;
	BOSSACTION ActionType;
	BossStatus Status;
	MOTIONTYPE pMotion;
	OBJECTINFO BossMotion;
	OBJECT Object;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	BossAi BossAi;
	int Action;
	int nNumKey, nKey, nCounterMotion, nNextKey;
	int nNumModel;
	int IndxShadow;
	int nActionCount, nActionCounter;
	int statecount;
	float ShadowRadius;
	float ModelMinX, ModelMaxX;
	float Radius;
	bool bUse;
	bool bMotion;
	bool bHit;
	int IndxGuage[3];
	float fDistance;
}BOSS;

//*****************
// �v���g�^�C�v�錾
//*****************
void InitBoss(void);										// �{�X�̏���������
void UninitBoss(void);										// �{�X�̏I������
void UpdateBoss(void);										// �{�X�̍X�V����
void DrawBoss(void);										// �{�X�̕`�揈��
BOSS* GetBoss();											// �{�X�̎擾����
void HitBoss(float Atack);									// �{�X�̃q�b�g����
void DeadBoss();											// �{�X�̎��S����
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// �{�X�̐ݒ菈��
void UpdateBossAction();									// �{�X�̍s���p�^�[���X�V����
void BossState();											// �{�X�̏�ԍX�V����
void SetBossPartsInfo(LoadInfo PartsInfo);					// �{�X�̃o�b�t�@�⃂�[�V�����ݒ菈��
void CollisionBoss(void);									// �{�X�̓����蔻�菈��
#endif // !ENEMY_H_