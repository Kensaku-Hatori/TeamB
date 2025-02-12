//******************************************
//
// �����Ȃ��ǂƂ̓����蔻��[invisiblewall.h]
// Hatori Kensaku
//
//******************************************
#ifndef INVISIBLEWALL_H_
#define INVISIBLEWALL_H_

#include "main.h"
#include "player.h"
#include "fade.h"

// ��X�e�[�W�ɏo�����������Ȃ��ǂ̎��
typedef enum
{
	WALLTYPE_ENTRANCE = 0,
	WALLTYPE_EXIT,
	WALLTYPE_MAX
}WALLTYPE;

// �����Ȃ��ǂƂ̓����蔻��ɕK�v�ȍ\����
typedef struct
{
	D3DXVECTOR3 Top, Left, Right, Bottom, Center;
	D3DXVECTOR3 norTop, norLeft, norRight, norBottom,norWall;
	MODE MoveStageNum;
	D3DXVECTOR3 PlayerPos;
}Invisiblewall;

void InitInvisibleWall();											// �����Ȃ��ǂ̏���������
void UpdateInvisibleWall();											// �����Ȃ��ǂ̍X�V����
void CollisionInvisibleWall(Invisiblewall Box, D3DXVECTOR3 Point,D3DXVECTOR3 &NextPoint);	// �����Ȃ��ǂƂ̓����蔻��
D3DXVECTOR2 Gettest();	// �f�o�b�N�p
#endif // !INVISIBLEWALL_H_