//==============================
//
//  �{�X�Q�[�W����[bossgauge.h]
//  Author:kaiti
//
//==============================
#ifndef _BOSSGAUGE_H_
#define _BOSSGAUGE_H_

#include "main.h"
#include "boss.h"

#define BOSSGAUGE_DIVISION (float)(1.5f)
#define BOSSGAUGE_FRAME_X (float)(BOSS_HP / BOSSGAUGE_DIVISION)
#define BOSSGAUGE_FRAME_Y (15)

#define BOSSNAME_X (100)
#define BOSSNAME_Y (15)

//�v���g�^�C�v�錾
void InitBossGauge(void);
void UninitBossGauge(void);
void UpdateBossGauge(void);
void DrawBossGauge(void);
void BossgaugeDeff(void);
void RedBossgaugeDeff(void);

#endif
