//==============================
//
//  目的表示処理[mission.h]
//  Author:kaiti
//
//==============================
#ifndef _MISSION_H_
#define _MISSION_H_

#include"main.h"

#define MISSION_X (120)
#define MISSION_Y (35)

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

//プロトタイプ宣言
void InitMission(void);
void UninitMission(void);
void UpdateMission(void);
void DrawMission(const char *MissionInfo, LPD3DXFONT Font,D3DXVECTOR2 Pos,D3DXCOLOR Grow,D3DXCOLOR FontCol,int GrowRadius);
void SetMapPlayer(int nStageNo);
Mission* GetMission();
#endif
