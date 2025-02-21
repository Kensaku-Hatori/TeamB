//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	//BGM
	SOUND_LABEL_GAME = 0,
	SOUND_LABEL_GAMECLEAR,
	SOUND_LABEL_GAMEOVER,
	SOUND_LABEL_RANKING,
	SOUND_LABEL_TITLE,

	//SE
	SOUND_LABEL_DESICION,
	SOUND_LABEL_MAGIC,
	SOUND_LABEL_POTION,
	SOUND_LABEL_SELECT,
	SOUND_LABEL_SKELETON,
	SOUND_LABEL_SLASH,
	SOUND_LABEL_ZOMBI,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
