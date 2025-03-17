//==============================
//
//  オプション処理[option.h]
//  Author:kaiti
//
//==============================
#ifndef _OPTION_H_
#define _OPTION_H_

#include "main.h"

#define TUTO_X (400)
#define TUTO_Y (250)

#define YAJIRUSI_SIZE (50)
#define TUTO_NO_SIZE (50)
//ポーズメニュー
typedef enum
{
	OPTION_KANDO=0,
	OPTION_MAX,
}OPTION;

//プロトタイプ宣言
void InitOption(void);
void UninitOption(void);
void UpdateOption(void);
void DrawOption(void);
#endif