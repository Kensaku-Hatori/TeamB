//==============================
//
//  アイテム欄処理[itemui.h]
//  Author:kaiti
//
//==============================
#ifndef _ITEMUI_H_
#define _ITEMUI_H_

#include"main.h"

#define ITEMUIFRAME_X (250)
#define ITEMUIFRAME_Y (300)

#define ITEMUI_X (150)
#define ITEMUI_Y (50)

#define ITEMUINO_SIZE (50)
//プロトタイプ宣言
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI(void);
void DrawItemUI(void);

#endif
