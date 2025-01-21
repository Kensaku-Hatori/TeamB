//================================
//
// �v���C���[�\������[Enemy.h]
// Author:kaiti
//
//================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "model.h"
#include "key.h"

#define ENEMY_SPEED (5)		//�G�̑��x
#define MAX_ENEMY (30)		//�G�̍ő吔
#define ENEMY_RADIUS (3)	//�G�̔��a
#define ENEMYAND_RADIUS (3)	//�G���m�̔��a
#define MAX_ENEMYTIME (120)	//�G�o������
#define ENEMY_LIFE (2)		//�G�̃��C�t
#define MOTIONFILE_ENEMY  ("data\\MOTION\\motionPin.txt")//�G�̃��[�V�����t�@�C��

//���[�V�����̎��
typedef enum
{
	ENEMYMOTIONTYPE_NEUTRAL = 0,
	ENEMYMOTIONTYPE_MOVE,
	ENEMYMOTIONTYPE_ACTION,
	ENEMYMOTIONTYPE_JUMP,
	ENEMYMOTIONTYPE_LANDING,
	ENEMYMOTIONTYPE_MAX
}ENEMYMOTIONTYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;

	float fRotX;
	float fRotY;
	float fRotZ;
}ENEMYKEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;
	ENEMYKEY aKey[MAX_PARTS];
}ENEMYKEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;
	int nNumKey;
	ENEMYKEY_INFO aKeyInfo[MAX_KEY];
}ENEMYMOTION_INFO;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ʒu
	D3DXVECTOR3 size;	//�T�C�Y
	D3DXVECTOR3 move;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 rotDest;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nIdxShadow;
	int nLife;
	int nDamage;
	float fDistance;
	bool bDamage;
	bool bJump;
	bool bCollision;
	bool bUse;
	//���f��
	MODELINFO aModel[MAX_PARTS];
	int nNumModel;
	//���[�V����
	ENEMYMOTION_INFO aMotionInfo[ENEMYMOTIONTYPE_MAX];  //���[�V�������
	int nNumMotion;										//���[�V�����̑���
	ENEMYMOTIONTYPE motionType;							//���[�V�����̎��
	bool bLoopMotion;									//���[�v���邩�ǂ���
	int nNumKey;										//�L�[�̑���
	int nKey;											//���݂̃L�[No
	int nCntMotion;										//���[�V�����̃J�E���^�[
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy* GetEnemy(void);
void SetEnemyMotion(int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos);
void CollisionEnemy(void);
void CollisionEnemyAndEnemy(int nCntEnemy);

#endif