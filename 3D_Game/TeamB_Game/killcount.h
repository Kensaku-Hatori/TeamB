//==============================
//
//  スコア処理[KillCount.h]
//  Author:kaiti
//
//==============================
#ifndef _KILLCOUNT_H_
#define _KILLCOUNT_H_

#include"main.h"

#define MAX_KILLCOUNTER (3)

//プロトタイプ宣言
void InitKillCount(void);
void UninitKillCount(void);
void UpdateKillCount(void);
void DrawKillCount(void);
void SetKillCount(int nKillCount);
void AddKillCount(int nValue);
int GetKillCount(void);

#endif#pragma once
