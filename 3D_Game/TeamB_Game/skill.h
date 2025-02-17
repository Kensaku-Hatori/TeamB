//================================
//
// �e����[skill.h]
// Author:kaiti
//
//================================
#ifndef _SKILL_H_
#define _SKILL_H_

#include "main.h"

#define MAX_SKILL (256)
#define SKILL_LIFE (30)
#define SKILL_SIZE (float)(2.5)
#define INTERVAL_IMPACT (30)
#define DISTANCE_HORMING (100)
#define INTERVAL_HORMING (100)
#define HORMING_SPEEDANIM (100)

typedef enum
{
	SKILLTYPE_NONE = 0,
	SKILLTYPE_HORMING,
	SKILLTYPE_MAX
}SKILLTYPE;
//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 StartPos;		// �ŏ��̈ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 moveDest;		// �ړ���
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 dir;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	SKILLTYPE ntype;
	int nIdxShadow;				// �e�̃C���f�b�N�X�ۑ��p
	int nLife;					// ����
	int nCount, nCounter;
	int nIndxHorming;
	int AnimCounter;
	float fDistance;			// ����
	float Speed;
	float fRotRatio;
	bool bHit;
	bool bUse;					// �g�p���Ă��邩�ǂ���
	bool bHorming;
}Skill;

//�v���g�^�C�v�錾
void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 rot, SKILLTYPE ntype,float fRotRatio);
void SerchHormingEnemy(int Indx);
void UpdateHormingPosition(int Indx);
void UpdateHormingAnim(int Indx);
Skill* GetSkill();
#endif