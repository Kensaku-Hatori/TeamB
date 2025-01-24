//==============================
//
//  アイテム欄処理[itemui.h]
//  Author:kaiti
//
//==============================
#ifndef _ITEMUI_H_
#define _ITEMUI_H_

#include"main.h"

#define ITEMUIFRAME_X (200)
#define ITEMUIFRAME_Y (300)

#define ITEMUI_X (120)
#define ITEMUI_Y (50)


//プロトタイプ宣言
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI(void);
void DrawItemUI(void);

#endif
