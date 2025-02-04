//============================================================
//
//ウェーブ処理[wave.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _WAVE_H_
#define _WAVE_H_

#include"main.h"

//マクロ定義
#define MAX_WAVE (4)

//プロトタイプ宣言
void InitWave(MODE mode);
void LoadWave();
int GetWave();
bool GetFinish();

#endif // !_WAVE_H_

