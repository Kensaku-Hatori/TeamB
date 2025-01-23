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
#define SKILL_LIFE (100)
#define SKILL_SIZE (10)

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 dir;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nIdxShadow;
	int nLife;
	bool bUse;
}Skill;

//�v���g�^�C�v�錾
void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 rot);

#endif