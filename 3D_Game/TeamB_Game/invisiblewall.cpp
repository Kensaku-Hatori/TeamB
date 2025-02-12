//******************************************
//
// �����Ȃ��ǂƂ̓����蔻��[invisiblewall.cpp]
// Hatori Kensaku
//
//******************************************

#include "invisiblewall.h"

Invisiblewall g_InvisibleWall[WALLTYPE_MAX];

// ���ό��ʂ��f�o�b�N�\�����邽�߂̃e�X�g�ϐ�
D3DXVECTOR2 test;

//***********************
// �����Ȃ��ǂ̏���������
//***********************
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
		g_InvisibleWall[nCount].PlayerPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_InvisibleWall[nCount].MoveStageNum = MODE_STAGEONE;
	}
	// �X�e�[�W���ƂɌ����Ȃ������Əo����ݒ肷��
	switch (Mode)
	{
	case MODE_STAGEONE:
		// ����
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		// �o��
		g_InvisibleWall[WALLTYPE_EXIT].Center = D3DXVECTOR3(-945.0f, 250, -650.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(-945.0f, 500, -650.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(-945.0f, 250.0f, -540.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(-945.0f, 250.0f, -760.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(-945.0f, 0, -650.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norWall = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].PlayerPos = D3DXVECTOR3(945.0f, 0.0f, 650.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGETWO;
		break;
	case MODE_STAGETWO:
		// ����
		g_InvisibleWall[WALLTYPE_ENTRANCE].Center = D3DXVECTOR3(945.0f, 250, 650.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(945.0f, 500, 645.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(945.0f, 250.0f, 540.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(945.0f, 250.0f, 750.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(945.0f, 0, 645.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norWall = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].PlayerPos = D3DXVECTOR3(-945.0f, 0.0f, -650.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		// �o��
		g_InvisibleWall[WALLTYPE_EXIT].Center = D3DXVECTOR3(-355.0f, 250, -945.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(-355.0f, 500.0f, -945.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(-460.0f, 250.0f, -945.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(-250.0f, 250.0f, -945.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(-355.0f, 0.0f, -945.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norWall = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].PlayerPos = D3DXVECTOR3(85.0f, 0.0f, -725.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGETHREE;
		break;
	case MODE_STAGETHREE:
		// ����
		g_InvisibleWall[WALLTYPE_ENTRANCE].Center = D3DXVECTOR3(85.0f, 250, -725.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(85.0f, 500.0f, -725.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(30.0f, 250.0f, -725.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(140.0f, 250.0f, -725.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(85.0f, 0.0f, -725.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norWall = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].PlayerPos = D3DXVECTOR3(-355.0f, 0.0f, -945.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGETWO;

		// �o��
		g_InvisibleWall[WALLTYPE_EXIT].Center = D3DXVECTOR3(-800.0f, 250, 35.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(-800.0f, 500.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(-800.0f, 250.0f, -20.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(-800.0f, 250.0f, 90.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(-800.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norWall = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGEFOUR;
		break;
	case MODE_STAGEFOUR:
		// ����
		g_InvisibleWall[WALLTYPE_ENTRANCE].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_ENTRANCE].MoveStageNum = MODE_STAGEONE;

		// �o��
		g_InvisibleWall[WALLTYPE_EXIT].Top = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Left = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].Bottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norLeft = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].norBottom = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_InvisibleWall[WALLTYPE_EXIT].MoveStageNum = MODE_STAGEONE;
		break;
	default:
		break;
	}
}
//*********************
// �����Ȃ��ǂ̍X�V����
//*********************
void UpdateInvisibleWall()
{
	for (int nCount = 0; nCount < WALLTYPE_MAX; nCount++)
	{
		Player* pPlayer = GetPlayer();
		CollisionInvisibleWall(g_InvisibleWall[nCount],pPlayer->pos,pPlayer->NextPosition);
	}
}
//*************************
// �����Ȃ��ǂƂ̓����蔻��
//*************************
void CollisionInvisibleWall(Invisiblewall Box, D3DXVECTOR3 Point , D3DXVECTOR3 &NextPoint)
{
	D3DXVECTOR3 TopVec,LeftVec,RightVec,BottomVec,WallVec;
	TopVec = Point - Box.Top;
	LeftVec = Point - Box.Left;
	RightVec = Point - Box.Right;
	BottomVec = Point - Box.Bottom;
	WallVec = Point - Box.Center;
	D3DXVECTOR3 test1 = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVECTOR3 test2 = D3DXVECTOR3(0.0f, 0.0f,-1.0f);
	FLOAT fDotTop, fDotLeft, fDotRight, fDotBottom,fDotWall;
	fDotTop = D3DXVec3Dot(&TopVec, &Box.norTop);
	fDotLeft = D3DXVec3Dot(&LeftVec, &Box.norLeft);
	fDotRight = D3DXVec3Dot(&RightVec, &Box.norRight);
	fDotBottom = D3DXVec3Dot(&BottomVec, &Box.norBottom);
	fDotWall = D3DXVec3Dot(&WallVec, &Box.norWall);
	test.x = fDotLeft;
	test.y = fDotRight;

	// �e�ʂƃv���C���[�Ƃ̓��ό��ʂ��O�ȏ�ŏo���ɑ΂��Đ����Ȗʂ̓��ό��ʂ��O�ȏゾ������
	if (fDotTop < 0 && fDotLeft < 0 && fDotRight < 0 && fDotBottom <= 0 && fDotWall < 0)
	{
		// �e�����o���ɐݒ肳��Ă���ړ���̃X�e�[�W�ԍ��Ɉړ�����
		SetFade(Box.MoveStageNum);
		// �����ʒu��ݒ肷��
		NextPoint = Box.PlayerPos;
	}
}

D3DXVECTOR2 Gettest()
{
	return test;
}

D3DXVECTOR3 GetBottom()
{
	return g_InvisibleWall[WALLTYPE_EXIT].Bottom;
}