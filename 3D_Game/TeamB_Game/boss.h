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
#define BOSSHORMING_DIST (150)
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
void InitBoss(void);										// �G�̏���������
void UninitBoss(void);										// �G�̏I������
void UpdateBoss(void);										// �G�̍X�V����
void DrawBoss(void);										// �G�̕`�揈��
BOSS* GetBoss();											// �G�̎擾����
void HitBoss(float Atack);						// �G�̃q�b�g����
void DeadBoss();									// �G�̎��S����
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �G�̐ݒ菈��
void UpdateBossAction();								// �G�̍s���p�^�[���X�V����
void BossState();									// �G�̏�ԍX�V����
void SetBossPartsInfo(LoadInfo PartsInfo);		// �G�̃o�b�t�@�⃂�[�V�����ݒ菈��
void CollisionBoss(void);									// �G�̓����蔻�菈��
#endif // !ENEMY_H_