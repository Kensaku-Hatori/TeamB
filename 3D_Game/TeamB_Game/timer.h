//==============================
//
//  スコア処理[timer.h]
//  Author:kaiti
//
//==============================
#ifndef _TIMER_H_
#define _TIMER_H_

#include"main.h"
#include "game.h"

#define MAX_TIME (MAX_GAMETIME * 60)
#define MAX_TIMER (2)
#define TIMER_SIZE (15)
 
//プロトタイプ宣言
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(int nTimer, int nMinutes);
void AddTimer(int nValue);
int GetTimer(void);
void AddTimerMinutes(int nValue);
int GetMinutes(void);
void TimeScore(void);

#endif
