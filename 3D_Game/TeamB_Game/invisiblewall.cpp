//******************************************
//
// Œ©‚¦‚È‚¢•Ç‚Æ‚Ì“–‚½‚è”»’è[invisiblewall.cpp]
// Hatori Kensaku
//
//******************************************

#include "invisiblewall.h"

Invisiblewall g_InvisibleWall[WALLTYPE_MAX];
D3DXVECTOR2 test;

void InitInvisibleWall()
{
	MODE Mode = GetMode();
	for (int nCount = 0; nCount < WALLTYPE_MAX; nCount++)
	{
		g_InvisibleWall[nCount].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[nCount].MoveStageNum = MODE_STAGEONE;
	}
	switch (Mode)
	{
	case MODE_STAGEONE:
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(-945.0f, 500, -650.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(-945.0f, 250.0f, -540.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(-945.0f, 250.0f, -760.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(-945.0f, 0, -650.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGETWO;
		break;
	case MODE_STAGETWO:
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGEONE;
		break;
	case MODE_STAGETHREE:
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGEONE;
		break;
	case MODE_STAGEFOUR:
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGEONE;
		break;
	default:
		break;
	}
}
void UpdateInvisibleWall()
{
	for (int nCount = 0; nCount < WALLTYPE_MAX; nCount++)
	{
		Player* pPlayer = GetPlayer();
		CollisionInvisibleWall(g_InvisibleWall[1],pPlayer->pos);
	}
}
void CollisionInvisibleWall(Invisiblewall Box, D3DXVECTOR3 Point)
{
	D3DXVECTOR3 TopVec,LeftVec,RightVec,BottomVec;
	TopVec = Point - Box.Top;
	LeftVec = Point - Box.Left;
	RightVec = Point - Box.Right;
	BottomVec = Point - Box.Bottom;
	D3DXVECTOR3 test1 = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVECTOR3 test2 = D3DXVECTOR3(0.0f, 0.0f,-1.0f);
	FLOAT fDotTop, fDotLeft, fDotRight, fDotBottom;
	fDotTop = D3DXVec3Dot(&TopVec, &Box.norTop);
	fDotLeft = D3DXVec3Dot(&LeftVec, &Box.norLeft);
	fDotRight = D3DXVec3Dot(&RightVec, &Box.norRight);
	fDotBottom = D3DXVec3Dot(&BottomVec, &Box.norBottom);
	test.x = fDotTop;
	test.y = fDotBottom;

	if (fDotTop < 0 && fDotLeft < 0 && fDotRight < 0 && fDotBottom <= 0)
	{
		SetFade(Box.MoveStageNum);
	}
}
D3DXVECTOR2 Gettest()
{
	return test;
}