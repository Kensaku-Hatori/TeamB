//==============================
//
//  �X�R�A����[KillCount.h]
//  Author:kaiti
//
//==============================
#ifndef _KILLCOUNT_H_
#define _KILLCOUNT_H_

#include"main.h"

#define MAX_KILLCOUNTER (3)

//�v���g�^�C�v�錾
void InitKillCount(void);
void UninitKillCount(void);
void UpdateKillCount(void);
void DrawKillCount(void);
void SetKillCount(int nKillCount);
void AddKillCount(int nValue);
int GetKillCount(void);

#endif#pragma once
