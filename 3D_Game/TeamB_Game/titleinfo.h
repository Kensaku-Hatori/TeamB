//==============================
//
//  �^�C�g���\������[titleinfo.h]
//  Author:kaiti
//
//==============================
#ifndef _TITLEINFO_H_
#define _TITLEINFO_H_

#include"main.h"

//�|�[�Y���j���[
typedef enum
{
	TITLE_START = 0,//�Q�[��START
	TITLE_RANK,		//�����L���O
	TITLE_FIN,		//�����
	TITLE_MAX,
}TITLEINFO;

//�v���g�^�C�v�錾
void InitTitleInfo(void);
void UninitTitleInfo(void);
void UpdateTitleInfo(void);
void DrawTitleInfo(void);

#endif