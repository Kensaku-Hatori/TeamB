//==============================
//
//  �ړI�\������[mission.h]
//  Author:kaiti
//
//==============================
#ifndef _MISSION_H_
#define _MISSION_H_

#include"main.h"

#define MISSION_X (75)
#define MISSION_Y (25)


typedef enum
{
	MISSION_ZENMETU = 0,
	MISSION_IDOU,
	MISSION_BOSS,
	MISSION_MAX
}MISSION;

typedef struct
{
	MISSION mission;
}Mission;

//�v���g�^�C�v�錾
void InitMission(void);
void UninitMission(void);
void UpdateMission(void);
void DrawMission(void);
void SetMapPlayer(int nStageNo);
Mission* GetMission();


#endif
