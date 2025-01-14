//==============================
//
//  �Q�[����ʕ\������[game.h]
//  Author:kaiti
//
//==============================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#define MAX_GAMETIME (60)

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,	//�������Ă��Ȃ����
	GAMESTATE_NORMAL,	//�ʏ��ԁi�Q�[���v���C���j
	GAMESTATE_TIMEOVER,	// �N���A
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameSatate(void);
void SetEnablePause(bool bPause);

#endif