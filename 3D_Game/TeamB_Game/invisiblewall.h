//******************************************
//
// Œ©‚¦‚È‚¢•Ç‚Æ‚Ì“–‚½‚è”»’è[invisiblewall.h]
// Hatori Kensaku
//
//******************************************
#ifndef INVISIBLEWALL_H_
#define INVISIBLEWALL_H_

#include "main.h"
#include "player.h"
#include "fade.h"

typedef enum
{
	WALLTYPE_ENTRANCE = 0,
	WALLTYPE_EXIT,
	WALLTYPE_MAX
}WALLTYPE;

typedef struct
{
	D3DXVECTOR3 Top, Left, Right, Bottom;
	D3DXVECTOR3 norTop, norLeft, norRight, norBottom;
	MODE MoveStageNum;
}Invisiblewall;

void InitInvisibleWall();
void UpdateInvisibleWall();
void CollisionInvisibleWall(Invisiblewall Box,D3DXVECTOR3 Point);
D3DXVECTOR2 Gettest();
#endif // !INVISIBLEWALL_H_