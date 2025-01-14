//==============================
//
//  スコア処理[BallGauge.h]
//  Author:kaiti
//
//==============================
#ifndef _BALLGAUGE_H_
#define _BALLGAUGE_H_

#include"main.h"

#define GAUGE_X (4)
#define GAUGE_Y (100)

//プロトタイプ宣言
void InitBallGauge(void);
void UninitBallGauge(void);
void UpdateBallGauge(void);
void DrawBallGauge(void);

#endif
