//==============================
//
//  �~�j�}�b�v����[minimap.h]
//  Author:kaiti
//
//==============================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include"main.h"

#define MINIMAP_X (250)
#define MINIMAP_Y (230)

#define MAPSIZE_PLAYER (40)

//�v���g�^�C�v�錾
void InitMiniMap(void);
void UninitMiniMap(void);
void UpdateMiniMap(void);
void DrawMiniMap(void);
void SetMapPlayer(int nStageNo);


#endif
