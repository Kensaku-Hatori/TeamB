//==============================
//
//  �^�C�g���\������[title.h]
//  Author:kaiti
//
//==============================
#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"

#define MAX_TITLE (450)

//�|�[�Y���j���[
typedef enum
{
	TITLE_START = 0,//�Q�[��START
	TITLE_RANK,		//�����L���O
	TITLE_MAX,
}TITLE;

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif