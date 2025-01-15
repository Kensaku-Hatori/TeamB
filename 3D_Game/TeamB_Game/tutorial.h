//==============================
//
//  ゲーム画面表示処理[Tutorial.h]
//  Author:kaiti
//
//==============================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

#define MAX_TUTORIALTIME (999)
//ゲームの状態
typedef enum
{
	TUTORIAL_NONE=0,	//何もしていない状態
	TUTORIAL_NORMAL,	//通常状態（ゲームプレイ中）
	TUTORIAL_TIMEOVER,	//クリア
	TUTORIAL_MAX
}TUTORIAL;

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorialState(TUTORIAL state);
TUTORIAL GetTutorialSatate(void);

#endif