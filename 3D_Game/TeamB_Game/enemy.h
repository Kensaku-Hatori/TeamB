//************************
// 
// �G�Ɋւ��鏈��[enemy.h]
// Hatori Kensaku
//
//************************
#ifndef ENEMY_H_
#define ENEMY_H_

#include "main.h"
#include "key.h"
#include "Object.h"
#include "status.h"
#include "loadmotion.h"

#define MAX_ENEMY (126)					// �G�̍ő吔
#define MAX_ENEMYPARTS (10)				// �G�̍ő�p�[�c��
#define ENEMY_RADIUS (float)(8.0f)		// �G�̑傫��
#define ENEMY_RUNSPEED (float)(1.0f)	// �G�̑���X�s�[�h

#define ENEMY_HP (float)(150)			// HP
#define ENEMY_SPEED (float) (2.0f)		// ���x
#define ENEMY_AP (float)(10)			// �U����

// �s���̋���
#define ATTACK_DIST (float)(50.0f)		// �U��
#define HOMING_DIST (float)(300.0f)		// �z�[�~���O

//�t���[��
#define ATTACK_FREAM (180)				// �U��a

//�ړ���
#define HOMING_MOVE (float)(0.2f)		// �z�[�~���O
#define WELL_MOVE (float)(0.1f)			// �l�q��

// �G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_KNOCKUP,
	ENEMYSTATE_MAX
}ENEMYSTATE;

// �G�̍s���p�^�[��
typedef enum
{
	ENEMYACTION_WELL,
	ENEMYACTION_RUN,
	ENEMYACTION_ATTACK,
	ENEMYACTION_MAX
}ENEMYACTION;

// �G�̎��
typedef enum
{
	ENEMYTYPE_SKELETON = 0,
	ENEMYTYPE_ZOMBIE,
	ENEMYTyPE_MIDBOSS,
	ENEMYTYPE_MAX
}ENEMYTYPE;

// �G�̃o�b�t�@�E���[�V�����i�[
typedef struct
{
	OBJECTINFO EnemyMotion;
	int nNumParts;
}EnemyOrigin;

// �G�̍\����
typedef struct
{
	ENEMYSTATE state;
	ENEMYACTION ActionType;
	EnemyStatus Status;
	MOTIONTYPE pMotion;
	OBJECTINFO EnemyMotion;
	OBJECT Object;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	int nType;
	int Action;
	int nNumKey, nKey, nCounterMotion, nNextKey;
	int nNumModel;
	int IndxShadow;
	int nActionCount,nActionCounter;
	int statecount;
	float ShadowRadius;
	float ModelMinX, ModelMaxX;
	float Radius;
	bool bUse;
	bool bMotion;
	bool bHit;
	int IndxGuage[3];
	float fDistance;
	float fActionDistance;

	float fSightRange;
	float fSightAngle;
	bool bLockOn;

}ENEMY;

//*****************
// �v���g�^�C�v�錾
//*****************
void InitEnemy(void);										// �G�̏���������
void UninitEnemy(void);										// �G�̏I������
void UpdateEnemy(void);										// �G�̍X�V����
void DrawEnemy(void);										// �G�̕`�揈��
ENEMY* GetEnemy();											// �G�̎擾����
int* GetNumEnemy(void);										// �G�̑����擾����
void HitEnemy(float Atack,int Indx);						// �G�̃q�b�g����
void DeadEnemy(int Indx);									// �G�̎��S����
void SetEnemy(D3DXVECTOR3 pos, int nType,D3DXVECTOR3 rot);	// �G�̐ݒ菈��
void UpdateAction(int nCount);								// �G�̍s���p�^�[���X�V����
void EnemyState(int Indx);									// �G�̏�ԍX�V����
void SetEnemyPartsInfo(LoadInfo PartsInfo, int nType);		// �G�̃o�b�t�@�⃂�[�V�����ݒ菈��
void CollisionEnemy(void);									// �G�̓����蔻�菈��
void CollisionEnemyAction(int nCnt);						// �G�̃A�N�V�������̓����蔻�菈��
bool IsPlayerInsight(int Index);

#endif // !ENEMY_H_