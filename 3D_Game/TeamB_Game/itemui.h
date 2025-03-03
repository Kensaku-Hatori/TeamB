//==============================
//
//  アイテム欄処理[itemui.h]
//  Author:kaiti
//
//==============================
#ifndef _ITEMUI_H_
#define _ITEMUI_H_

#include "main.h"
#include "Item.h"

#define ITEMUIFRAME_X (280)
#define ITEMUIFRAME_Y (160)

#define ITEMUI_X (180)
#define ITEMUI_Y (50)

#define ITEMUINO_SIZE (40)

#define MAX_ITEMGET (2)//取得できるアイテムの桁数

#define MAX_ITEMUI (2)

//プロトタイプ宣言
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI(void);
void DrawItemUI(void);
void SetItemUI(void);
void AddItemUI(ITEMTYPE type);


#endif
