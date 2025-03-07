//==============================
//
//  操作方法UI表示処理[ButtonUi.h]
//  Author:kaiti
//
//==============================
#ifndef _BUTTONUI_H_
#define _BUTTONUI_H_

#include"main.h"

#define MAX_BUTTONUI (64)

typedef enum
{
	//キーボード
	BUTTONUI_WHEEL,

	//コントローラー
	BUTTONUI_SAYU,
	BUTTONUI_MAX
}BUTTONUI;

typedef struct
{
	BUTTONUI ButtonUi;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	bool bUse;
}ButtonUi;

//プロトタイプ宣言
void InitButtonUi(void);
void UninitButtonUi(void);
void UpdateButtonUi(void);
void DrawButtonUi(void);
void SetButtonUi(BUTTONUI type, D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif
