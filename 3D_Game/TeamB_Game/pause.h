//==============================
//
//  ポーズ処理[pause.h]
//  Author:kaiti
//
//==============================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTNUE=0,//戻る
	PAUSE_MENU_RETRY,    //やり直す
	PAUSE_MENU_QUIT,     //タイトルに戻る
	PAUSE_MENU_MAX,
}PAUSE_MENU;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif