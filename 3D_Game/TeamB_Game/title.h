//==============================
//
//  タイトル表示処理[title.h]
//  Author:kaiti
//
//==============================
#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"

#define MAX_TITLE (450)

//ポーズメニュー
typedef enum
{
	TITLE_START = 0,//ゲームSTART
	TITLE_RANK,		//ランキング
	TITLE_MAX,
}TITLE;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif