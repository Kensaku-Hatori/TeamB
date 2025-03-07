//==============================
//
//  ������@UI�\������[ButtonUi.h]
//  Author:kaiti
//
//==============================
#ifndef _BUTTONUI_H_
#define _BUTTONUI_H_

#include"main.h"

#define MAX_BUTTONUI (64)

typedef enum
{
	//�L�[�{�[�h
	BUTTONUI_WHEEL = 0,
	BUTTONUI_AKEY,
	BUTTONUI_DKEY,

	//�R���g���[���[
	BUTTONUI_SAYU,
	BUTTONUI_R1,
	BUTTONUI_L1,

	BUTTONUI_MAX
}BUTTONUI;

typedef enum
{
	BUTTONUI_TYPE_GAME = 0,
	BUTTONUI_TYPE_TUTORIAL,
	BUTTONUI_TYPE_MAX
}BUTTONUI_TYPE;


typedef struct
{
	BUTTONUI ButtonUi;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	BUTTONUI_TYPE UiType;
	bool bUse;
}ButtonUi;

//�v���g�^�C�v�錾
void InitButtonUi(void);
void UninitButtonUi(void);
void UpdateButtonUi(void);
void DrawButtonUi(void);
void DrawTutorialButtonUi(void);
void SetButtonUi(BUTTONUI type, D3DXVECTOR3 pos, D3DXVECTOR3 size,BUTTONUI_TYPE UiType);
#endif
