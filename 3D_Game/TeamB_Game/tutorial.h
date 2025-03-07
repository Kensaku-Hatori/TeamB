//==============================
//
//  チュートリアル処理[tutorial.h]
//  Author:kaiti
//
//==============================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

#define TUTO_X (400)
#define TUTO_Y (250)

#define YAJIRUSI_SIZE (50)
#define TUTO_NO_SIZE (50)
//ポーズメニュー
typedef enum
{
	TUTORIAL_MOVE=0,
	TUTORIAL_ROLL,
	TUTORIAL_SKILL,    
	TUTORIAL_SKILLCHENGE,
	TUTORIAL_ITEM,
	TUTORIAL_LOCKON,
	TUTORIAL_MAX,
}TUTORIAL;

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void ChangeTutorial(void);
void ChangeTutorialArrow(void);
void SetTutorial(TUTORIAL type);
void SetTutorialNo(void);
#endif