//==============================
//
//  タイトル表示処理[titleinfo.h]
//  Author:kaiti
//
//==============================
#ifndef _TITLEINFO_H_
#define _TITLEINFO_H_

#include"main.h"

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