//============================
//
// ���b�N�I������[lockon.h]
// Author:kaiti
//
//============================
#ifndef _LOCKON_H
#define _LOCKON_H_

#include "main.h"

#define LOCKON_X (100)
#define LOCKON_Y (100)

//�v���g�^�C�v�錾
void InitLockon(void);
void UninitLockon(void);
void UpdateLockon(void);
void DrawLockon(void);
bool IsEnemyInsight(void);
bool EnemyDistanceSort(int EnemyCount);

#endif
