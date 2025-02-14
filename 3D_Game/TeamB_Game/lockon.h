//============================
//
// ���b�N�I������[lockon.h]
// Author:kaiti
//
//============================
#ifndef _LOCKON_H
#define _LOCKON_H_

#include "main.h"

#define LOCKON_SIZE (20)

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;
}Lockon;

//�v���g�^�C�v�錾
void InitLockon(void);
void UninitLockon(void);
void UpdateLockon(void);
void DrawLockon(void);
bool IsEnemyInsight(void);
bool EnemyDistanceSort(int EnemyCount);


#endif
