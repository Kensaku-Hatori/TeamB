//==============================
//
//  �Q�[����ʕ\������[Tutorial.h]
//  Author:kaiti
//
//==============================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

#define MAX_TUTORIALTIME (999)
//�Q�[���̏��
typedef enum
{
	TUTORIAL_NONE=0,	//�������Ă��Ȃ����
	TUTORIAL_NORMAL,	//�ʏ��ԁi�Q�[���v���C���j
	TUTORIAL_TIMEOVER,	//�N���A
	TUTORIAL_MAX
}TUTORIAL;

//�v���g�^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorialState(TUTORIAL state);
TUTORIAL GetTutorialSatate(void);

#endif