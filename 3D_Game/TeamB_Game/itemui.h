//==============================
//
//  �A�C�e��������[itemui.h]
//  Author:kaiti
//
//==============================
#ifndef _ITEMUI_H_
#define _ITEMUI_H_

#include "main.h"
#include "Item.h"

#define ITEMUIFRAME_X (250)
#define ITEMUIFRAME_Y (230)

#define ITEMUI_X (180)
#define ITEMUI_Y (50)

#define ITEMUINO_SIZE (40)

#define MAX_ITEMGET (1)//�擾�ł���A�C�e���̌���

//�v���g�^�C�v�錾
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI(void);
void DrawItemUI(void);
void SetItemUI(void);
void AddItemUI(ITEMTYPE type);


#endif
