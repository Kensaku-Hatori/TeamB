//==============================
//
//  �|�[�Y����[pause.h]
//  Author:kaiti
//
//==============================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTNUE=0,//�߂�
	PAUSE_MENU_RETRY,    //��蒼��
	PAUSE_MENU_QUIT,     //�^�C�g���ɖ߂�
	PAUSE_MENU_MAX,
}PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif