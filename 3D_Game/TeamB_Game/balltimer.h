//==============================
//
//  �X�R�A����[BallTimer.h]
//  Author:kaiti
//
//==============================
#ifndef _BALLTIMER_H_
#define _BALLTIMER_H_

#include"main.h"

#define MAX_BALLTIMER (3)
#define BALLTIMER_Y (600)

//�v���g�^�C�v�錾
void InitBallTimer(void);
void UninitBallTimer(void);
void UpdateBallTimer(void);
void DrawBallTimer(void);
void SetBallTimer(int nBallTimer);
void AddBallTimer(int nValue);
int GetBallTimer(void);

#endif
