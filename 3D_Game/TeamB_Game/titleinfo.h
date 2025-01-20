//==============================
//
//  タイトル表示処理[titleinfo.h]
//  Author:kaiti
//
//==============================
#ifndef _TITLEINFO_H_
#define _TITLEINFO_H_

#include"main.h"

#define TITLESELECT_HEIGHT (100)
#define TITLESELECT_WIDTH (400)

#define TITLELOGO_HEIGHT (200)
#define TITLELOGO_WIDTH (600)

#define LOGO_END_Y (200)

//ポーズメニュー
typedef enum
{
	TITLE_START = 0,//ゲームSTART
	TITLE_RANK,		//ランキング
	TITLE_FIN,		//おわる
	TITLE_MAX,
}TITLEINFO;

//プロトタイプ宣言
void InitTitleInfo(void);
void UninitTitleInfo(void);
void UpdateTitleInfo(void);
void DrawTitleInfo(void);

#endif